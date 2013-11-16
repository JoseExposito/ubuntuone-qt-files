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

#include "AbstractDAO.h"

/**
 * The VersionDAO class manages the database version. This value is crucial to be able to update the database between
 * versions.
 */
class VersionDAO : public AbstractDAO
{
    Q_OBJECT

public:

    VersionDAO(QSqlDatabase *db, QObject *parent = 0);

    virtual void createTableIfNotExists() const;

    void setDatabaseVersion(const QString &databaseVersion);
    QString getDatabaseVersion();

};

#endif // GENERALINFODAO_H
