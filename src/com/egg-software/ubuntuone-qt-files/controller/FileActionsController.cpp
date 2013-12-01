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
#include "FileActionsController.h"
#include "DatabaseManager.h"
#include "LoginInfoDTO.h"
#include "DeleteMessage.h"
#include "PublishMessage.h"

FileActionsController::FileActionsController(QObject *parent)
    : QObject(parent),
      loginInfo(DatabaseManager::getInstance()->getLoginInfo())
{

}

void FileActionsController::deleteNode(const QString &path)
{
    DeleteMessage *deleteMessage = new DeleteMessage(this->loginInfo, this);
    connect(deleteMessage, SIGNAL(nodeDeleted()), this, SIGNAL(actionFinished()));
    connect(deleteMessage, SIGNAL(nodeDeleted()), deleteMessage, SLOT(deleteLater()));
    connect(deleteMessage, SIGNAL(errorDeletingNode(QString)), this, SIGNAL(actionFinishedWithError(QString)));
    connect(deleteMessage, SIGNAL(errorDeletingNode(QString)), deleteMessage, SLOT(deleteLater()));
    deleteMessage->deleteNode(path);
}

void FileActionsController::publishNode(const QString &path, bool publish)
{
    PublishMessage *publishMessage = new PublishMessage(this->loginInfo, this);
    connect(publishMessage, SIGNAL(nodePublished()), this, SIGNAL(actionFinished()));
    connect(publishMessage, SIGNAL(nodePublished()), publishMessage, SLOT(deleteLater()));
    connect(publishMessage, SIGNAL(errorPublishingNode(QString)), this, SIGNAL(actionFinishedWithError(QString)));
    connect(publishMessage, SIGNAL(errorPublishingNode(QString)), publishMessage, SLOT(deleteLater()));
    publishMessage->publishNode(path, publish);
}
