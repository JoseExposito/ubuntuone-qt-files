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
#include "PublishMessage.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString PUBLISH_URL = "https://one.ubuntu.com/api/file_storage/v1";
}

PublishMessage::PublishMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : AbstractMessage(loginInfo, parent),
      publishReply(NULL)
{

}
PublishMessage::~PublishMessage()
{
    delete this->publishReply;
}

void PublishMessage::publishNode(const QString &path, bool publish)
{
    qDebug() << "[+] " << (publish ? "PUBLISHING" : "UNPUBLISHING") << " FILE:";
    this->publishing = publish;
    QString url = PUBLISH_URL + this->toPercentEncoding(path);
    QString json = QString() + "{ \"is_public\": " + (publish ? "true" : "false") + " }";

    qDebug() << "\t Path: " << path;
    qDebug() << "\t URL: "  << url;
    this->printJson(json);

    this->publishReply = this->oauthPutRequest(url, json.toUtf8());
}

void PublishMessage::replyFinished(QNetworkReply *reply)
{
    if (reply == this->publishReply) {
        if (this->publishReply->error() == QNetworkReply::NoError) {
            qDebug() << "\t Node correctly published or unpublished";
            emit this->nodePublished();
        } else {
            qDebug() << QString() + "\t Error " + (this->publishing ? "publishing" : "unpublishing") + " node: "
                    << this->publishReply->errorString();
            emit this->errorPublishingNode(this->publishing
                    ? tr("Error publishing file")
                    : tr("Error unpublishing file"));
        }
    }
}
