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
#include "VersionDAO.h"
#include <QtCore>
#include <QtSql>

namespace
{
    static const QString VERSION_TABLE     = "version_table";
    static const QString ID_COLUMN         = "id";
    static const QString VERSION_COLUMN    = "version";
    static const QString SINGLE_VERSION_ID = "1";
}

VersionDAO::VersionDAO(QSqlDatabase *db, QObject *parent)
    : AbstractDAO(db, parent)
{

}

void VersionDAO::createTableIfNotExists() const
{
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS " + VERSION_TABLE + " ("
            + ID_COLUMN +" INTEGER PRIMARY KEY, "
            + VERSION_COLUMN + " TEXT)")) {
        this->printQueryError(query);
    }
}

void VersionDAO::setDatabaseVersion(const QString &databaseVersion)
{
    QSqlQuery query;
    if (!query.exec("INSERT OR REPLACE INTO " + VERSION_TABLE + " VALUES ("
            + SINGLE_VERSION_ID + ", "
            + "\"" + databaseVersion + "\")")) {
        this->printQueryError(query);
    }
}

QString VersionDAO::getDatabaseVersion()
{    
    QSqlQuery query;
    if (!query.exec("SELECT " + VERSION_COLUMN + " FROM " + VERSION_TABLE
            + " WHERE " + ID_COLUMN + " = " + SINGLE_VERSION_ID)) {
        this->printQueryError(query);
        return "";
    } else {
        return query.value(0).toString();
    }
}
