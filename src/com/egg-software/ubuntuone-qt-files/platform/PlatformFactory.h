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
#ifndef PLATFORMFACTORY_H
#define PLATFORMFACTORY_H

#include "PlatformUtils.h"
class QObject;

/**
 * The PlatformFactory class provides the only way to create a PlatformUtils class matching the running device.
 */
class PlatformFactory
{

public:

    /**
     * Creates a new PlatformUtils class matching the running device.
     * IMPORTANT: Remember to delete the object.
     */
    static PlatformUtils *createPlatformUtils(QObject *parent = 0);

private:

    // Singleton
    PlatformFactory();
    PlatformFactory(const PlatformFactory &);
    const PlatformFactory &operator = (const PlatformFactory &);

};

#endif // PLATFORMFACTORY_H
