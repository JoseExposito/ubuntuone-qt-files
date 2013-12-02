/*
 * This file is part of UbuntuOne Qt Files.
 *
 * UbuntuOne Qt Files is free software:  you can redistribute it  and/or  modify it under the terms of the  GNU  General
 * Public License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any
 * later version.
 *
 * UbuntuOne Qt Files  is distributed in the hope  that it will be useful,  but  WITHOUT ANY WARRANTY;  without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with Foobar.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include "DownloadNodeMessage.h"
#include "NodeInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString DOWNLOAD_URL = "https://files.one.ubuntu.com";
}

DownloadNodeMessage::DownloadNodeMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      downloadReply(NULL),
      saveFile(NULL)
{

}

DownloadNodeMessage::~DownloadNodeMessage()
{
    delete this->downloadReply;
    delete this->saveFile;
}

void DownloadNodeMessage::downloadNode(NodeInfoDTO *node, const QString &savePath)
{
    qDebug() << "[+] DOWNLOADING FILE:";
    qDebug() << "\t Path: " << node->path;

    qDebug() << "\t Creating file at local path: " << savePath;
    this->saveFile = new QFile(savePath);
    if (!this->saveFile->open(QIODevice::WriteOnly)) {
        qDebug() << "Error opening file";
        emit this->errorDownloadingNode(tr("Error downloading file. Can not write at %1.").arg(savePath));
    }

    QString url = DOWNLOAD_URL + this->toPercentEncoding(node->contentPath);
    this->downloadReply = this->oauthGetRequest(url);
    connect(this->downloadReply, SIGNAL(downloadProgress(qint64,qint64)), this, SLOT(downloadProgress(qint64,qint64)));
    connect(this->downloadReply, SIGNAL(readyRead()), this, SLOT(downloadReadyRead()));
}

void DownloadNodeMessage::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    if (bytesTotal > 0) {
        int progress = (int)(bytesReceived/bytesTotal);
        qDebug() << "\t " << progress << "%";
        emit this->downloadProgress(progress);
    }
}

void DownloadNodeMessage::downloadReadyRead()
{
    this->saveFile->write(this->downloadReply->readAll());
}

void DownloadNodeMessage::replyFinished(QNetworkReply *reply)
{
    if (reply == this->downloadReply) {
        if (this->downloadReply->error() == QNetworkReply::NoError) {
            qDebug() << "\t Node correctly downloaded";
            this->saveFile->close();
            emit this->nodeDownloaded();
        } else {
            qDebug() << "\t Error downloading node: " << this->downloadReply->errorString();
            emit this->errorDownloadingNode(tr("Error downloading file. Please, try again later."));
        }
    }

}
