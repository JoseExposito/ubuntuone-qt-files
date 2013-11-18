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
    static const int FILE_TYPE_ROLE     = Qt::UserRole + 1;
    static const int FILE_PATH_ROLE     = Qt::UserRole + 2;
    static const int FILE_NAME_ROLE     = Qt::UserRole + 3;
    static const int IS_PUBLIC_ROLE     = Qt::UserRole + 4;
    static const int PUBLIC_URL_ROLE    = Qt::UserRole + 5;
    static const int FILE_SIZE_ROLE     = Qt::UserRole + 6;
    static const int LAST_MODIFIED_ROLE = Qt::UserRole + 7;
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
    roles.insert(FILE_TYPE_ROLE, QByteArray("fileType"));
    roles.insert(FILE_PATH_ROLE, QByteArray("filePath"));
    roles.insert(FILE_NAME_ROLE, QByteArray("fileName"));
    roles.insert(IS_PUBLIC_ROLE, QByteArray("isPublic"));
    roles.insert(PUBLIC_URL_ROLE, QByteArray("publicUrl"));
    roles.insert(FILE_SIZE_ROLE, QByteArray("fileSize"));
    roles.insert(LAST_MODIFIED_ROLE, QByteArray("lastModified"));
    return roles;
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > this->nodeList->size()-1)
        return QVariant();

    NodeInfoDTO *nodeInfo = this->nodeList->at(index.row());
    switch (role) {
    case FILE_TYPE_ROLE:
        return nodeInfo->type;
    case FILE_PATH_ROLE:
        return nodeInfo->path;
    case Qt::DisplayRole:
    case FILE_NAME_ROLE:
        return nodeInfo->name;
    case IS_PUBLIC_ROLE:
        return nodeInfo->isPublic;
    case PUBLIC_URL_ROLE:
        return nodeInfo->publicUrl;
    case FILE_SIZE_ROLE:
        return nodeInfo->size;
    case LAST_MODIFIED_ROLE:
        return nodeInfo->lastModified;
    default:
        return QVariant();
    }
}
