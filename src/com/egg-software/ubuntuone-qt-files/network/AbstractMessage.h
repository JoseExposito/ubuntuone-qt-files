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
#ifndef ABSTRACTMESSAGE_H
#define ABSTRACTMESSAGE_H

#include <QtCore/QObject>
#include <liboauthcpp/liboauthcpp.h>
class LoginInfoDTO;
class QNetworkAccessManager;
class QNetworkReply;

/**
 * The AbstractMessage class must be used as parent of all Message classes.
 */
class AbstractMessage : public QObject
{
    Q_OBJECT

public:

    /**
     * Basic contructor.
     * @param loginInfo Information to be able to do OAuth queries.
     * @param parent Parent of the class.
     */
    AbstractMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~AbstractMessage();

protected slots:

    /**
     * This slot is connected to the networkAccessManager finished() SIGNAL.
     * Must be implemented by the children.
     */
    virtual void replyFinished(QNetworkReply *reply);

protected:

    /**
     * Makes an OAuth GET/PUT/DELETE request with the consumer info and token stored in "loginInfo".
     */
    QNetworkReply *oauthGetRequest(const QString &url);
    QNetworkReply *oauthPutRequest(const QString &url, const QByteArray &data);
    QNetworkReply *oauthDeleteRequest(const QString &url);

    /**
     * Escapes the specified URL.
     */
    QString toPercentEncoding(const QString &url);

    /**
     * Prints a Json with format.
     */
    void printJson(const QString &json);

    LoginInfoDTO *loginInfo;
    QNetworkAccessManager *networkAccessManager;

private:

    /**
     * Auxiliar method used by oauthGetRequest(), oauthPutRequest() and oauthDeleteRequest() to generate the OAuth URL
     * with the authentication parameters in the query.
     */
    QString generateOAuthUrl(const OAuth::Http::RequestType requestType, const QString &url);

};

#endif // ABSTRACTMESSAGE_H
