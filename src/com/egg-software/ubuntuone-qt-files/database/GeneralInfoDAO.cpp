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
#include "GeneralInfoDAO.h"
#include <QtCore>
#include <QtSql>

namespace
{
    static const QString GENERAL_DATA_TABLE = "general_info_table";
    static const QString ID_COLUMN          = "id";
    static const QString VALUE_COLUMN       = "value";
    static const int     DB_VERSION_ID      = 1;
    static const int     CONSUMER_KEY_ID    = 2;
    static const int     CONSUMER_SECRET_ID = 3;
    static const int     TOKEN_ID           = 4;
    static const int     TOKEN_SECRET_ID    = 5;
}

GeneralInfoDAO::GeneralInfoDAO(QSqlDatabase *db, QObject *parent)
    : QObject(parent),
      db(db)
{

}

void GeneralInfoDAO::createGeneralInfoTable()
{
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS " + GENERAL_DATA_TABLE + " (" + ID_COLUMN +" INTEGER PRIMARY KEY, "
            + VALUE_COLUMN + " TEXT)");
}

void GeneralInfoDAO::setDatabaseVersion(const QString &databaseVersion)
{
    this->insertOrReplaceValue(DB_VERSION_ID, databaseVersion);
}

QString GeneralInfoDAO::getDatabaseVersion()
{
    return this->selectValue(DB_VERSION_ID);
}

void GeneralInfoDAO::setConsumerKey(const QString &consumerKey)
{
    this->insertOrReplaceValue(CONSUMER_KEY_ID, consumerKey);
}

QString GeneralInfoDAO::getConsumerKey()
{
    return this->selectValue(CONSUMER_KEY_ID);
}

void GeneralInfoDAO::setConsumerSecret(const QString &consumerSecret)
{
    this->insertOrReplaceValue(CONSUMER_SECRET_ID, consumerSecret);
}

QString GeneralInfoDAO::getConsumerSecret()
{
    return this->selectValue(CONSUMER_SECRET_ID);
}

void GeneralInfoDAO::setToken(const QString &token)
{
    this->insertOrReplaceValue(TOKEN_ID, token);
}

QString GeneralInfoDAO::getToken()
{
    return this->selectValue(TOKEN_ID);
}

void GeneralInfoDAO::setTokenSecret(const QString &tokenSecret)
{
    this->insertOrReplaceValue(TOKEN_SECRET_ID, tokenSecret);
}

QString GeneralInfoDAO::getTokenSecret()
{
    return this->selectValue(TOKEN_SECRET_ID);
}

void GeneralInfoDAO::insertOrReplaceValue(int id, const QString &value)
{
    QString queryString = "INSERT OR REPLACE INTO " + GENERAL_DATA_TABLE + " VALUES ("
            + QString::number(id) + ", \"" + value + "\")";

    QSqlQuery query;
    if (!query.exec(queryString))
        qDebug() << "INVALID QUERY: " << queryString << "\nREASON: " << query.lastError();
}

QString GeneralInfoDAO::selectValue(int id)
{
    QString queryString = "SELECT " + VALUE_COLUMN + " FROM " + GENERAL_DATA_TABLE + " WHERE " + ID_COLUMN + " = "
            + QString::number(id);

    QSqlQuery query;
    if (!query.exec(queryString))
        qDebug() << "INVALID QUERY: " << queryString << "\nREASON: " << query.lastError();
    return query.value(0).toString();
}
