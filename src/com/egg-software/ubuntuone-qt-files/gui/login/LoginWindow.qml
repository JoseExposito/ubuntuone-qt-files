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

    property string toolBarTitle: qsTr("Login")
    property U1Menu toolBarMenu: toolbarMenu

    U1Menu {
        id: toolbarMenu
        MenuItem { text: qsTr("About..."); onTriggered: { menuAbout() } }
    }

    signal login(string username, string password)
    signal menuAbout()

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10*u
        spacing: 10*u

        TextField {
            id: usernameTextField
            focus: true
            placeholderText: qsTr("Email")
            inputMethodHints: Qt.ImhEmailCharactersOnly | Qt.ImhLowercaseOnly
            style: U1TextFieldStyle { }

            Layout.fillWidth: true
            Layout.maximumWidth: 600*u
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        TextField {
            id: passwordTextField
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
            style: U1TextFieldStyle { }

            Layout.fillWidth: true
            Layout.maximumWidth: 600*u
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
        }

        Button {
            text: qsTr("Login")
            style: U1ButtonStyle { }

            Layout.fillWidth: true
            Layout.maximumWidth: 600*u
            Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter

            onClicked: {
                usernameTextField.focus = false;
                passwordTextField.focus = false;
                Qt.inputMethod.hide();
                login(usernameTextField.text, passwordTextField.text)
            }
        }

        Item {
            id: separator
            Layout.fillHeight: true
        }
    }
}
