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
#include "NodeListController.h"
#include "NodeListView.h"
#include "NodeListModel.h"
#include "VolumesMessage.h"
#include "NodeChildrenMessage.h"
#include "LoginInfoDTO.h"
#include "DatabaseManager.h"
#include "MainWindow.h"
#include <QtCore>
#include <QtQuick>

const QString NodeListController::ROOT_PATH = "/~/";
NodeListController *NodeListController::instance = NULL;

NodeListController *NodeListController::getInstance()
{
    if (NodeListController::instance == NULL)
        NodeListController::instance = new NodeListController();
    return NodeListController::instance;
}

NodeListView *NodeListController::createView(const QString &path)
{
    NodeListView *nodeListView;

    // If the view exists, refresh it. Otherwise create it.
    if (this->views.contains(path)) {
        nodeListView = this->views.value(path);
    } else {
        nodeListView = new NodeListView(path);
        nodeListView->setToolBarTitle(path == ROOT_PATH ? "Ubuntu One" : QFileInfo(path).fileName());
    }

    // Add the view to the views hash
    this->views.insert(path, nodeListView);

    // Load the model from the database if possible
    QList<NodeInfoDTO *> *nodeList = DatabaseManager::getInstance()->getNodeList(path);
    if (nodeList == NULL || nodeList->isEmpty()) {
        MainWindow::getInstance()->showLoadingSpinner(true, tr("Loading..."));
    } else {
        nodeListView->getModel()->setNodeList(nodeList);
    }

    // Update the cached data
    LoginInfoDTO *loginInfo = DatabaseManager::getInstance()->getLoginInfo();
    if (path == ROOT_PATH) {
        VolumesMessage *volumesMessage = new VolumesMessage(loginInfo, this);

        connect(volumesMessage, SIGNAL(volumeList(QString,QList<NodeInfoDTO*>*)),
                this, SLOT(nodeListReceived(QString,QList<NodeInfoDTO*>*)));
        connect(volumesMessage, SIGNAL(errorGettingVolumes(QString,QString)),
                this, SLOT(errorGettingNodeList(QString,QString)));
        connect(volumesMessage, SIGNAL(volumeList(QString,QList<NodeInfoDTO*>*)), volumesMessage, SLOT(deleteLater()));
        connect(volumesMessage, SIGNAL(errorGettingVolumes(QString,QString)), volumesMessage, SLOT(deleteLater()));

        volumesMessage->getVolumes();

    } else {
        NodeChildrenMessage *childrenMessage = new NodeChildrenMessage(loginInfo, this);

        connect(childrenMessage, SIGNAL(childrenList(QString,QList<NodeInfoDTO*>*)),
                this, SLOT(nodeListReceived(QString,QList<NodeInfoDTO*>*)));
        connect(childrenMessage, SIGNAL(errorGettingChildren(QString,QString)),
                this, SLOT(errorGettingNodeList(QString,QString)));
        connect(childrenMessage, SIGNAL(childrenList(QString,QList<NodeInfoDTO*>*)),
                childrenMessage, SLOT(deleteLater()));
        connect(childrenMessage, SIGNAL(errorGettingChildren(QString,QString)), childrenMessage, SLOT(deleteLater()));

        childrenMessage->getNodeChildren(path);
    }

    return nodeListView;
}

void NodeListController::refreshView(const QString &path)
{
    this->createView(path);
}

void NodeListController::nodeListReceived(const QString &path, QList<NodeInfoDTO *> *nodeList)
{
    DatabaseManager::getInstance()->setNodeList(path, nodeList);

    NodeListView *view = this->views.value(path);
    view->getModel()->setNodeList(nodeList);

    MainWindow::getInstance()->showLoadingSpinner(false);
}

void NodeListController::errorGettingNodeList(const QString &path, const QString &errorDescription)
{
    MainWindow::getInstance()->showLoadingSpinner(false);
    qDebug() << "Error getting node list at " << path << ": " << errorDescription;
}
