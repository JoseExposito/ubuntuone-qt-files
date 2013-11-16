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
#include "LoginInfoDAO.h"
#include "LoginInfoDTO.h"
#include <QtCore>
#include <QtSql>

namespace
{
    static const QString LOGIN_INFO_TABLE       = "login_info_table";
    static const QString ID_COLUMN              = "id";
    static const QString CONSUMER_KEY_COLUMN    = "consumer_key";
    static const QString CONSUMER_SECRET_COLUMN = "consumer_secret";
    static const QString TOKEN_COLUMN           = "token";
    static const QString TOKEN_SECRET_COLUMN    = "token_secret";
    static const QString SINGLE_LOGIN_INFO_ID   = "1";
}

LoginInfoDAO::LoginInfoDAO(QSqlDatabase *db, QObject *parent)
    : AbstractDAO(db, parent)
{

}

void LoginInfoDAO::createTableIfNotExists() const
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS " + LOGIN_INFO_TABLE + " ("
            + ID_COLUMN +" INTEGER PRIMARY KEY, "
            + CONSUMER_KEY_COLUMN + " TEXT, "
            + CONSUMER_SECRET_COLUMN + " TEXT, "
            + TOKEN_COLUMN + " TEXT, "
            + TOKEN_SECRET_COLUMN + " TEXT)")) {
        this->printQueryError(query);
    }
}

void LoginInfoDAO::setLoginInfo(LoginInfoDTO *loginInfo)
{
    QSqlQuery query;
    if (!query.exec("INSERT OR REPLACE INTO " + LOGIN_INFO_TABLE + " VALUES ("
            + SINGLE_LOGIN_INFO_ID + ", "
            + "\"" + loginInfo->consumerKey + "\", "
            + "\"" + loginInfo->consumerSecret + "\", "
            + "\"" + loginInfo->token + "\", "
            + "\"" + loginInfo->tokenSecret + "\")")) {
        this->printQueryError(query);
    }
}

LoginInfoDTO *LoginInfoDAO::getLoginInfo()
{
    QSqlQuery query;
    if (!query.exec("SELECT (" + CONSUMER_KEY_COLUMN + ", "
            + CONSUMER_SECRET_COLUMN + ", "
            + TOKEN_COLUMN + ", "
            + TOKEN_SECRET_COLUMN
            + ") FROM " + LOGIN_INFO_TABLE
            + " WHERE " + ID_COLUMN + " = " + SINGLE_LOGIN_INFO_ID)) {
        this->printQueryError(query);
        return NULL;
    } else {
        return new LoginInfoDTO(query.value(0).toString(),
                query.value(1).toString(),
                query.value(2).toString(),
                query.value(3).toString());
    }
}
