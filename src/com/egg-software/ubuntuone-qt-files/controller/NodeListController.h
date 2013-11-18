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
#ifndef NODELISTCONTROLLER_H
#define NODELISTCONTROLLER_H

#include <QtCore/QObject>
#include <QtCore/QList>
#include "NodeInfoDTO.h"
class NodeListView;
class NodeListModel;

/**
 * The NodeListController class creates a FileListView class with the required NodeListModel, using offline data if
 * available, and updates the model and the cache asking for the last changes to the Ubuntu One server.
 */
class NodeListController : public QObject
{
    Q_OBJECT

public:

    NodeListController(QObject *parent = 0);

    /**
     * Creates a view to visualize the specified path.
     * IMPORTANT: Free the view after use it.
     */
    NodeListView *createView(const QString &path);

    /**
     * The Ubuntu One root path is "/~/". It is used to list the volumes.
     */
    static const QString ROOT_PATH;

private slots:

    void nodeListReceived(QList<NodeInfoDTO *> *nodeList);
    void errorGettingNodeList(const QString &errorDescription);

private:

    /**
     * Model attached to the view returned in createView(). It is stored to be able to update it when the data from the
     * Uuntu One server is returned.
     */
    NodeListModel *nodeListModel;

};

#endif // NODELISTCONTROLLER_H
