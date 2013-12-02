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
#include "NodeListDAO.h"
#include <QtCore>
#include <QtSql>

namespace
{
    static const QString NODES_TABLE          = "nodes_table";
    static const QString PARENT_PATH_COLUMN   = "parent_path";
    static const QString TYPE_COLUMN          = "type";
    static const QString PATH_COLUMN          = "path";
    static const QString CONTENT_PATH_COLUMN  = "content_path";
    static const QString NAME_COLUMN          = "name";
    static const QString IS_PUBLIC_COLUMN     = "is_public";
    static const QString PUBLIC_URL_COLUMN    = "public_url";
    static const QString SIZE_COLUMN          = "size";
    static const QString LAST_MODIFIED_COLUMN = "last_modified";
    static const QString HASH_COLUMN          = "hash";
}

NodeListDAO::NodeListDAO(QSqlDatabase *db, QObject *parent)
    : AbstractDAO(db, parent)
{

}

void NodeListDAO::createTableIfNotExists() const
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS " + NODES_TABLE + " ("
            + PARENT_PATH_COLUMN +" TEXT, "
            + TYPE_COLUMN + " INTEGER, "
            + PATH_COLUMN +" TEXT, "
            + CONTENT_PATH_COLUMN +" TEXT, "
            + NAME_COLUMN + " TEXT, "
            + IS_PUBLIC_COLUMN + " INTEGER, "
            + PUBLIC_URL_COLUMN + " TEXT, "
            + SIZE_COLUMN + " INTEGER, "
            + LAST_MODIFIED_COLUMN + " TEXT, "
            + HASH_COLUMN + " TEXT)")) {
        this->printQueryError(query);
    }
}

void NodeListDAO::setNodeList(const QString &parentPath, QList<NodeInfoDTO *> *nodeList)
{
    // Remove all the old nodes associated with the parent path
    QSqlQuery query;
    if (!query.exec("DELETE FROM " + NODES_TABLE + " WHERE " + PARENT_PATH_COLUMN + " = \"" + parentPath + "\"")) {
        this->printQueryError(query);
        return;
    }

    // Insert the new nodes
    for (int n=0; n<nodeList->count(); n++) {
        NodeInfoDTO *node = nodeList->at(n);
        if (!query.exec("INSERT INTO " + NODES_TABLE + " VALUES ("
                        + "\"" + parentPath + "\", "
                        + "\"" + QString::number(node->type) + "\", "
                        + "\"" + node->path + "\", "
                        + "\"" + node->contentPath + "\", "
                        + "\"" + node->name + "\", "
                        + "\"" + QString::number(node->isPublic) + "\", "
                        + "\"" + node->publicUrl + "\", "
                        + "\"" + QString::number(node->size) + "\", "
                        + "\"" + node->lastModified + "\", "
                        + "\"" + node->hash + "\")")) {
            this->printQueryError(query);
            return;
        }
    }
}

QList<NodeInfoDTO *> *NodeListDAO::getNodeList(const QString &parentPath)
{
    QSqlQuery query;
    if (!query.exec("SELECT " + TYPE_COLUMN + ", "
            + PATH_COLUMN + ", "
            + CONTENT_PATH_COLUMN + ", "
            + NAME_COLUMN + ", "
            + IS_PUBLIC_COLUMN + ", "
            + PUBLIC_URL_COLUMN + ", "
            + SIZE_COLUMN + ", "
            + LAST_MODIFIED_COLUMN + ", "
            + HASH_COLUMN
            + " FROM " + NODES_TABLE
            + " WHERE " + PARENT_PATH_COLUMN + " = \"" + parentPath + "\"")) {
        this->printQueryError(query);
        return NULL;
    }

    QList<NodeInfoDTO *> *nodeList = new QList<NodeInfoDTO *>();
    while (query.next()) {
        NodeInfoDTO *node = new NodeInfoDTO((NodeInfoDTO::NodeType)query.value(0).toInt(),
                query.value(1).toString(), query.value(2).toString(), query.value(3).toString());
        node->isPublic     = query.value(4).toBool();
        node->publicUrl    = query.value(5).toString();
        node->size         = query.value(6).toInt();
        node->lastModified = query.value(7).toString();
        node->hash         = query.value(8).toString();
        nodeList->append(node);
    }

    return nodeList;
}
