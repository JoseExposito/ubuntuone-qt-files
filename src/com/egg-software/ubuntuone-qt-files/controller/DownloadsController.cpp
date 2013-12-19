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
#include "DownloadsController.h"
#include "NodeInfoDTO.h"
#include "LoginInfoDTO.h"
#include "DatabaseManager.h"
#include "DownloadNodeMessage.h"
#include "NodeListModel.h"
#include "Utils.h"
#ifdef Q_OS_ANDROID
#include "AndroidUtils.h"
#endif
#include <QtCore>

DownloadsController::DownloadsController(QObject *parent)
    : QObject(parent)
{

}

void DownloadsController::downloadAndOpenNode(NodeListModel *model, int nodeIndex)
{
    this->model     = model;
    this->nodeIndex = nodeIndex;
    this->node      = this->model->getNode(this->nodeIndex);
    this->localPath = Utils::getLocalPath(this->node->path);

    // Avoid download twice the same file
    if (this->node->status == NodeInfoDTO::DOWNLOADING)
        return;

    // Check if the file is downloaded and in the last version
    if (QFileInfo(this->localPath).exists()) {
        // Calculate the SHA1 of the local file to determine is it is in the last version
        QFile file(this->localPath);
        file.open(QIODevice::ReadOnly);
        QCryptographicHash fileSHA1(QCryptographicHash::Sha1);
        fileSHA1.addData(file.readAll());
        file.close();
        QString sha1 = "sha1:" + fileSHA1.result().toHex();

        if (this->node->hash == sha1) {
            qDebug() << "The file is in the last version, opening it without download";
            this->nodeDownloaded();
            return;
        }
    }

    // Set the node in download status
    this->node->status = NodeInfoDTO::DOWNLOADING;
    this->node->downloadProgress = 0;
    this->model->refresNode(this->nodeIndex);

    // Download and open the file
    LoginInfoDTO *loginInfo = DatabaseManager::getInstance()->getLoginInfo();
    QString localSaveDir = QFileInfo(this->localPath).dir().path();
    QDir().mkpath(localSaveDir);

/*#ifdef Q_OS_ANDROID
    DownloadNodeMessage downloadMessage(loginInfo, this);
    QString url = downloadMessage.getDownloadUrlWithCredentials(this->node);
    qDebug() << url;
    qDebug() << localSaveDir;
    qDebug() << QFileInfo(this->localPath).fileName();
    AndroidUtils::downloadFile(url, localSaveDir, QFileInfo(this->localPath).fileName());
#else*/
    DownloadNodeMessage *downloadMessage = new DownloadNodeMessage(loginInfo, this);
    connect(downloadMessage, SIGNAL(downloadProgress(int)), this, SLOT(downloadProgress(int)));
    connect(downloadMessage, SIGNAL(errorDownloadingNode(QString)), this, SIGNAL(errorDownloadingNode(QString)));
    connect(downloadMessage, SIGNAL(nodeDownloaded()), this, SLOT(nodeDownloaded()));
    downloadMessage->downloadNode(this->node, this->localPath);
//#endif
}

void DownloadsController::downloadProgress(int progress)
{
    this->node->downloadProgress = progress;
    this->model->refresNode(this->nodeIndex);
}

void DownloadsController::nodeDownloaded()
{
    this->node->status = NodeInfoDTO::DOWNLOADED;
    this->node->downloadProgress = -1;
    this->model->refresNode(this->nodeIndex);

    Utils::openFile(this->localPath);
}

