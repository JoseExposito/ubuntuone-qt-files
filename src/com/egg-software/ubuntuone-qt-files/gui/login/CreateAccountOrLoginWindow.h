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
#ifndef CREATEACCOUNTORLOGINWINDOW_H
#define CREATEACCOUNTORLOGINWINDOW_H

#include "BaseWindow.h"
class LoginWindow;

/**
 * First screen of the application if the user is not already logged. It allows to the user to go to the "login" or
 * "create account" screens and shows a slideshow with the main features of the application.
 */
class CreateAccountOrLoginWindow : public BaseWindow
{
    Q_OBJECT

public:

    CreateAccountOrLoginWindow();
    virtual ~CreateAccountOrLoginWindow();

    inline QQuickItem *getView() { return this->view; }

private slots:

    void loginClicked();
    void createAccountClicked();
    void menuAbout();

private:

    LoginWindow *loginWindow;

};

#endif // CREATEACCOUNTORLOGINWINDOW_H
