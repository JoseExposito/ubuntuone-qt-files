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
#ifndef FILEACTIONSCONTROLLER_H
#define FILEACTIONSCONTROLLER_H

#include <QtCore/QObject>
class LoginInfoDTO;

class FileActionsController : public QObject
{
    Q_OBJECT

public:

    FileActionsController(QObject *parent = 0);

    void deleteNode(const QString &path);
    void publishNode(const QString &path, bool publish);

signals:

    void actionFinished();
    void actionFinishedWithError(const QString &errorDescription);

private:

    LoginInfoDTO *loginInfo;

};

#endif // FILEACTIONSCONTROLLER_H
