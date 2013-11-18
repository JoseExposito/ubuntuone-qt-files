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

    NodeInfoDTO(NodeType type, const QString &path, const QString &name)
        : type(type),
          path(path),
          name(name),
          isPublic(false),
          publicUrl(""),
          size(-1),
          lastModified("") {}

    NodeType type; /// Volume root (Ubuntu One), volume, file or directory
    QString path; /// Complete path: /~/Ubuntu One/file.txt
    QString name; /// Human readable file name: file.txt

    // Only for type FILE
    bool isPublic; /// If the file is public or not
    QString publicUrl; /// If the file is public, the public URL
    qint64 size; /// File size in bytes
    QString lastModified; /// DD/MM/YYYY
};


#endif // NODEINFODTO_H
