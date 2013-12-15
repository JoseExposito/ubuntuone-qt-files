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
#ifndef UTILS_H
#define UTILS_H

#include <QtCore/QString>
class QQmlContext;

/**
 * The Utils class containts some useful methods used throughout the application.
 */
class Utils
{

public:

    /**
     * Set the global variables in the specified context.
     */
    static void setGlobalProperties(QQmlContext *contex);

    /**
     * Returns the local path for the specified node path. For example, the local path for the node
     * "/~/Ubuntu One/file.txt" will be "/storage/emulated/0/u1/Ubuntu One/file.txt" on Android.
     */
    static QString getLocalPath(const QString &nodePath);

    /**
     * Opens the specified downloaded local file.
     */
    static void openFile(const QString &localPath);

};

#endif // UTILS_H
