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
#ifndef LOGININFODTO_H
#define LOGININFODTO_H

#include <QtCore/QString>

/**
 * The LoginInfoDTO class is used to transfer all the required information to login.
 */
class LoginInfoDTO
{

public:

    LoginInfoDTO(const QString &consumerKey, const QString &consumerSecret, const QString &token,
        const QString &tokenSecret)
        : consumerKey(consumerKey),
          consumerSecret(consumerSecret),
          token(token),
          tokenSecret(tokenSecret) {}

    QString consumerKey;
    QString consumerSecret;
    QString token;
    QString tokenSecret;
};

#endif // LOGININFODTO_H
