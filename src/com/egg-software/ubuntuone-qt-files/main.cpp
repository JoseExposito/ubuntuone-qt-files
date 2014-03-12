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
#include <QtWidgets/QApplication>
#include <QtCore/QTranslator>
#include "DatabaseManager.h"
#include "MainWindow.h"
#include "CreateAccountOrLoginWindow.h"
#include "NodeListController.h"
#include "NodeListView.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Load translations
    QString locale = QLocale::system().name().left(2);
    QTranslator translator;
    translator.load(":/translations/" + locale + ".qm");
    app.installTranslator(&translator);

    // Show the volumes or the create account or login screen
    DatabaseManager *db = DatabaseManager::getInstance();
    MainWindow *mainWindow = MainWindow::getInstance();

    QQuickItem *initialView = (db->getLoginInfo() == NULL)
            ? (new CreateAccountOrLoginWindow())->getView()
            : NodeListController::getInstance()->createView(NodeListController::ROOT_PATH)->getView();

    mainWindow->push(initialView);
    mainWindow->show();

    int returnCode = app.exec();

    // Free memory and exit
    db->closeDatabase();
    return returnCode;
}
