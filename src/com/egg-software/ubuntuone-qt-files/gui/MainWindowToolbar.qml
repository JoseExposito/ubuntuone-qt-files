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

ColumnLayout {

    id: mainWindowToolbar

    property string toolBarTitle: ""
    signal menuButtonClicked()

    width:  parent.width
    height: toolBarArea.height + bottomSeparator.height

    Rectangle {
        id: toolBarArea
        anchors.top: parent.top
        Layout.minimumHeight: 50*u
        Layout.maximumHeight: 50*u
        Layout.fillWidth: true
        color: Qt.rgba(213/255, 213/255, 213/255, 1)

        // Back button, visible if the stack have more than one item
        Rectangle {
            id: backButton
            anchors.left: parent.left
            anchors.leftMargin: 10*u
            anchors.verticalCenter: parent.verticalCenter
            width: stackView.depth > 1 ? 30*u : 0
            height: 30*u
            opacity: stackView.depth > 1 ? 1 : 0
            Behavior on opacity { NumberAnimation{} }
            color: "transparent"

            Image {
                anchors.fill: parent
                source: "qrc:/theme/navigation_previous_item.png"
                antialiasing: true
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                anchors.margins: -10
                onClicked: {
                    Qt.inputMethod.hide()
                    popStackView()
                }
            }
        }

        // Title
        U1Label {
            id: titleLabel
            anchors.right: menuButton.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.leftMargin: 10*u
            anchors.left: backButton.right
            font.pixelSize: 24*u
            color: "black"
            text: toolBarTitle
            maximumLineCount: 1
            wrapMode: Text.Wrap
            elide: Text.ElideMiddle
        }

        // Menu button
        Rectangle {
            id: menuButton
            anchors.right: parent.right
            anchors.rightMargin: 10*u
            anchors.verticalCenter: parent.verticalCenter
            width: 30*u
            height: 30*u
            color: "transparent"

            Image {
                anchors.fill: parent
                source: "qrc:/theme/menu_button.png"
                antialiasing: true
                fillMode: Image.PreserveAspectFit
            }
            MouseArea {
                anchors.fill: parent
                anchors.margins: -10
                onClicked: menuButtonClicked()
            }
        }
    }

    // Bottom separator
    Rectangle {
        id: bottomSeparator
        anchors.top: toolBarArea.bottom
        Layout.minimumHeight: 2*u
        Layout.maximumHeight: 2*u
        Layout.fillWidth: true
        color: Qt.rgba(176/255, 176/255, 176/255, 1)
    }

}
