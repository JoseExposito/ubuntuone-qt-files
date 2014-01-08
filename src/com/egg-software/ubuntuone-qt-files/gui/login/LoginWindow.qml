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
import QtQuick.Dialogs 1.1
import "qrc:/."

Item {

    property string toolBarTitle: qsTr("Login")
    property Menu toolBarMenu: Menu {
        MenuItem { text: qsTr("About..."); onTriggered: { menuAbout() } }
    }

    signal login(string username, string password)
    signal menuAbout()

    ColumnLayout {
        spacing: 10*u
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
            topMargin: 10*u
            leftMargin: 10*u
            rightMargin: 10*u
        }

        TextField {
            id: usernameTextField
            focus: true
            placeholderText: qsTr("Email")
            inputMethodHints: Qt.ImhEmailCharactersOnly
            style: UbuntuTextFieldStyle { }
            Layout.fillWidth: true
        }

        TextField {
            id: passwordTextField
            placeholderText: qsTr("Password")
            echoMode: TextInput.Password
            style: UbuntuTextFieldStyle { }
            Layout.fillWidth: true
        }

        Button {
            text: qsTr("Login")
            style: UbuntuButtonStyle { }
            Layout.fillWidth: true
            onClicked: {
                usernameTextField.focus = false;
                passwordTextField.focus = false;
                Qt.inputMethod.hide();
                login(usernameTextField.text, passwordTextField.text)
            }
        }
    }

    /**
     * Error message.
     */
    function showErrorDialog() { errorDialog.visible = true }
    property string errorDialogText: ""
    MessageDialog {
        id: errorDialog
        title: qsTr("Error")
        text: errorDialogText
    }

}
