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
#include "PlatformFactory.h"
#include <QtCore>

namespace
{
    static const int INDEX_ROLE                      = Qt::UserRole + 1;

    static const int FILE_TYPE_VOLUME_ROLE           = Qt::UserRole + 2;
    static const int FILE_TYPE_FILE_ROLE             = Qt::UserRole + 3;
    static const int FILE_TYPE_DIRECTORY_ROLE        = Qt::UserRole + 4;

    static const int FILE_STATUS_DOWNLOADED_ROLE     = Qt::UserRole + 5;
    static const int FILE_STATUS_DOWNLOADING_ROLE    = Qt::UserRole + 6;

    static const int FILE_PATH_ROLE                  = Qt::UserRole + 7;
    static const int FILE_NAME_ROLE                  = Qt::UserRole + 8;
    static const int IS_PUBLIC_ROLE                  = Qt::UserRole + 9;
    static const int PUBLIC_URL_ROLE                 = Qt::UserRole + 10;
    static const int FILE_SIZE_ROLE                  = Qt::UserRole + 11;
    static const int LAST_MODIFIED_ROLE              = Qt::UserRole + 12;
    static const int FILE_ICON_ROLE                  = Qt::UserRole + 13;
    static const int FILE_DOWNLOAD_PROGRESS_ROLE     = Qt::UserRole + 14;
}

NodeListModel::NodeListModel(QObject *parent)
    : QAbstractListModel(parent),
      nodeList(new QList<NodeInfoDTO *>())
{

}

NodeListModel::~NodeListModel()
{
    if (this->nodeList != NULL) {
        for (int n=0; n<this->nodeList->count(); n++)
            delete this->nodeList->at(n);
        delete this->nodeList;
    }
}

void NodeListModel::setNodeList(QList<NodeInfoDTO *> *nodeList)
{
    // Delete all the showed rows
    if (this->rowCount() > 0) {
        this->beginRemoveRows(QModelIndex(), 0, this->rowCount()-1);
        this->endRemoveRows();
    }

    // Save the download status/progress in the new nodes
    for (int i=0; i<this->nodeList->count(); i++) {
        NodeInfoDTO *oldNode = this->nodeList->at(i);

        for (int j=0; j<nodeList->count(); j++) {
            NodeInfoDTO *newNode = nodeList->at(j);
            if (oldNode->path == newNode->path) {
                newNode->status = oldNode->status;
                newNode->downloadProgress = oldNode->downloadProgress;
                break;
            }
        }
    }

    // Free and replace the node list
    for (int n=0; n<this->nodeList->count(); n++)
        delete this->nodeList->at(n);
    delete this->nodeList;
    this->nodeList = nodeList;

    // Insert the new rows
    if (this->rowCount() > 0) {
        this->beginInsertRows(QModelIndex(), 0, this->nodeList->count()-1);
        this->endInsertRows();
    }
}

NodeInfoDTO *NodeListModel::getNode(int index)
{
    if (this->nodeList == NULL || index < 0 || index >= this->nodeList->count())
        return NULL;
    return this->nodeList->at(index);
}

void NodeListModel::refresNode(int index)
{
    emit this->dataChanged(this->createIndex(index, 0), this->createIndex(index, 0));
}

int NodeListModel::rowCount(const QModelIndex &/*parent*/) const
{
    return (this->nodeList != NULL) ? this->nodeList->count() : 0;
}

QHash<int, QByteArray> NodeListModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractListModel::roleNames();
    roles.insert(INDEX_ROLE, QByteArray("index"));

    roles.insert(FILE_TYPE_VOLUME_ROLE, QByteArray("isVolume"));
    roles.insert(FILE_TYPE_FILE_ROLE, QByteArray("isFile"));
    roles.insert(FILE_TYPE_DIRECTORY_ROLE, QByteArray("isDirectory"));

    roles.insert(FILE_STATUS_DOWNLOADED_ROLE, QByteArray("downloadedStatus"));
    roles.insert(FILE_STATUS_DOWNLOADING_ROLE, QByteArray("downloadingStatus"));

    roles.insert(FILE_PATH_ROLE, QByteArray("filePath"));
    roles.insert(FILE_NAME_ROLE, QByteArray("fileName"));
    roles.insert(IS_PUBLIC_ROLE, QByteArray("isPublic"));
    roles.insert(PUBLIC_URL_ROLE, QByteArray("publicUrl"));
    roles.insert(FILE_SIZE_ROLE, QByteArray("fileSize"));
    roles.insert(LAST_MODIFIED_ROLE, QByteArray("lastModified"));
    roles.insert(FILE_ICON_ROLE, QByteArray("icon"));
    roles.insert(FILE_DOWNLOAD_PROGRESS_ROLE, QByteArray("downloadProgress"));

    return roles;
}

QVariant NodeListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() > this->nodeList->size()-1)
        return QVariant();

    NodeInfoDTO *node = this->nodeList->at(index.row());
    switch (role) {
    case INDEX_ROLE:
        return index.row();

    case FILE_TYPE_VOLUME_ROLE:
        return (node->type == NodeInfoDTO::VOLUME) || (node->type == NodeInfoDTO::VOLUME_ROOT);
    case FILE_TYPE_FILE_ROLE:
        return (node->type == NodeInfoDTO::FILE);
    case FILE_TYPE_DIRECTORY_ROLE:
        return (node->type == NodeInfoDTO::DIRECTORY);

    case FILE_STATUS_DOWNLOADED_ROLE: {
        PlatformUtils *utils = PlatformFactory::createPlatformUtils();
        QString localPath = utils->getLocalPath(node->path);
        delete utils;
        return (node->type == NodeInfoDTO::FILE) && QFileInfo(localPath).exists();
    }
    case FILE_STATUS_DOWNLOADING_ROLE:
        return (node->status == NodeInfoDTO::DOWNLOADING);

    case FILE_PATH_ROLE:
        return node->path;
    case Qt::DisplayRole:
    case FILE_NAME_ROLE:
        return node->name;
    case IS_PUBLIC_ROLE:
        return node->isPublic;
    case PUBLIC_URL_ROLE:
        return node->publicUrl;
    case FILE_SIZE_ROLE:
        return this->humanReadableSize(node->size);
    case LAST_MODIFIED_ROLE:
        return node->lastModified.left(10);
    case FILE_ICON_ROLE:
        return this->fileIcon(node->type, node->name);
    case FILE_DOWNLOAD_PROGRESS_ROLE:
        return node->downloadProgress;

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
        return "qrc:/icons/folder.png";

    static QStringList imageExtension;
    imageExtension << "bmp" << "gif" << "jpg" << "jpeg" << "png" << "tif" << "tiff" << "svg";

    QString extension = QFileInfo(fileName).suffix();
    if (imageExtension.contains(extension.toLower()))
        return "qrc:/icons/image.png";
    else
        return "qrc:/icons/file.png";
}
