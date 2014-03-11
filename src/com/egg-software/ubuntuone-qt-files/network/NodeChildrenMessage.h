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
#ifndef NODECHILDRENMESSAGE_H
#define NODECHILDRENMESSAGE_H

#include "AbstractMessage.h"
#include <QtCore/QList>
#include "NodeInfoDTO.h"

/**
 * The NodeChildrenMessage class returns all the files and folders stored in a directory or volume. A GET request to
 * "https://one.ubuntu.com/api/file_storage/v1/~/Ubuntu%20One?include_children=true" returns a list of files and folders
 * with this format:
 *
 * {
 *     "kind": "directory",
 *     "when_created": "2012-08-25T15:34:49Z",
 *     "generation": 0, "has_children": true,
 *     "content_path": "/content/~/Ubuntu One",
 *     "generation_created": 0,
 *     "parent_path": null,
 *     "is_live": true,
 *     "resource_path": "/~/Ubuntu One",
 *     "when_changed": "2013-11-14T17:39:01Z",
 *     "key": "sjeBHgNrQoiL6hksWulgQw",
 *     "path": "/",
 *     "volume_path": "/volumes/~/Ubuntu One",
 *     "children":
 *     [
 *         {
 *             "kind": "file",
 *             "public_url": "http://ubuntuone.com/6uWL2Ihxc4LdcasnLATDcr",
 *             "hash": "sha1:3dc233a66d9a902a34f78bd8d40409150847a536",
 *             "when_created": "2013-04-22T11:29:46Z", "generation": 3916,
 *             "content_path": "/content/~/Ubuntu One/Public file.txt",
 *             "generation_created": 3836,
 *             "parent_path": "/~/Ubuntu One",
 *             "is_live": true,
 *             "resource_path": "/~/Ubuntu One/Public file.txt",
 *             "when_changed": "2013-04-22T11:29:46Z",
 *             "key": "B12R09pcQz6s-EjMNbkbDw",
 *             "is_public": true,
 *             "path": "/Public file.txt",
 *             "volume_path": "/volumes/~/Ubuntu One",
 *             "size": 12658
 *         },
 *         {
 *             "kind": "file",
 *             "public_url": null,
 *             "hash": "sha1:f0c75afc88a55f5a39973031530bb29b3b204f48",
 *             "when_created": "2013-04-22T11:24:29Z",
 *             "generation": 3838,
 *             "content_path": "/content/~/Ubuntu One/Image Feb 19, 2013, 1:10:52 PM.jpeg",
 *             "generation_created": 3833,
 *             "parent_path": "/~/Ubuntu One",
 *             "is_live": true,
 *             "resource_path": "/~/Ubuntu One/Image Feb 19, 2013, 1:10:52 PM.jpeg",
 *             "when_changed": "2013-04-22T11:24:29Z",
 *             "key": "ikRLL9OLRMOuVQQ-b-RnUg",
 *             "is_public": false,
 *             "path": "/Image Feb 19, 2013, 1:10:52 PM.jpeg",
 *             "volume_path": "/volumes/~/Ubuntu One",
 *             "size": 450421
 *         },
 *         {
 *             "kind": "directory",
 *             "when_created": "2013-11-14T17:39:00Z",
 *             "generation": 3919,
 *             "has_children": true,
 *             "content_path": "/content/~/Ubuntu One/ExampleFolder",
 *             "generation_created": 3919,
 *             "parent_path": "/~/Ubuntu One",
 *             "is_live": true,
 *             "resource_path": "/~/Ubuntu One/ExampleFolder",
 *             "when_changed": "2013-11-14T17:39:14Z",
 *             "key": "GXJQrVmLRdu5h0azI5ivRQ",
 *             "path": "/ExampleFolder",
 *             "volume_path": "/volumes/~/Ubuntu One"
 *         }
 *     ]
 * }
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#get--api-file_storage-v1-(volume)-(path)
 */
class NodeChildrenMessage : public AbstractMessage
{
    Q_OBJECT

public:

    NodeChildrenMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~NodeChildrenMessage();

    /**
     * Returns the information about the specified directory.
     * @param path The path of the DIRECTORY or VOLUME!!!
     */
    void getNodeChildren(const QString &path);

signals:

    /**
     * Returns the children list.
     * @param path         Path of the "childrenList".
     * @param lastModified Last modification of the node "path".
     * @param childrenList The node list.
     * IMPORTANT: Delete "childrenList" and its content after use it.
     */
    void childrenList(const QString &path, const QString &lastModified, QList<NodeInfoDTO *> *childrenList);

    /**
     * Emmited when an error happens getting the children list.
     * @param errorDescription Human readable description of the problem.
     */
    void errorGettingChildren(const QString &path, const QString &errorDescription);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

private:

    QNetworkReply *childrenReply;
    QString path;

};

#endif // NODECHILDRENMESSAGE_H
