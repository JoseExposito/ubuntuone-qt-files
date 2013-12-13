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
#include "DeleteMessage.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString DELETE_URL = "https://one.ubuntu.com/api/file_storage/v1";
}

DeleteMessage::DeleteMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      deleteReply(NULL)
{

}

DeleteMessage::~DeleteMessage()
{
    delete this->deleteReply;
}

void DeleteMessage::deleteNode(const QString &path)
{
    qDebug() << "[+] DELETING NODE:";
    qDebug() << "\t Path: " << path;
    QString url = DELETE_URL + this->toPercentEncoding(path);
    this->deleteReply = this->oauthDeleteRequest(url);
}

void DeleteMessage::replyFinished(QNetworkReply *reply)
{
    AbstractMessage::replyFinished(reply);

    if (reply == this->deleteReply) {
        if (this->deleteReply->error() == QNetworkReply::NoError) {
            qDebug() << "\t Node correctly deleted";
            emit this->nodeDeleted();
        } else {
            qDebug() << "\t Error deleting node: " << this->deleteReply->errorString();
            emit this->errorDeletingNode(tr("Error deleting file or folder"));
        }
    }
}
