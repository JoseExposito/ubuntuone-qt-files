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
#ifndef GENERALINFODAO_H
#define GENERALINFODAO_H

#include <QtCore/QObject>
class QSqlDatabase;

/**
 * DAO to manage the general_info_table of the database.
 */
class GeneralInfoDAO : public QObject
{
    Q_OBJECT

public:

    GeneralInfoDAO(QSqlDatabase *db, QObject *parent = 0);

    /**
     * Getting and setting the database version. Used to migrate the database between versions.
     */
    void setDatabaseVersion(const QString &databaseVersion);
    QString getDatabaseVersion();

    /**
     * Creates the general_info_table if not exists.
     */
    void createGeneralInfoTable();

    /**
     * Getting and setting the OAuth required data to login and use the Ubuntu One API.
     */
    void setConsumerKey(const QString &consumerKey);
    QString getConsumerKey();

    void setConsumerSecret(const QString &consumerSecret);
    QString getConsumerSecret();

    void setToken(const QString &token);
    QString getToken();

    void setTokenSecret(const QString &tokenSecret);
    QString getTokenSecret();

private:

    void insertOrReplaceValue(int id, const QString &value);
    QString selectValue(int id);

    QSqlDatabase *db;

};

#endif // GENERALINFODAO_H
