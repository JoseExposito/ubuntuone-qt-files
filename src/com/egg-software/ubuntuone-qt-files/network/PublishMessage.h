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
#ifndef PUBLISHMESSAGE_H
#define PUBLISHMESSAGE_H

#include "AbstractMessage.h"

/**
 * The PublishMessage allows to publish or unpublish the specified node. The node MUST be a file.
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#put--api-file_storage-v1-(volume)-(path)
 */
class PublishMessage : public AbstractMessage
{
    Q_OBJECT

public:

    PublishMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~PublishMessage();

    /**
     * Publish or unpublish the specified node.
     * @see nodePublished()
     * @see errorPublishingNode()
     */
    void publishNode(const QString &path, bool publish);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

signals:

    /**
     * Emmited when the node is correctly published or unpublished.
     */
    void nodePublished();

    /**
     * Emmited when an error happens publishing or publishing the node.
     * @param errorDescription Human readable description of the problem.
     */
    void errorPublishingNode(const QString &errorDescription);


private:

    QNetworkReply *publishReply;
    bool publishing;

};

#endif // PUBLISHMESSAGE_H
