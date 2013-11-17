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
#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QtCore/QObject>
class QSqlDatabase;
class LoginInfoDTO;

/**
 * Facade to manage the database.
 *
 * IMPORTANT:
 * This is the only required class to manage the database. Use only this singleton outside of this "package".
 */
class DatabaseManager : public QObject
{
    Q_OBJECT

public:

    /**
     * Only method to get an instance of the class.
     * @return The single instance of the class.
     */
    static DatabaseManager *getInstance();

    /**
     * Getting/Setting in the database the required login info.
     */
    void setLoginInfo(LoginInfoDTO *loginInfo);
    LoginInfoDTO *getLoginInfo();

private:

    /**
     * Unique handler of the database.
     */
    QSqlDatabase *db;

    // Singleton
    static DatabaseManager *instance;
    DatabaseManager();
    DatabaseManager(const DatabaseManager &);
    const DatabaseManager &operator = (const DatabaseManager &);

};

#endif // DATABASEMANAGER_H
