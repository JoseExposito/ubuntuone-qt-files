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
#ifndef LOGININFODAO_H
#define LOGININFODAO_H

#include "AbstractDAO.h"
class LoginInfoDTO;

/**
 * The LoginInfoDAO class manages the "login_info_table" table of the database.
 */
class LoginInfoDAO : public AbstractDAO
{
    Q_OBJECT

public:

    LoginInfoDAO(QSqlDatabase *db, QObject *parent = 0);

    virtual void createTableIfNotExists() const;

    void setLoginInfo(LoginInfoDTO *loginInfo);
    LoginInfoDTO *getLoginInfo();

};

#endif // LOGININFODAO_H
