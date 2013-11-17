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
        DERECTORY
    };

    NodeInfoDTO(NodeType type, const QString &path)
        : type(type),
          path(path),
          isPublic(false),
          publicUrl("") {}

    NodeType type;
    QString path;

    // Only for type FILE
    bool isPublic;
    QString publicUrl;
};


#endif // NODEINFODTO_H
