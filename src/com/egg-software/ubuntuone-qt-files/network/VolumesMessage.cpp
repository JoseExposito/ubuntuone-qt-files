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
#include "VolumesMessage.h"
#include "o1.h"
#include "o1requestor.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString GET_VOLUMES_URL = "https://one.ubuntu.com/api/file_storage/v1/volumes";

    static const QString PATH_ID = "node_path";
    static const QString TYPE_ID = "type";
}

VolumesMessage::VolumesMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      volumesReply(NULL)
{

}
VolumesMessage::~VolumesMessage()
{
    delete this->volumesReply;
}

void VolumesMessage::getVolumes()
{
    qDebug() << "[+] GETTING VOLUME LIST:";
    this->volumesReply = this->oauthGetRequest(GET_VOLUMES_URL);
}

void VolumesMessage::replyFinished(QNetworkReply *reply)
{
    if (reply == this->volumesReply) {
        if (this->volumesReply->error() != QNetworkReply::NoError) {
            qDebug() << "\t Error receiving the volume list: " << this->volumesReply->errorString();
            emit this->errorGettingVolumes(tr("Error receiving the volume list"));
            return;
        }

        qDebug() << "\t Volume list received:";
        QByteArray replyContent = this->volumesReply->readAll();
        this->printJson(replyContent);

        QList<NodeInfoDTO *> *volumeList = new QList<NodeInfoDTO *>();

        QJsonDocument jsonDoc = QJsonDocument::fromJson(replyContent);
        QJsonArray volumes = jsonDoc.array();
        for (int n=0; n<volumes.count(); n++) {
            QJsonValue volume = volumes.at(n);
            NodeInfoDTO::NodeType nodeType = (volume.toObject().value(TYPE_ID).toString() == "root")
                    ? NodeInfoDTO::VOLUME_ROOT
                    : NodeInfoDTO::VOLUME;
            QString nodePath = volume.toObject().value(PATH_ID).toString();
            QString nodeName = QFileInfo(nodePath).fileName();
            NodeInfoDTO *nodeInfo = new NodeInfoDTO(nodeType, nodePath, nodeName);
            volumeList->append(nodeInfo);
        }

        emit this->volumeList(volumeList);
    }
}
