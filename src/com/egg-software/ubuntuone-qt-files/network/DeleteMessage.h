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
#ifndef DELETEMESSAGE_H
#define DELETEMESSAGE_H

#include "AbstractMessage.h"

/**
 * The DeleteMessage class allows to delete files or folders from the Ubuntu One server.
 */
class DeleteMessage : public AbstractMessage
{
    Q_OBJECT

public:

    DeleteMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~DeleteMessage();

    /**
     * Deletes the specified node.
     * @see nodeDeleted()
     * @see errorDeletingNode()
     */
    void deleteNode(const QString &path);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

signals:

    /**
     * Emmited when the node is correctly deleted.
     */
    void nodeDeleted();

    /**
     * Emmited when an error happens getting the volume list.
     * @param errorDescription Human readable description of the problem.
     */
    void errorDeletingNode(const QString &errorDescription);

private:

    QNetworkReply *deleteReply;

};

#endif // DELETEMESSAGE_H
