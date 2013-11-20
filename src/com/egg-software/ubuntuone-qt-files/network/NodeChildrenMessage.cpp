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
#include "NodeChildrenMessage.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString BASE_URL  = "https://one.ubuntu.com/api/file_storage/v1";
    static const QString FINAL_URL = "?include_children=true";

    static const QString CHILDREN_ID      = "children";
    static const QString TYPE_ID          = "kind";
    static const QString PATH_ID          = "resource_path";
    static const QString IS_PUBLIC_ID     = "is_public";
    static const QString PUBLIC_URL_ID    = "public_url";
    static const QString SIZE_ID          = "size";
    static const QString LAST_MODIFIED_ID = "when_changed";
}


NodeChildrenMessage::NodeChildrenMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      childrenReply(NULL)
{

}

NodeChildrenMessage::~NodeChildrenMessage()
{
    delete this->childrenReply;
}

void NodeChildrenMessage::getNodeChildren(const QString &path)
{
    qDebug() << "[+] GETTING CHILDREN FOR NODE: " << path;
    QString requestUrl = BASE_URL + QUrl::toPercentEncoding(path).replace("%2F", "/") + FINAL_URL;
    qDebug() << "\t Request URL: " << requestUrl;
    this->childrenReply = this->oauthGetRequest(requestUrl);
}

void NodeChildrenMessage::replyFinished(QNetworkReply *reply)
{
    if (reply == this->childrenReply) {
        if (this->childrenReply->error() != QNetworkReply::NoError) {
            qDebug() << "\t Error receiving the children list: " << this->childrenReply->errorString();
            emit this->errorGettingChildren(tr("Error loading folder"));
            return;
        }

        qDebug() << "\t Children list received:";
        QByteArray replyContent = this->childrenReply->readAll();
        this->printJson(replyContent);

        QList<NodeInfoDTO *> *childrenList = new QList<NodeInfoDTO *>();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(replyContent);

        if (jsonDoc.object().value(CHILDREN_ID).isNull()) {
            qDebug() << "\t Error parsing the message. Is the specified path a directory or a volume?";
            emit this->errorGettingChildren(tr("Error loading folder"));
            return;
        }

        QJsonArray children = jsonDoc.object().value(CHILDREN_ID).toArray();
        for (int n=0; n<children.count(); n++) {
            QJsonValue child = children.at(n);

            NodeInfoDTO::NodeType nodeType = (child.toObject().value(TYPE_ID).toString() == "directory")
                    ? NodeInfoDTO::DIRECTORY
                    : NodeInfoDTO::FILE;
            QString nodePath         = child.toObject().value(PATH_ID).toString();
            QString nodeName         = QFileInfo(nodePath).fileName();
            bool    nodeIsPublic     = false;
            QString nodePublicUrl    = "";
            int     nodeSize         = -1;
            QString nodeLastModified = "";

            if (nodeType == NodeInfoDTO::FILE) {
                    nodeIsPublic     = child.toObject().value(IS_PUBLIC_ID).toBool();
                    nodePublicUrl    = child.toObject().value(PUBLIC_URL_ID).toString();
                    nodeSize         = child.toObject().value(SIZE_ID).toInt();
                    nodeLastModified = child.toObject().value(LAST_MODIFIED_ID).toInt();
            }

            NodeInfoDTO *nodeInfo  = new NodeInfoDTO(nodeType, nodePath, nodeName);
            nodeInfo->isPublic     = nodeIsPublic;
            nodeInfo->publicUrl    = nodePublicUrl;
            nodeInfo->size         = nodeSize;
            nodeInfo->lastModified = nodeLastModified;
            childrenList->append(nodeInfo);
        }

        emit this->childrenList(childrenList);
    }
}
