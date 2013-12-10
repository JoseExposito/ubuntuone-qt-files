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
#ifndef NODEINFODTO_H
#define NODEINFODTO_H

#include <QtCore/QString>

/**
 * The NodeInfoDTO class is used to transfer all the required information about nodes.
 */
class NodeInfoDTO
{

public:

    enum NodeType
    {
        VOLUME,
        VOLUME_ROOT,
        FILE,
        DIRECTORY
    };

    enum Status
    {
        UNKNOW,
        NOT_DOWNLOADED,
        DOWNLOADED,
        DOWNLOADING
    };

    NodeInfoDTO(NodeType type, const QString &path, const QString &contentPath, const QString &name)
        : type(type),
          path(path),
          contentPath(contentPath),
          name(name),
          isPublic(false),
          publicUrl(""),
          size(-1),
          lastModified(""),
          hash(""),
          status(UNKNOW),
          downloadProgress(-1)
    {

    }

    NodeType type;       /// Volume root (Ubuntu One), volume, file or directory
    QString path;        /// Complete path: /~/Ubuntu One/file.txt
    QString contentPath; /// Path used to download the file: /content/~/Ubuntu One/file.txt
    QString name;        /// Human readable file name: file.txt

    // Only for type FILE
    bool isPublic;        /// If the file is public or not
    QString publicUrl;    /// If the file is public, the public URL
    int size;             /// File size in bytes
    QString lastModified; /// DD/MM/YYYY
    QString hash;         /// SHA1 hash, used to know if the local file is up to date
    Status status;        /// Status of the node
    int downloadProgress; /// If the status is DOWNLOADING, the download progress

};

#endif // NODEINFODTO_H
