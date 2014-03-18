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

/**
 * In Qt 5.2 personalized dialog are not supported and use the native dialogs is a pain in order to support more
 * platforms. Due to this, this QML components implements a very simple dialog used to create folders, rename files...
 */
MouseArea {
    id: inputDialog
    anchors.fill: parent
    z:1

    property string userInputText: inputText.text

    signal dialogCanceled()
    signal dialogAccepted()

    function show(title, defaultInputText, okButtonTitle, cancelButtonTitle) {
        titleLabel.text = title
        inputText.text = defaultInputText
        okButton.text = okButtonTitle
        cancelButton.text = cancelButtonTitle

        opacity = 1
        visible = true
    }

    function hide() {
        inputText.focus = false;
        Qt.inputMethod.hide();
        opacity = 0;
    }

    // Fade in/out animation
    visible: false
    opacity: 0
    Behavior on opacity {
        PropertyAnimation {
            duration: 300
            onRunningChanged: visible = (opacity == 1) ? true : false
        }
    }

    // If the user click outside of the dialog
    onClicked: { dialogCanceled(); }

    MouseArea {
        id: inputDialogBox
        width: parent.width >= 620*u ? 600*u : parent.width - 20
        height: 120*u
        anchors.top: parent.top
        anchors.topMargin: 10*u
        anchors.horizontalCenter: parent.horizontalCenter

        Rectangle {
            id: backgroundBox
            anchors.fill: parent
            color: Qt.rgba(36/255, 36/255, 36/255, 1)
        }

        ColumnLayout {
            id: components
            anchors.fill: parent
            anchors.margins: 10*u
            spacing: 0

            ULabel {
                id: titleLabel
                verticalAlignment: Text.AlignVCenter
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                color: Qt.rgba(235/255, 235/255, 235/255, 1)
                font.bold: true
            }

            TextField {
                id: inputText
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                style: UbuntuTextFieldStyle { }
                textColor: Qt.rgba(235/255, 235/255, 235/255, 1)
            }

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                height: 30*u

                Button {
                    id: cancelButton
                    anchors.left: parent.left
                    anchors.bottom: parent.bottom
                    width: parent.width/2
                    style: u1DialogButtonStyle
                    onClicked: dialogCanceled()
                }
                Button {
                    id: okButton
                    anchors.right: parent.right
                    anchors.bottom: parent.bottom
                    width: parent.width/2
                    style: u1DialogButtonStyle
                    onClicked: dialogAccepted()
                }
            }
        }
    }

    Component {
        id: u1DialogButtonStyle
        ButtonStyle {
            background: Rectangle {
                border.color: Qt.rgba(0,0,0,0)
                border.width: 1*u
                color: Qt.rgba(0,0,0,0)
            }

            label: ULabel {
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                text: control.text
                color: Qt.rgba(235/255, 235/255, 235/255, 1)
                font.bold: control.pressed
            }
        }
    }

}
