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
#include "Utils.h"
#include <QtCore>
#include <QtQuick>
#ifdef Q_OS_ANDROID
#include "AndroidUtils.h"
#else
#include <QtGui>
#endif

void Utils::setGlobalProperties(QQmlContext *contex)
{
    // Resolution independent unit "u"
    QScreen *screen = qApp->screens().at(0);
    qreal desktopLogicalDotsPerInch = 72;
    qreal u = screen->logicalDotsPerInch()/desktopLogicalDotsPerInch;
    contex->setContextProperty("u", u);
}

QString Utils::getLocalPath(const QString &nodePath)
{
#ifdef Q_OS_ANDROID
    QString baseLocalPath = AndroidUtils::getSDCardPath() + "/u1";
#else
    QString baseLocalPath = QStandardPaths::writableLocation(QStandardPaths::DataLocation);
#endif

    return baseLocalPath.endsWith(QDir::separator())
            ? baseLocalPath + QString(nodePath).replace("/~/", "")
            : baseLocalPath + QDir::separator() + QString(nodePath).replace("/~/", "");
}

void Utils::openFile(const QString &localPath)
{
#ifdef Q_OS_ANDROID
    AndroidUtils::openFile(localPath);
#else
    QDesktopServices::openUrl(QUrl::fromLocalFile(localPath));
#endif
}
