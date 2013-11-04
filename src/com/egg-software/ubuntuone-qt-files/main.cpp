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
#include <QApplication>
#include "MainWindow.h"
#include "CreateAccountOrLoginWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    /*QScreen *screen = app.screens().at(0);
    qDebug() << "#########################################################";
    qDebug() << app.screens().size();           // Desktop: 1   Android: 1
    qDebug() << screen->logicalDotsPerInch();  // Desktop: 72  Android: 144
    qDebug() << screen->logicalDotsPerInchY();  // Desktop: 72  Android: 144
    qDebug() << screen->physicalDotsPerInchX(); // Desktop: 136 Android: 319.79
    qDebug() << screen->physicalDotsPerInchY(); // Desktop: 135 Android: 319.932*/

    MainWindow mainWindow;

    CreateAccountOrLoginWindow createAccountOrLoginWindow(mainWindow.getWindow());
    mainWindow.push(&createAccountOrLoginWindow);
    mainWindow.show();

    return app.exec();
}
