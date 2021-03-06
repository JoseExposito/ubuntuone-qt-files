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
#ifndef RENAMEMESSAGE_H
#define RENAMEMESSAGE_H

#include "AbstractMessage.h"
class NodeInfoDTO;

/**
 * The RenameMessage class allows to rename files or folders from the Ubuntu One server.
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#put--api-file_storage-v1-(volume)-(path)
 */
class RenameMessage : public AbstractMessage
{
    Q_OBJECT

public:

    RenameMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~RenameMessage();

    /**
     * Deletes the specified node.
     * @see nodeRenamed()
     * @see errorRenamingNode()
     */
    void renameNode(NodeInfoDTO *node, const QString &newName);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

signals:

    /**
     * Emmited when the node is correctly renamed.
     */
    void nodeRenamed();

    /**
     * Emmited when an error happens renaming the node.
     * @param errorDescription Human readable description of the problem.
     */
    void errorRenamingNode(const QString &errorDescription);

private:

    QNetworkReply *renameReply;

};

#endif // RENAMEMESSAGE_H
