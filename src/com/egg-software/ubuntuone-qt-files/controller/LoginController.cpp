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
#include "LoginInfoDTO.h"
#include "MainWindow.h"
#include <QtCore>

void LoginController::login(const QString &username, const QString &password)
{
    MainWindow::getInstance()->showLoadingSpinner(true, tr("Log in..."));
    LoginMessage *loginMessage = new LoginMessage(this);
    connect(loginMessage, SIGNAL(loginError(QString)), this, SLOT(loginMessageFinishedWithError(QString)));
    connect(loginMessage, SIGNAL(loginFinished(LoginInfoDTO*)), this, SLOT(loginMessageFinished(LoginInfoDTO*)));
    loginMessage->login(username, password);
}

void LoginController::loginMessageFinished(LoginInfoDTO *loginInfo)
{
    MainWindow::getInstance()->showLoadingSpinner(false);
    DatabaseManager::getInstance()->setLoginInfo(loginInfo);
    delete loginInfo;
    emit this->loginFinished();
}

void LoginController::loginMessageFinishedWithError(const QString &errorDescription)
{
    MainWindow::getInstance()->showLoadingSpinner(false);
    emit this->loginError(errorDescription);
}
