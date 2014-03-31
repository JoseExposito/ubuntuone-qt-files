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

Rectangle {
    id: toast    
    property string toastText: ""

    anchors.bottom: parent.bottom
    anchors.bottomMargin: 10*u
    anchors.horizontalCenter: parent.horizontalCenter

    color: Qt.rgba(0, 0, 0, 0.2)
    radius: 8*u
    width: 300*u
    height: 40*u

    z:1
    visible: false
    opacity: 0

    function show() {
        opacity = 1
        visible = true
    }

    function hide() {
        opacity = 0;
    }

    Behavior on opacity {
        PropertyAnimation {
            duration: 400
            onRunningChanged: visible = (opacity == 1) ? true : false
        }
    }

    U1Label {
        anchors.fill: parent
        anchors.leftMargin: 2*u
        anchors.rightMargin: 2*u
        text: toastText
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        maximumLineCount: 2
    }

}
