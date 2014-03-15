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
#ifndef PLATFORMUTILS_H
#define PLATFORMUTILS_H

#include <QtCore/QObject>

/**
 * The PlatformUtils class provides the default implementation of the platform specified things, ie desktop, and also is
 * the base class for other platforms, that can override this implementation if it is necessary.
 * Do NOT instance this class directly, use PlatformFactory instead to create an instance.
 */
class PlatformUtils : public QObject
{
    Q_OBJECT

public:

    PlatformUtils(QObject *parent = 0);

    /**
     * Opens the specified file with the default viewer.
     */
    virtual void openFile(const QString &filePath);

    /**
     * Returns the local path for the specified node path. For example, the local path for the node
     * "/~/Ubuntu One/file.txt" will be "/storage/emulated/0/u1/Ubuntu One/file.txt" on Android.
     */
    virtual QString getLocalPath(const QString &nodePath);

    /**
     * Shares the specified link. On desktop copies it to clipboard.
     */
    virtual void shareLink(const QString &link);

};

#endif // PLATFORMUTILS_H
