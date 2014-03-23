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
#include <QtQuick>

void Utils::setGlobalProperties(QQmlContext *contex)
{
    // Resolution independent unit "u"
    QScreen *screen = qApp->screens().at(0);
    qreal desktopLogicalDotsPerInch = 72;
    qreal u = screen->logicalDotsPerInch()/desktopLogicalDotsPerInch;
    contex->setContextProperty("u", u);

    // Platform
    QString platform;
#ifdef Q_OS_ANDROID
    platform = "ANDROID";
#elif defined(Q_OS_IOS)
    platform = "IOS";
#else
    platform = "DESKTOP";
#endif
    contex->setContextProperty("platform", platform);
}
