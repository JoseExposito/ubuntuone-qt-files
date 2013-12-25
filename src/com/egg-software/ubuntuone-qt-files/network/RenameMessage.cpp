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
#include "RenameMessage.h"
#include "LoginInfoDTO.h"
#include "NodeInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString RENAME_URL = "https://one.ubuntu.com/api/file_storage/v1";
}

RenameMessage::RenameMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      renameReply(NULL)
{

}

RenameMessage::~RenameMessage()
{
    delete this->renameReply;
}

void RenameMessage::renameNode(NodeInfoDTO *node, const QString &newName)
{
    QString newPath = "/";
    QStringList paths = node->path.split("/");
    for (int n=3; n<paths.length()-1; n++)
        newPath += paths.at(n) + "/";
    newPath += newName;

    QString url = RENAME_URL + this->toPercentEncoding(node->path);
    QString json = QString() + "{ \"path\": \"" + newPath + "\" }";

    qDebug() << "[+] RENAMING NODE:";
    qDebug() << "\t Old path: " << node->path;
    qDebug() << "\t New path: " << newPath;
    qDebug() << "\t URL: " << url;
    this->printJson(json);

    this->renameReply = this->oauthPutRequest(url, json.toUtf8());
}

void RenameMessage::replyFinished(QNetworkReply *reply)
{
    AbstractMessage::replyFinished(reply);

    if (reply == this->renameReply) {
        if (this->renameReply->error() == QNetworkReply::NoError) {
            qDebug() << "\t Node correctly renamed";
            emit this->nodeRenamed();
        } else {
            qDebug() << "\t Error renaming node: " << this->renameReply->errorString();
            emit this->errorRenamingNode(tr("Error renaming file or folder"));
        }
    }
}
