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
#include "LogoutController.h"
#include "MainWindow.h"
#include "CreateAccountOrLoginWindow.h"
#include "DatabaseManager.h"

void LogoutController::logout()
{
    // Delete the database
    DatabaseManager::getInstance()->deleteDatabase();

    // Show the first screen
    MainWindow::getInstance()->clear();
    //MainWindow::getInstance()->push(new CreateAccountOrLoginWindow());
}
