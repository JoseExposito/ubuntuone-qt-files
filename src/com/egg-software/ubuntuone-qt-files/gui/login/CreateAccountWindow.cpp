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
#include "CreateAccountWindow.h"
#include "MainWindow.h"
#include "Utils.h"
#include <QtCore>
#include <QtQuick>
#include <QtGui/QDesktopServices>

CreateAccountWindow::CreateAccountWindow()
    : QQuickView(MainWindow::getInstance()->getWindow())
{
    Utils::setGlobalProperties(this->rootContext());
    this->setSource(QUrl("qrc:/qml/CreateAccountWindow.qml"));

    connect(this->rootObject(), SIGNAL(createAccount(QString,QString,QString)),
            this, SLOT(createAccountButtonPressed(QString,QString,QString)));
    connect(this->rootObject(), SIGNAL(termsOfservice()), this, SLOT(termsOfserviceButtonPressed()));
    connect(this->rootObject(), SIGNAL(menuAbout()), this, SLOT(menuAbout()));
}

void CreateAccountWindow::createAccountButtonPressed(const QString &fullName, const QString &email,
    const QString &password)
{

}

void CreateAccountWindow::termsOfserviceButtonPressed()
{
    QDesktopServices::openUrl(QUrl("http://www.ubuntu.com/legal/"));
}

void CreateAccountWindow::menuAbout()
{
    MainWindow::getInstance()->showAboutDialog();
}
