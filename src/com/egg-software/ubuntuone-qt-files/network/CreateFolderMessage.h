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
#ifndef CREATEFOLDERMESSAGE_H
#define CREATEFOLDERMESSAGE_H

#include "AbstractMessage.h"

/**
 * The CreateFolderMessage class allows to create new folders in the Ubuntu One server.
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#put--api-file_storage-v1-(volume)-(path)
 */
class CreateFolderMessage : public AbstractMessage
{
    Q_OBJECT

public:

    CreateFolderMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~CreateFolderMessage();

    /**
     * Deletes the specified node.
     * @see nodeRenamed()
     * @see errorRenamingNode()
     */
    void createFolder(const QString &path);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

signals:

    /**
     * Emmited when the folder is correctly created.
     */
    void folderCreated();

    /**
     * Emmited when an error happens creating the folder.
     * @param errorDescription Human readable description of the problem.
     */
    void errorCreatingFolder(const QString &errorDescription);

private:

    QNetworkReply *createFolderReply;

};

#endif // CREATEFOLDERMESSAGE_H
