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
#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H

#include <QtCore/QObject>

/**
 * Controller that facilitates the login process. Manages the network and database operations.
 */
class LoginController : public QObject
{
    Q_OBJECT

public:

    LoginController(QObject *parent = 0) : QObject(parent) {}

    /**
     * Starts the login process.
     * @see loginFinished()
     * @see loginError()
     */
    void login(const QString &username, const QString &password);

private slots:

    void loginMessageFinished(const QString &consumerKey, const QString &consumerSecret,
            const QString &token, const QString &tokenSecret);

signals:

    /**
     * Emitted when the login process ends without problems.
     */
    void loginFinished();

    /**
     * Emmited when an error happens during the login process.
     * @param errorDescription Human readable description of the problem.
     */
    void loginError(const QString &errorDescription);


};

#endif // LOGINCONTROLLER_H
