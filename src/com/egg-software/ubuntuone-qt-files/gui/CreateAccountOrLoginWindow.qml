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
import QtQuick.Controls.Styles 1.1
import "qrc:/."
import "qrc:/js/Util.js" as Util

Item {

    property variant styles: Styles { }

    // Slideshows
    SlideViewer {
        anchors.top: parent.top
        anchors.bottom: buttons.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: Util.u(10)
        anchors.bottomMargin: Util.u(20)
        anchors.leftMargin: Util.u(18)
        anchors.rightMargin: Util.u(18)
    }

    // Buttons to login or create an account
    ColumnLayout {
        id: buttons
        spacing: Util.u(10)
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: Util.u(10)
        anchors.rightMargin: Util.u(10)
        anchors.bottomMargin: Util.u(15)

        Button {
            id: signIn
            style: styles.ubuntuButtonStyle
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Sign in")
        }

        Button {
            id: createAccount
            style: styles.ubuntuButtonStyle
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("I don't have an account")
        }
    }

}
