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
#include <QtCore>
#ifdef Q_OS_ANDROID
#include "AndroidUtils.h"
#else
#include <QtGui>
#endif

DownloadsController::DownloadsController(QObject *parent)
    : QObject(parent)
{

}

void DownloadsController::downloadAndOpenNode(NodeInfoDTO *node)
{
    // Check if the file is downloaded and in the last version
    this->localPath = this->getLocalPath(node->path);

    if (QFileInfo(this->localPath).exists()) {
        // Calculate the SHA1 of the local file to determine is it is in the last version
        QFile file(this->localPath);
        file.open(QIODevice::ReadOnly);
        QCryptographicHash fileSHA1(QCryptographicHash::Sha1);
        fileSHA1.addData(file.readAll());
        file.close();
        QString sha1 = "sha1:" + fileSHA1.result().toHex();

        if (node->hash == sha1) {
            qDebug() << "The file is in the last version, opening it without download";
            this->nodeDownloaded();
            return;
        }
    }

    // Download and open the file
    LoginInfoDTO *loginInfo = DatabaseManager::getInstance()->getLoginInfo();
    QDir().mkpath(QFileInfo(this->localPath).dir().path());
    DownloadNodeMessage *downloadMessage = new DownloadNodeMessage(loginInfo, this);
    connect(downloadMessage, SIGNAL(downloadProgress(int)), this, SIGNAL(downloadProgress(int)));
    connect(downloadMessage, SIGNAL(errorDownloadingNode(QString)), this, SIGNAL(errorDownloadingNode(QString)));
    connect(downloadMessage, SIGNAL(nodeDownloaded()), this, SLOT(nodeDownloaded()));
    downloadMessage->downloadNode(node, this->localPath);
}

void DownloadsController::nodeDownloaded()
{
#ifdef Q_OS_ANDROID
    AndroidUtils::openFile(this->localPath);
#else
    QDesktopServices::openUrl(QUrl::fromLocalFile(this->localPath));
#endif
}

QString DownloadsController::getLocalPath(const QString &nodePath)
{
#ifdef Q_OS_ANDROID
    QString baseLocalPath = AndroidUtils::getSDCardPath() + "/u1";
#else
    QString baseLocalPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif

    return baseLocalPath.endsWith(QDir::separator())
            ? baseLocalPath + QString(nodePath).replace("/~/", "")
            : baseLocalPath + QDir::separator() + QString(nodePath).replace("/~/", "");
}
