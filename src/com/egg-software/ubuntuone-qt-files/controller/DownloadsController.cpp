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
    // TODO Check if the file exists, check the SHA1... (QCryptographicHash)

    LoginInfoDTO *loginInfo = DatabaseManager::getInstance()->getLoginInfo();
    this->savePath = this->getLocalPath(node->path);
    QDir().mkpath(QFileInfo(this->savePath).dir().path());

    DownloadNodeMessage *downloadMessage = new DownloadNodeMessage(loginInfo, this);
    connect(downloadMessage, SIGNAL(downloadProgress(int)), this, SIGNAL(downloadProgress(int)));
    connect(downloadMessage, SIGNAL(errorDownloadingNode(QString)), this, SIGNAL(errorDownloadingNode(QString)));
    connect(downloadMessage, SIGNAL(nodeDownloaded()), this, SLOT(nodeDownloaded()));
    downloadMessage->downloadNode(node, this->savePath);
}

void DownloadsController::nodeDownloaded()
{
#ifdef Q_OS_ANDROID
    AndroidUtils::openFile(this->savePath);
#else
    QDesktopServices::openUrl(QUrl::fromLocalFile(this->savePath));
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
