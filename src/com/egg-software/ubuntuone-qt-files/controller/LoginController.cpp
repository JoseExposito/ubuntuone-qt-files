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
#include "LoginController.h"
#include "LoginMessage.h"
#include "DatabaseManager.h"
#include <QtCore>

void LoginController::login(const QString &username, const QString &password)
{
    LoginMessage *loginMessage = new LoginMessage(username, password, this);
    connect(loginMessage, SIGNAL(loginError(QString)), this, SIGNAL(loginError(QString)));
    connect(loginMessage, SIGNAL(loginFinished(QString,QString,QString,QString)),
            this, SLOT(loginMessageFinished(QString,QString,QString,QString)));
    loginMessage->login();
}

void LoginController::loginMessageFinished(const QString &consumerKey, const QString &consumerSecret,
    const QString &token, const QString &tokenSecret)
{
    DatabaseManager *db = DatabaseManager::getInstance();
    db->setLoginInfo(consumerKey, consumerSecret, token, tokenSecret);
    emit this->loginFinished();
}
