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
#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QtCore/QObject>
class QNetworkAccessManager;
class QNetworkReply;
class O1;

/**
 * Class that allows to make login with user and password. The login process consist in two steps:
 *
 * First a token from Ubuntu SSO should be obtained. To get the token, a GET request to
 * "https://login.ubuntu.com/api/1.0/authentications" should be sent with the extra parameters "ws.op=authenticate" and
 * "token_name=Ubuntu One @ Human readable device name".
 *
 * The Ubuntu SSO server should ask with a 401 unauthorized response if the username or password is incorrect or with a
 * JSON like this if all is all right:
 *
 * {
 *     "updated": "2013-11-07 12:09:18.296069",
 *     "name": "Ubuntu One @ Human readable device name",
 *     "created": "2013-11-07 12:09:18.296063",
 *     "consumer_secret": "FwJHMKnQhxPwplOhfgaZbIFSPZGtCB",
 *     "token": "SWHBrnvekfTewHtmmhLBNGkyPxLdmPOtAjJiYNNgmccVtlvcnQ",
 *     "consumer_key": "LExxPE3",
 *     "token_secret": "HsoWKOaaEVfXsqpoTrlNEtaznuaMWTLtsNobTrexrokkOJOPaM"
 * }
 *
 * At this point the created token can be used to authenticate to other methods on the Ubuntu SSO, but not in the Ubuntu
 * One API, that is our objetive. To be able to acces to the Ubuntu One API with this token an OAuth GET request should
 * be sent to "https://one.ubuntu.com/oauth/sso-finished-so-get-tokens/USERNAME".
 *
 * After that request the obtained token can be used to interact with the Ubuntu One API without problems.
 *
 * Extra documentation:
 * https://one.ubuntu.com/developer/account_admin/auth/otherplatforms
 */
class LoginController : public QObject
{
    Q_OBJECT

public:

    /**
     * Initialices the LoginController with the specified username and password.
     */
    LoginController(const QString &username, const QString &password, QObject *parent = 0);
    virtual ~LoginController();

    /**
     * Starts the login process.
     * @see loginFinished()
     * @see loginError()
     */
    void login();

signals:

    /**
     * Emitted when the login process ends without problems. Gives the required information to use the Ubuntu One API.
     */
    void loginFinished(O1 *u1OAuth);

    /**
     * Emmited when an error happens during the login process.
     * @param errorDescription Human readable description of the problem.
     */
    void loginError(const QString &errorDescription);

private slots:

    void ssoReplyFinished(QNetworkReply *reply);

private:

    QNetworkAccessManager *networkAccessManager;

    QString username;
    QString password;

    QNetworkReply *ssoReply;
    QNetworkReply *pairTokenReply;
    O1 *u1OAuth;

};

#endif // LOGINCONTROLLER_H
