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
#ifndef CREATEACCOUNTWINDOW_H
#define CREATEACCOUNTWINDOW_H

#include <QtQuick/QQuickView>

/**
 * Screen that allows to the user to create an account the first time.
 */
class CreateAccountWindow : public QQuickView
{
    Q_OBJECT

public:

    CreateAccountWindow();

private slots:

    void createAccountButtonPressed(const QString &fullName, const QString &email, const QString &password);
    void termsOfserviceButtonPressed();
    void menuAbout();

};

#endif // CREATEACCOUNTWINDOW_H
