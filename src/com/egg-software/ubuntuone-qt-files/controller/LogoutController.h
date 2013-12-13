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
#ifndef LOGOUTCONTROLLER_H
#define LOGOUTCONTROLLER_H

#include <QtCore/QObject>

/**
 * The LogoutController class manages a correct log out: Showing the first screen and deleting the database.
 */
class LogoutController : public QObject
{
    Q_OBJECT

public:

    static void logout();

};

#endif // LOGOUTCONTROLLER_H
