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
#ifndef DOWNLOADSCONTROLLER_H
#define DOWNLOADSCONTROLLER_H

#include <QtCore/QObject>
class NodeInfoDTO;
class NodeListModel;

/**
 * The DownloadsController class manages the file download process, including hash checking to check if the downloaded
 * file is in the last version and local storage.
 */
class DownloadsController : public QObject
{
    Q_OBJECT

public:

    DownloadsController(QObject *parent = 0);

    /**
     * Donloads the specified node.
     */
    void downloadAndOpenNode(NodeListModel *model, int nodeIndex);

signals:

    void errorDownloadingNode(const QString &errorDescription);

private slots:

    void downloadProgress(int progress);
    void nodeDownloaded();

private:

    /**
     * Returns the local path for the specified node path. For example, the local path for the node
     * "/~/Ubuntu One/file.txt" will be "/storage/emulated/0/u1/Ubuntu One/file.txt" on Android.
     */
    QString getLocalPath(const QString &nodePath);

    NodeListModel *model;
    int nodeIndex;
    NodeInfoDTO *node;
    QString localPath;
};

#endif // DOWNLOADERCONTROLLER_H
