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
#include "AbstractMessage.h"
#include "LoginInfoDTO.h"
#include "o1.h"
#include "o1requestor.h"
#include <QtCore>
#include <QtNetwork>

AbstractMessage::AbstractMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : QObject(parent),
      loginInfo(loginInfo),
      networkAccessManager(new QNetworkAccessManager(this))
{
    connect(this->networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    // HACK Check with Qt 5.2: http://stackoverflow.com/a/15707366/1204395
    QNetworkProxy proxy = this->networkAccessManager->proxy();
    proxy.setHostName(" ");
    this->networkAccessManager->setProxy(proxy);
}

AbstractMessage::~AbstractMessage()
{

}

QNetworkReply *AbstractMessage::oauthGetRequest(const QString &url)
{
    O1 *oauth = this->createO1();
    O1Requestor *requestor = new O1Requestor(this->networkAccessManager, oauth, this);
    return requestor->get(QNetworkRequest(url), QList<O1RequestParameter>());;
}

QNetworkReply *AbstractMessage::oauthPutRequest(const QString &url, const QByteArray &data)
{
    O1 *oauth = this->createO1();
    O1Requestor* requestor = new O1Requestor(this->networkAccessManager, oauth, this);
    return requestor->put(QNetworkRequest(url), QList<O1RequestParameter>(), data);
}

O1 *AbstractMessage::createO1()
{
    O1 *oauth = new O1(this);
    oauth->setClientId(loginInfo->consumerKey);
    oauth->setClientSecret(loginInfo->consumerSecret);
    oauth->setToken(loginInfo->token);
    oauth->setTokenSecret(loginInfo->tokenSecret);
    return oauth;
}

void AbstractMessage::printJson(const QString &json)
{
    if (json.isEmpty() || json.isNull())
        return;

    int tabLevel = 1;
    QString output = "";
    QString jsonWithLines = json;
    jsonWithLines = jsonWithLines.replace("\n", "")
            .replace("[", "[\n")
            .replace("{", "{\n")
            .replace("]", "]\n")
            .replace("}", "\n}")
            .replace(",", ",\n");
    QStringList lines = jsonWithLines.split("\n");

    for (int n=0; n<lines.count(); n++) {
        QString line = lines.at(n);

        if (line.contains("}") || line.contains("]"))
            tabLevel--;

        for (int t=0; t<tabLevel; t++)
            output += "\t";
        output += " " + line.trimmed();
        if (n != lines.count()-1)
            output += "\n";

        if (line.contains("{") || line.contains("["))
            tabLevel++;
    }

    qDebug() << qPrintable(output);
}
