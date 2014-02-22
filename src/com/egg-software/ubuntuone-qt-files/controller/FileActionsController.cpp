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
#include "RenameMessage.h"
#include "CreateFolderMessage.h"
#include "NodeInfoDTO.h"
#ifdef Q_OS_ANDROID
#include "AndroidUtils.h"
#include <QtAndroidExtras>
#else
#include <QtWidgets/QInputDialog>
#include <QtGui>
#endif
#include <QtCore>

FileActionsController *FileActionsController::instance = NULL;

FileActionsController *FileActionsController::getInstance()
{
    if (FileActionsController::instance == NULL)
        FileActionsController::instance = new FileActionsController();
    return FileActionsController::instance;
}

FileActionsController::FileActionsController()
    : loginInfo(DatabaseManager::getInstance()->getLoginInfo())
{

}

void FileActionsController::deleteNode(NodeInfoDTO *node)
{
    DeleteMessage *deleteMessage = new DeleteMessage(this->loginInfo, this);
    connect(deleteMessage, SIGNAL(nodeDeleted()), this, SIGNAL(actionFinished()));
    connect(deleteMessage, SIGNAL(nodeDeleted()), deleteMessage, SLOT(deleteLater()));
    connect(deleteMessage, SIGNAL(errorDeletingNode(QString)), this, SIGNAL(actionFinishedWithError(QString)));
    connect(deleteMessage, SIGNAL(errorDeletingNode(QString)), deleteMessage, SLOT(deleteLater()));
    deleteMessage->deleteNode(node->path);
}

void FileActionsController::publishNode(NodeInfoDTO *node, bool publish)
{
    PublishMessage *publishMessage = new PublishMessage(this->loginInfo, this);
    connect(publishMessage, SIGNAL(nodePublished()), this, SIGNAL(actionFinished()));
    connect(publishMessage, SIGNAL(nodePublished()), publishMessage, SLOT(deleteLater()));
    connect(publishMessage, SIGNAL(errorPublishingNode(QString)), this, SIGNAL(actionFinishedWithError(QString)));
    connect(publishMessage, SIGNAL(errorPublishingNode(QString)), publishMessage, SLOT(deleteLater()));
    publishMessage->publishNode(node->path, publish);
}

void FileActionsController::shareLink(NodeInfoDTO *node)
{
    if (!node->isPublic) {
        emit this->actionFinishedWithError(tr("Error sharing the public link"));
        return;
    }

#ifdef Q_OS_ANDROID
    AndroidUtils::shareLink(node->publicUrl);
#else
    QClipboard *clipboard = qApp->clipboard();
    clipboard->setText(node->publicUrl);
#endif
}

#ifdef Q_OS_ANDROID
NodeInfoDTO *renameAuxNode;
void FileActionsController::renameCallback(JNIEnv */*env*/, jobject /*object*/, jstring result)
{
    QString newName = QAndroidJniObject(result).toString();
    if (!newName.isEmpty())
        emit FileActionsController::getInstance()->renameOnMainThread(renameAuxNode, newName);
}
#endif

void FileActionsController::rename(NodeInfoDTO *node)
{
#ifdef Q_OS_ANDROID
    renameAuxNode = node;
    connect(this, SIGNAL(renameOnMainThread(NodeInfoDTO*,QString)), this, SLOT(renameAux(NodeInfoDTO*,QString)));
    AndroidUtils::showInputDialog(tr("Rename"), "", node->name, tr("Rename file"), tr("Cancel"),
            (void *)FileActionsController::renameCallback);
#else
    bool ok;
    QString newName = QInputDialog::getText(NULL, tr("Rename"), "", QLineEdit::Normal, node->name, &ok);
    if (ok && !newName.isEmpty())
        FileActionsController::renameAux(node, newName);
#endif
}

void FileActionsController::renameAux(NodeInfoDTO *node, const QString &newName)
{
    RenameMessage *renameMessage = new RenameMessage(DatabaseManager::getInstance()->getLoginInfo());
    connect(renameMessage, SIGNAL(nodeRenamed()), FileActionsController::instance, SIGNAL(actionFinished()));
    connect(renameMessage, SIGNAL(nodeRenamed()), renameMessage, SLOT(deleteLater()));
    connect(renameMessage, SIGNAL(errorRenamingNode(QString)),
            FileActionsController::instance, SIGNAL(actionFinishedWithError(QString)));
    connect(renameMessage, SIGNAL(errorRenamingNode(QString)), renameMessage, SLOT(deleteLater()));
    renameMessage->renameNode(node, newName);
}

#ifdef Q_OS_ANDROID
QString createFolderPahtAux;
void FileActionsController::createFolderCallback(JNIEnv */*env*/, jobject /*object*/, jstring result)
{
    QString folderName = QAndroidJniObject(result).toString();
    if (!folderName.isEmpty())
        emit FileActionsController::getInstance()->createFolderOnMainThread(createFolderPahtAux, folderName);
}
#endif

void FileActionsController::createFolder(const QString &path)
{
#ifdef Q_OS_ANDROID
    createFolderPahtAux = path;
    connect(this, SIGNAL(createFolderOnMainThread(QString, QString)), this, SLOT(createFolderAux(QString, QString)));
    AndroidUtils::showInputDialog(tr("Create folder"), "", tr("New folder"), tr("Create"), tr("Cancel"),
            (void *)FileActionsController::createFolderCallback);
#else
    bool ok;
    QString folderName = QInputDialog::getText(NULL, tr("Create folder"), "", QLineEdit::Normal, tr("New folder"), &ok);
    if (ok && !folderName.isEmpty())
        FileActionsController::createFolderAux(path, folderName);
#endif
}

void FileActionsController::createFolderAux(const QString &path, const QString &folderName)
{
    CreateFolderMessage *folderMessage = new CreateFolderMessage(DatabaseManager::getInstance()->getLoginInfo());
    connect(folderMessage, SIGNAL(folderCreated()), FileActionsController::instance, SIGNAL(actionFinished()));
    connect(folderMessage, SIGNAL(folderCreated()), folderMessage, SLOT(deleteLater()));
    connect(folderMessage, SIGNAL(errorCreatingFolder(QString)),
            FileActionsController::instance, SIGNAL(actionFinishedWithError(QString)));
    connect(folderMessage, SIGNAL(errorCreatingFolder(QString)), folderMessage, SLOT(deleteLater()));
    folderMessage->createFolder(path + "/" + folderName);
}
