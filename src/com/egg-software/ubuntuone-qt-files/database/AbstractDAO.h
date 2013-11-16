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
#ifndef ABSTRACTDAO_H
#define ABSTRACTDAO_H

#include <QtCore/QObject>
#include <QtSql/QSqlQuery>
class QSqlDatabase;

/**
 * The AbstractDAO class must be used as parent of all DAO classes.
 */
class AbstractDAO : public QObject
{
    Q_OBJECT

public:

    /**
     * Basic contructor.
     * @param db Connection to the database.
     * @param parent Parent of the class.
     */
    AbstractDAO(QSqlDatabase *db, QObject *parent = 0);

    /**
     * The children must implement this method to create the table that they manages.
     */
    virtual void createTableIfNotExists() const = 0;

    /**
     * Traces the error in with format.
     */
    void printQueryError(const QSqlQuery &query) const;

protected:

    QSqlDatabase *db;

};

#endif // ABSTRACTDAO_H
