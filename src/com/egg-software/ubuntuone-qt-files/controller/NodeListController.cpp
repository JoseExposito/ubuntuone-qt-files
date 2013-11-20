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
#include <QtCore>
#include <QtQuick>

const QString NodeListController::ROOT_PATH = "/~/";

NodeListController::NodeListController(QObject *parent)
    : QObject(parent),
      nodeListModel(NULL)
{

}

NodeListView *NodeListController::createView(const QString &path)
{
    // Create the view and set the model
    this->nodeListModel = new NodeListModel();
    NodeListView *nodeListView = new NodeListView(this->nodeListModel);

    // TODO Load from the database if possible

    // Update the cached data
    LoginInfoDTO *loginInfo = DatabaseManager::getInstance()->getLoginInfo();
    if (path == ROOT_PATH) {
        VolumesMessage *volumesMessage = new VolumesMessage(loginInfo, this);
        connect(volumesMessage, SIGNAL(volumeList(QList<NodeInfoDTO*>*)),
                this, SLOT(nodeListReceived(QList<NodeInfoDTO*>*)));
        connect(volumesMessage, SIGNAL(errorGettingVolumes(QString)), this, SLOT(errorGettingNodeList(QString)));
        volumesMessage->getVolumes();

    } else {
        NodeChildrenMessage *childrenMessage = new NodeChildrenMessage(loginInfo, this);
        connect(childrenMessage, SIGNAL(childrenList(QList<NodeInfoDTO*>*)),
                this, SLOT(nodeListReceived(QList<NodeInfoDTO*>*)));
        connect(childrenMessage, SIGNAL(errorGettingChildren(QString)), this, SLOT(errorGettingNodeList(QString)));
        childrenMessage->getNodeChildren(path);
    }

    return nodeListView;
}

void NodeListController::nodeListReceived(QList<NodeInfoDTO *> *nodeList)
{
    this->nodeListModel->setNodeList(nodeList);

    // TODO Cache the received data
}

void NodeListController::errorGettingNodeList(const QString &errorDescription)
{
    qDebug() << "Error getting node list: " << errorDescription;
}
