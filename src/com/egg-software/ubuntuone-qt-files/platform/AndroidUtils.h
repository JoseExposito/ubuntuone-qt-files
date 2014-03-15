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
#ifndef ANDROIDUTILS_H
#define ANDROIDUTILS_H

#include <QtCore/QObject>
#ifdef Q_OS_ANDROID
#include "PlatformUtils.h"
#include <jni.h>

/**
 * The AndroidUtils class brings easy access to the AndroidUtils.java class from C++.
 */
class AndroidUtils : public PlatformUtils
{

public:

    AndroidUtils(QObject *parent = 0);

    virtual void openFile(const QString &filePath);
    virtual QString getLocalPath(const QString &nodePath);
    virtual void shareLink(const QString &link);

    /**
     * QInputDialog is not working in Android and QML doesn't offer a similar dialog or a way to build personalized
     * dialogs. Due to this, this method offers a simple way to show an input dialog.
     */
    static void showInputDialog(const QString &title, const QString &description, const QString &defaultInput,
        const QString &okButtonTitle, const QString &cancelButtonTitle, void *callback);

};

#endif // Q_OS_ANDROID
#endif // ANDROIDUTILS_H
