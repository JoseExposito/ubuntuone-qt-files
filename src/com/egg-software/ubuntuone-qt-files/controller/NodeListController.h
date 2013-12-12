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
#include <QtCore/QHash>
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

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static NodeListController *getInstance();

    /**
     * Creates a view to visualize the specified path.
     */
    NodeListView *createView(const QString &path);

    /**
     * Refresh the node list of the specified path. The view must exists.
     */
    void refreshView(const QString &path);

    /**
     * The Ubuntu One root path is "/~/". It is used to list the volumes.
     */
    static const QString ROOT_PATH;

private slots:

    void nodeListReceived(const QString &path, QList<NodeInfoDTO *> *nodeList);
    void errorGettingNodeList(const QString &path, const QString &errorDescription);

private:

    /**
     * QHash that stores all the views identified by their path.
     */
    QHash<QString /*View path*/, NodeListView * /*The view*/> views;

    // Singleton
    static NodeListController *instance;
    NodeListController() {}
    NodeListController(const NodeListController &);
    const NodeListController &operator = (const NodeListController &);

};

#endif // NODELISTCONTROLLER_H
