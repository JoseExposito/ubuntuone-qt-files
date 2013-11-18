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
#include "NodeListModel.h"
#include <QtCore>

namespace
{
    static const int FILE_NAME_ROLE = Qt::UserRole + 1;
    static const int FILE_SIZE_ROLE = Qt::UserRole + 2;
}

NodeListModel::NodeListModel(QObject *parent)
    : QAbstractListModel(parent),
      nodeList(NULL)
{

}

void NodeListModel::setNodeList(QList<NodeInfoDTO *> *nodeList)
{
    if (this->nodeList != NULL) {
        this->removeRows(0, this->nodeList->count()-1);
    }

    delete this->nodeList;
    this->nodeList = nodeList;
    this->beginInsertRows(QModelIndex(), 0, this->nodeList->count() - 1);
    this->endInsertRows();
}

int NodeListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return (this->nodeList != NULL) ? this->nodeList->count() : 0;
}

QHash<int, QByteArray> NodeListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(FILE_NAME_ROLE, QByteArray("fileName"));
    roles.insert(FILE_SIZE_ROLE, QByteArray("fileSize"));
    return roles;
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > this->nodeList->size()-1)
        return QVariant();

    NodeInfoDTO *nodeInfo = this->nodeList->at(index.row());
    switch (role) {
    case Qt::DisplayRole:
    case FILE_NAME_ROLE:
        return nodeInfo->path;
    case FILE_SIZE_ROLE:
        return QVariant(); // TODO
    default:
        return QVariant();
    }
}
