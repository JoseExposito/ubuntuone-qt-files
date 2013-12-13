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

    property string toolBarTitle: qsTr("Welcome")
    property Menu toolBarMenu: Menu {
        MenuItem { text: qsTr("About..."); onTriggered: { menuAbout() } }
    }

    signal loginClicked()
    signal createAccountClicked()
    signal menuAbout()

    // Slideshows
    SlideViewer {
        anchors.top: parent.top
        anchors.bottom: buttons.top
        anchors.left: parent.left
        anchors.right: parent.right

        anchors.topMargin: 10*u
        anchors.bottomMargin: 20*u
        anchors.leftMargin: 18*u
        anchors.rightMargin: 18*u
    }

    // Buttons to login or create an account
    ColumnLayout {
        id: buttons
        spacing: 10*u
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.leftMargin: 10*u
        anchors.rightMargin: 10*u
        anchors.bottomMargin: 15*u

        Button {
            id: signIn
            style: UbuntuButtonStyle { }
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("Sign in")
            onClicked: loginClicked()
        }

        Button {
            id: createAccount
            style: UbuntuButtonStyle { }
            anchors.left: parent.left
            anchors.right: parent.right
            text: qsTr("I don't have an account")
            onClicked: createAccountClicked()
        }
    }

}
