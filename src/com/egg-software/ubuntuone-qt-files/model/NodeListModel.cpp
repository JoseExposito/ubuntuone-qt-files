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
    static const int FILE_TYPE_VOLUME_ROLE    = Qt::UserRole + 1;
    static const int FILE_TYPE_FILE_ROLE      = Qt::UserRole + 2;
    static const int FILE_TYPE_DIRECTORY_ROLE = Qt::UserRole + 3;
    static const int FILE_PATH_ROLE           = Qt::UserRole + 4;
    static const int FILE_NAME_ROLE           = Qt::UserRole + 5;
    static const int IS_PUBLIC_ROLE           = Qt::UserRole + 6;
    static const int PUBLIC_URL_ROLE          = Qt::UserRole + 7;
    static const int FILE_SIZE_ROLE           = Qt::UserRole + 8;
    static const int LAST_MODIFIED_ROLE       = Qt::UserRole + 9;
    static const int FILE_ICON_ROLE           = Qt::UserRole + 10;
}

NodeListModel::NodeListModel(QObject *parent)
    : QAbstractListModel(parent),
      nodeList(NULL)
{

}

void NodeListModel::setNodeList(QList<NodeInfoDTO *> *nodeList)
{
    // Delete all the showed rows
    this->beginRemoveRows(QModelIndex(), 0, this->rowCount()-1);
    this->endRemoveRows();

    // Free and replace the node list
    if (this->nodeList != NULL) {
        for (int n=0; n<this->nodeList->count(); n++)
            delete this->nodeList->at(n);
    }
    delete this->nodeList;

    this->nodeList = nodeList;

    // Inset the new rows
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
    roles.insert(FILE_TYPE_VOLUME_ROLE, QByteArray("isVolume"));
    roles.insert(FILE_TYPE_FILE_ROLE, QByteArray("isFile"));
    roles.insert(FILE_TYPE_DIRECTORY_ROLE, QByteArray("isDirectory"));
    roles.insert(FILE_PATH_ROLE, QByteArray("filePath"));
    roles.insert(FILE_NAME_ROLE, QByteArray("fileName"));
    roles.insert(IS_PUBLIC_ROLE, QByteArray("isPublic"));
    roles.insert(PUBLIC_URL_ROLE, QByteArray("publicUrl"));
    roles.insert(FILE_SIZE_ROLE, QByteArray("fileSize"));
    roles.insert(LAST_MODIFIED_ROLE, QByteArray("lastModified"));
    roles.insert(FILE_ICON_ROLE, QByteArray("icon"));
    return roles;
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > this->nodeList->size()-1)
        return QVariant();

    NodeInfoDTO *nodeInfo = this->nodeList->at(index.row());
    switch (role) {
    case FILE_TYPE_VOLUME_ROLE:
        return nodeInfo->type == NodeInfoDTO::VOLUME || nodeInfo->type == NodeInfoDTO::VOLUME_ROOT;
    case FILE_TYPE_FILE_ROLE:
        return nodeInfo->type == NodeInfoDTO::FILE;
    case FILE_TYPE_DIRECTORY_ROLE:
        return nodeInfo->type == NodeInfoDTO::DIRECTORY;
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
        return this->humanReadableSize(nodeInfo->size);
    case LAST_MODIFIED_ROLE:
        return nodeInfo->lastModified.left(10);
    case FILE_ICON_ROLE:
        return this->fileIcon(nodeInfo->type, nodeInfo->name);
    default:
        return QVariant();
    }
}

QString NodeListModel::humanReadableSize(int size) const
{
    QStringList list;
    list << "KB" << "MB" << "GB" << "TB";

    QStringListIterator i(list);
    QString unit("bytes");

    while(size >= 1024 && i.hasNext()) {
        unit = i.next();
        size /= 1024;
    }

    return QString::number(size) + " " + unit;
}

QString NodeListModel::fileIcon(NodeInfoDTO::NodeType type, const QString &fileName) const
{
    if (type != NodeInfoDTO::FILE)
        return "qrc:/mimetype/folder.png";

    static QStringList imageExtension;
    imageExtension << "bmp" << "gif" << "jpg" << "jpeg" << "png" << "tif" << "tiff" << "svg";

    QString extension = QFileInfo(fileName).suffix();
    if (imageExtension.contains(extension.toLower()))
        return "qrc:/mimetype/image.png";
    else
        return "qrc:/mimetype/file.png";
}
