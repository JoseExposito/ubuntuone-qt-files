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
#ifndef DOWNLOADNODEMESSAGE_H
#define DOWNLOADNODEMESSAGE_H

#include "AbstractMessage.h"
class NodeInfoDTO;
class QNetworkReply;
class QFile;

/**
 * The DownloadNodeMessage class manages the comunication to download a file from the Ubuntu One server.
 *
 * DOCUMENTATION:
 * https://one.ubuntu.com/developer/files/store_files/cloud#get--api-file_storage-v1-(content_path)
 */
class DownloadNodeMessage : public AbstractMessage
{
    Q_OBJECT

public:

    DownloadNodeMessage(LoginInfoDTO *loginInfo, QObject *parent = 0);
    virtual ~DownloadNodeMessage();

    /**
     * Downloads the specified node saving it at the specified path.
     * @see nodeDownloaded()
     * @see downloadProgress()
     * @see errorDownloadingNode()
     */
    void downloadNode(NodeInfoDTO *node, const QString &savePath);

    /**
     * This method return the download URL for the specified node adding to it the OAuth autentication.
     * It is useful to download files using the native OS API.
     */
    QString getDownloadUrlWithCredentials(NodeInfoDTO *node);

signals:

    void nodeDownloaded();
    void downloadProgress(int progress);
    void errorDownloadingNode(const QString &errorDescription);

protected slots:

    virtual void replyFinished(QNetworkReply *reply);

private slots:

    void downloadProgress(qint64 bytesReceived, qint64 bytesTotal);
    void downloadReadyRead();

private:

    QNetworkReply *downloadReply;
    QFile *saveFile;

};

#endif // DOWNLOADNODEMESSAGE_H
