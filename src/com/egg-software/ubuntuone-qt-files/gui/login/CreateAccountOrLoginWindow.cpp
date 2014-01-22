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
#include "CreateAccountOrLoginWindow.h"
#include "MainWindow.h"
#include "Utils.h"
#include "LoginWindow.h"
#include "CreateAccountWindow.h"
#include <QtCore>
#include <QtQuick>

CreateAccountOrLoginWindow::CreateAccountOrLoginWindow()
    : QQuickView(MainWindow::getInstance()->getWindow())
{
    Utils::setGlobalProperties(this->rootContext());
    this->setSource(QUrl("qrc:/qml/CreateAccountOrLoginWindow.qml"));

    connect(this->rootObject(), SIGNAL(loginClicked()), this, SLOT(loginClicked()));
    connect(this->rootObject(), SIGNAL(createAccountClicked()), this, SLOT(createAccountClicked()));
    connect(this->rootObject(), SIGNAL(menuAbout()), this, SLOT(menuAbout()));
}

void CreateAccountOrLoginWindow::loginClicked()
{
    LoginWindow *loginWindow = new LoginWindow();
    MainWindow::getInstance()->push(loginWindow);
}

void CreateAccountOrLoginWindow::createAccountClicked()
{
    //CreateAccountWindow *createAccountWindow = new CreateAccountWindow();
    //MainWindow::getInstance()->push(createAccountWindow);
}

void CreateAccountOrLoginWindow::menuAbout()
{
    MainWindow::getInstance()->showAboutDialog();
}
