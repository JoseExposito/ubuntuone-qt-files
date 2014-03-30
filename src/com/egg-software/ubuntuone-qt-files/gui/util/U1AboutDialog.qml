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

MouseArea {
    id: aboutDialog
    anchors.fill: parent
    z:1

    signal dialogCanceled()
    signal dialogAccepted()

    function show() {
        opacity = 1
        visible = true
    }

    function hide() {
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
        id: aboutDialogBox
        width: parent.width >= 620*u ? 600*u : parent.width - 20
        height: 180*u
        anchors.centerIn: parent

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

            Item {
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.top: parent.top
                height: 40*u

                Item {
                    anchors.centerIn: parent
                    height: 40*u
                    width: 120*u
                    Image {
                        Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                        source: "qrc:/icons/u1files.png"
                        height: 40*u
                        width:  40*u
                        fillMode: Image.PreserveAspectFit
                        antialiasing: true
                        anchors.left: parent.left
                    }

                    U1Label {
                        text: "U1Files"
                        font.pixelSize: 20*u
                        verticalAlignment: Text.AlignVCenter
                        color: Qt.rgba(235/255, 235/255, 235/255, 1)
                        font.bold: true
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.bottom: parent.bottom
                    }
                }
            }

            U1Label {
                Layout.fillWidth: true
                text: qsTr("<p>Copyright (C) 2013/14 <a href=\"http://www.egg-software.com\">José Expósito</a></p>" +
                           "<p><a href=\"mailto:jose.exposito89@gmail.com\">jose.exposito89@gmail.com</a></p><br />" +
                           "<p>Source code available on <a href=\"https://github.com/JoseExposito/ubuntuone-qt-files\">GitHub</a></p>" +
                           "<p>Follow the project on <a href=\"https://twitter.com/Jose__Exposito\">Twitter</a></p>")
                color: Qt.rgba(235/255, 235/255, 235/255, 1)
                linkColor: Qt.rgba(235/255, 235/255, 235/255, 1)
                onLinkActivated: Qt.openUrlExternally(link)
                horizontalAlignment: Qt.AlignHCenter
            }
        }
    }

}
