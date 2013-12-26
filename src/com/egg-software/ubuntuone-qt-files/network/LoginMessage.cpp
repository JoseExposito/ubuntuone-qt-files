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
#include "LoginMessage.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtNetwork>

namespace
{
    static const QString SSO_AUTHENTICATION_URL = "https://login.ubuntu.com/api/1.0/authentications";
    static const QString U1_PAIR_TOKEN_URL      = "https://one.ubuntu.com/oauth/sso-finished-so-get-tokens/";

    static const QString CONSUMER_KEY_ID    = "consumer_key";
    static const QString CONSUMER_SECRET_ID = "consumer_secret";
    static const QString TOKEN_ID           = "token";
    static const QString TOKEN_SECRET_ID    = "token_secret";
}

LoginMessage::LoginMessage(QObject *parent)
    : AbstractMessage(NULL, parent),
      ssoReply(NULL),
      pairTokenReply(NULL)
{

}

LoginMessage::~LoginMessage()
{
    delete this->ssoReply;
    delete this->pairTokenReply;
}

void LoginMessage::login(const QString &username, const QString &password)
{
    qDebug() << "[+] STARTING LOGIN PROCESS:";

    // Get the Ubuntu SSO token
    QString tokenName  = QUrl::toPercentEncoding("Ubuntu One @ " + QHostInfo::localHostName());
    QUrl ssoAuthenticationRequestUrl = SSO_AUTHENTICATION_URL + "?ws.op=authenticate&token_name=" + tokenName;
    ssoAuthenticationRequestUrl.setUserName(username);
    ssoAuthenticationRequestUrl.setPassword(password);

    qDebug() << "\t Getting Ubuntu SSO token";
    this->ssoReply = this->networkAccessManager->get(QNetworkRequest(ssoAuthenticationRequestUrl));
}

void LoginMessage::replyFinished(QNetworkReply *reply)
{
    // Not call the parent to avoid delete the database and send the user to the first screen when the username or
    // password is incrrect

    if (reply == this->ssoReply) {
        if (this->ssoReply->error() != QNetworkReply::NoError) {
            qDebug() << "\t Error receiving the Ubuntu SSO reply: " << this->ssoReply->errorString();
            emit this->loginError(tr("Invalid username or password"));
            return;
        }

        qDebug() << "\t Ubuntu SSO token received:";
        QByteArray replyContent = this->ssoReply->readAll();
        this->printJson(replyContent);

        QJsonDocument jsonDoc = QJsonDocument::fromJson(replyContent);
        if (jsonDoc.isNull() || !jsonDoc.isObject()
                || jsonDoc.object().find(CONSUMER_KEY_ID) == jsonDoc.object().end()
                || jsonDoc.object().find(CONSUMER_SECRET_ID) == jsonDoc.object().end()
                || jsonDoc.object().find(TOKEN_ID) == jsonDoc.object().end()
                || jsonDoc.object().find(TOKEN_SECRET_ID) == jsonDoc.object().end()) {
            qDebug() << "\t Error parsing the JSON Ubuntu SSO response";
            emit this->loginError(tr("Unexpected response received from the Ubuntu SSO server."
                                     "Please, try to login later"));
            return;
        }

        // Make the OAuth link request
        qDebug() << "\t Pairing Ubuntu SSO token with Ubuntu One at URL: " << U1_PAIR_TOKEN_URL;
        this->loginInfo = new LoginInfoDTO(jsonDoc.object().value(CONSUMER_KEY_ID).toString(),
                jsonDoc.object().value(CONSUMER_SECRET_ID).toString(),
                jsonDoc.object().value(TOKEN_ID).toString(),
                jsonDoc.object().value(TOKEN_SECRET_ID).toString());
        this->pairTokenReply = this->oauthGetRequest(U1_PAIR_TOKEN_URL);
    }

    if (reply == this->pairTokenReply) {
        if (this->pairTokenReply->error() != QNetworkReply::NoError) {
            qDebug() << "\t Error pairing the Ubuntu SSO token with the Ubuntu One server";
            delete this->loginInfo;
            this->loginInfo = NULL;
            emit this->loginError(tr("Error linking your Ubuntu SSO session with Ubuntu One. Please, try again later"));
        } else {
            qDebug() << "\t Ubuntu SSO correctly paired with the Ubuntu One server";
            qDebug() << "\t LOGIN SUCCESS :D";
            emit this->loginFinished(this->loginInfo);
        }
    }

}
