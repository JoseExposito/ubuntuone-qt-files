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
#ifndef VOLUMESMESSAGE_H
#define VOLUMESMESSAGE_H

#include "AbstractMessage.h"
#include <QtCore/QList>
#include "NodeInfoDTO.h"

/**
 * The VolumesMessage class is responsible for receive the volume list. A GET request to
 * "https://login.ubuntu.com/api/file_storage/v1/volumes" returns the volumes with this format:
 *
 * [
 *     {
 *         "resource_path": "/volumes/~/Ubuntu One",
 *         "when_created": "2012-08-25T15:34:49Z",
 *         "generation": 3921,
 *         "path": "~/Ubuntu One",
 *         "content_path": "/content/~/Ubuntu One",
 *         "type": "root",
 *         "node_path": "/~/Ubuntu One"
 *     },
 *     {
 *         "resource_path": "/volumes/~/Pictures - Nexus 4",
 *         "when_created": "2013-03-12T16:59:59Z",
 *         "generation": 10,
 *         "path": "~/Pictures - Nexus 4",
 *         "content_path": "/content/~/Pictures - Nexus 4",
 *         "type": "udf",
 *         "node_path": "/~/Pictures - Nexus 4"
 *     }
 * ]
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#get--api-file_storage-v1-volumes
 */
class VolumesMessage : public AbstractMessage
{
    Q_OBJECT

public:

    VolumesMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~VolumesMessage();

    /**
     * Returns the volume list.
     * @see volumeList()
     * @see errorGettingVolumes()
     */
    void getVolumes();

signals:

    /**
     * Returns the volume list.
     * IMPORTANT: Delete "volumeList" and its content after use it.
     */
    void volumeList(QList<NodeInfoDTO *> *volumeList);

    /**
     * Emmited when an error happens getting the volume list.
     * @param errorDescription Human readable description of the problem.
     */
    void errorGettingVolumes(const QString &errorDescription);

protected slots:

        virtual void replyFinished(QNetworkReply *reply);

private:

    QNetworkReply *volumesReply;

};

#endif // VOLUMESMESSAGE_H
