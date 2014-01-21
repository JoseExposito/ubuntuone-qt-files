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

        PauseAnimation { duration: 5000 }
        NumberAnimation { target: slide0; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide1; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 5000 }
        NumberAnimation { target: slide1; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide2; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 5000 }
        NumberAnimation { target: slide2; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide3; property: "opacity"; to: 1; duration: 1000 }

        PauseAnimation { duration: 5000 }
        NumberAnimation { target: slide3; property: "opacity"; to: 0; duration: 1000 }
        NumberAnimation { target: slide0; property: "opacity"; to: 1; duration: 1000 }
    }



    Slide {
        id: slide0
        opacity: 1
        slideImage: "qrc:/slides/slide0.png"
        slideTitle: qsTr("Your cloud")
        slideContent: qsTr("Store your files, photos and music safely in Ubuntu One and access them from any of your "
                + "devices, wherever you are. Get 5GB of cloud storage for FREE")
    }

    Slide {
        id: slide1
        opacity: 0
        slideImage: "qrc:/slides/slide1.png"
        slideTitle: qsTr("Your photos")
        slideContent: qsTr("Snap a photo and it will instantly appear online and on all your devices. Easily share "
                + "shots with friends, family, colleagues or on social networks")
    }

    Slide {
        id: slide2
        opacity: 0
        slideImage: "qrc:/slides/slide2.png"
        slideTitle: qsTr("Your music")
        slideContent: qsTr("Add more cloud storage when you need it or stream your music online or on your mobile. "
                + "Music Streaming has 20GB of extra cloud storage built in - try it free for 30 days")
    }

    Slide {
        id: slide3
        opacity: 0
        slideImage: "qrc:/slides/slide3.png"
        slideTitle: qsTr("Getting started")
        slideContent: qsTr("Go to https://one.ubuntu.com/downloads/ and follow our simple guide to install Ubuntu One "
                + "on all your devices. Ubuntu One works on Windows, OS X, Android, iOS, Ubuntu and via the Web")
    }

}
