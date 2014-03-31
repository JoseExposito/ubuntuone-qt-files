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
#include "NodeListView.h"
#include "MainWindow.h"
#include "Utils.h"
#include "NodeListModel.h"
#include "NodeListController.h"
#include "FileActionsController.h"
#include "DownloadsController.h"
#include <QtCore>
#include <QtQuick>

NodeListView::NodeListView(const QString &path)
    : BaseWindow("qrc:/qml/NodeListView.qml"),
      viewPath(path),
      fileAction(FileActionsController::getInstance()),
      model(new NodeListModel(this))
{
    this->context->setContextProperty("nodeListModel", this->model);
    this->context->setContextProperty("viewPath", this->viewPath);

    connect(this->view, SIGNAL(openFolder(int)), this, SLOT(openFolder(int)));
    connect(this->view, SIGNAL(openFile(int)), this, SLOT(openFile(int)));

    connect(this->view, SIGNAL(renameNode(int, QString)), this, SLOT(renameNode(int, QString)));
    connect(this->view, SIGNAL(deleteNode(int)), this, SLOT(deleteNode(int)));

    connect(this->view, SIGNAL(publishFile(int, bool)), this, SLOT(publishFile(int, bool)));
    connect(this->view, SIGNAL(copyPublicLink(int)), this, SLOT(copyPublicLink(int)));

    connect(this->view, SIGNAL(menuCreateFolder(QString)), this, SLOT(menuCreateFolder(QString)));
    connect(this->view, SIGNAL(menuRefresh()), this, SLOT(refreshView()));
    connect(this->view, SIGNAL(menuAbout()), this, SLOT(menuAbout()));

    connect(this->fileAction, SIGNAL(actionFinished()), this, SLOT(refreshView()));
    connect(this->fileAction, SIGNAL(actionFinishedWithError(QString)), this, SLOT(showError(QString)));
}

void NodeListView::setToolBarTitle(const QString &toolBarTitle)
{
    this->view->setProperty("toolBarTitle", toolBarTitle);
}

void NodeListView::openFolder(int nodeIndex)
{
    QString path = this->model->getNode(nodeIndex)->path;
    MainWindow::getInstance()->push(NodeListController::getInstance()->createView(path)->getView());
}

void NodeListView::openFile(int nodeIndex)
{    
    DownloadsController *downloader = new DownloadsController(this);
    downloader->downloadAndOpenNode(this->model, nodeIndex);
}

void NodeListView::renameNode(int nodeIndex, const QString &newName)
{
    NodeInfoDTO *node = this->model->getNode(nodeIndex);
    this->fileAction->rename(node, newName);
}

void NodeListView::deleteNode(int nodeIndex)
{
    NodeInfoDTO *node = this->model->getNode(nodeIndex);
    this->fileAction->deleteNode(node);
}

void NodeListView::publishFile(int nodeIndex, bool publish)
{
    NodeInfoDTO *node = this->model->getNode(nodeIndex);
    this->fileAction->publishNode(node, publish);
}

void NodeListView::copyPublicLink(int nodeIndex)
{
    NodeInfoDTO *node = this->model->getNode(nodeIndex);
    this->fileAction->shareLink(node);
}

void NodeListView::menuCreateFolder(const QString &folderName)
{
    this->fileAction->createFolder(this->viewPath, folderName);
}

void NodeListView::menuAbout()
{
    MainWindow::getInstance()->showAboutDialog();
}

void NodeListView::refreshView()
{
    NodeListController::getInstance()->refreshView(this->viewPath);
}

void NodeListView::showError(const QString &errorMessage)
{
    MainWindow::getInstance()->showToast(true, errorMessage);
}
