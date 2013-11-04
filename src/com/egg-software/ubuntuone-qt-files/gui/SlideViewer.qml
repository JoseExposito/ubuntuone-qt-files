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
import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import "qrc:/."

Item {

    SequentialAnimation {
        loops: Animation.Infinite
        running: true

        PauseAnimation { duration: 3000 }
        NumberAnimation { target: slide0; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide1; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 3000 }
        NumberAnimation { target: slide1; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide2; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 3000 }
        NumberAnimation { target: slide2; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide3; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 3000 }
        NumberAnimation { target: slide3; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide0; property: "opacity"; to: 1; duration: 1000 }
    }



    Slide {
        id: slide0
        opacity: 1
        slideImage: "qrc:/slides/slide0.png"
        slideTitle: qsTr("Your cloud")
        slideContent: qsTr("Store your files, photos and music safely in Ubuntu One...")
    }

    Slide {
        id: slide1
        opacity: 0
        slideImage: "qrc:/slides/slide1.png"
        slideTitle: qsTr("Your cloud")
        slideContent: qsTr("Store your files, photos and music safely in Ubuntu One...")
    }

    Slide {
        id: slide2
        opacity: 0
        slideImage: "qrc:/slides/slide2.png"
        slideTitle: qsTr("Your cloud")
        slideContent: qsTr("Store your files, photos and music safely in Ubuntu One...")
    }

    Slide {
        id: slide3
        opacity: 0
        slideImage: "qrc:/slides/slide3.png"
        slideTitle: qsTr("Your cloud")
        slideContent: qsTr("Store your files, photos and music safely in Ubuntu One...")
    }

}
