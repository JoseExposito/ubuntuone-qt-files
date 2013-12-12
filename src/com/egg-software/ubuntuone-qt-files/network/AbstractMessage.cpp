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
#include <QtCore>
#include <QtNetwork>
#include <liboauthcpp/liboauthcpp.h>

AbstractMessage::AbstractMessage(LoginInfoDTO *loginInfo, QObject *parent)
    : QObject(parent),
      loginInfo(loginInfo),
      networkAccessManager(new QNetworkAccessManager(this))
{
    connect(this->networkAccessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

AbstractMessage::~AbstractMessage()
{

}

QNetworkReply *AbstractMessage::oauthGetRequest(const QString &url)
{
    OAuth::Consumer consumer(this->loginInfo->consumerKey.toStdString(), this->loginInfo->consumerSecret.toStdString());
    OAuth::Token token(this->loginInfo->token.toStdString(), this->loginInfo->tokenSecret.toStdString());
    OAuth::Client oauth(&consumer, &token);
    QString oauthParameters = QString::fromStdString(oauth.getURLQueryString(OAuth::Http::Get, url.toStdString()));
    QString baseUrl = QUrl(url).toString(QUrl::RemoveQuery);
    return this->networkAccessManager->get(QNetworkRequest(baseUrl + "?" + oauthParameters));
}

QNetworkReply *AbstractMessage::oauthPutRequest(const QString &url, const QByteArray &data)
{
    OAuth::Consumer consumer(this->loginInfo->consumerKey.toStdString(), this->loginInfo->consumerSecret.toStdString());
    OAuth::Token token(this->loginInfo->token.toStdString(), this->loginInfo->tokenSecret.toStdString());
    OAuth::Client oauth(&consumer, &token);
    QString oauthParameters = QString::fromStdString(oauth.getURLQueryString(OAuth::Http::Put, url.toStdString()));
    QString baseUrl = QUrl(url).toString(QUrl::RemoveQuery);
    return this->networkAccessManager->put(QNetworkRequest(baseUrl + "?" + oauthParameters), data);
}

QNetworkReply *AbstractMessage::oauthDeleteRequest(const QString &url)
{
    OAuth::Consumer consumer(this->loginInfo->consumerKey.toStdString(), this->loginInfo->consumerSecret.toStdString());
    OAuth::Token token(this->loginInfo->token.toStdString(), this->loginInfo->tokenSecret.toStdString());
    OAuth::Client oauth(&consumer, &token);
    QString oauthParameters = QString::fromStdString(oauth.getURLQueryString(OAuth::Http::Delete, url.toStdString()));
    QString baseUrl = QUrl(url).toString(QUrl::RemoveQuery);
    return this->networkAccessManager->deleteResource(QNetworkRequest(baseUrl + "?" + oauthParameters));
}

QString AbstractMessage::toPercentEncoding(const QString &url)
{
    return QUrl::toPercentEncoding(url).replace("%2F", "/").replace("%5B", "[").replace("%5D", "]");
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
