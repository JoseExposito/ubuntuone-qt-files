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
import QtQuick.Controls.Styles 1.1
import QtQuick.Layouts 1.1
import "qrc:/."

/**
 * Application main window with the stack where all the screens of the application are pushed.
 */
ApplicationWindow {

    width:  320
    height: 480
    color:  Qt.rgba(232/255, 232/255, 232/255, 1)

    // Implements back key navigation
    // TODO In the Qt 5.2 BETA this is not working, test it in the future
    Keys.onReleased: {
        if (event.key === Qt.Key_Back) {
            if (stackView.depth > 1) {
                stackView.pop();
                event.accepted = true;
            } else {
                Qt.quit();
            }
        }
    }

    /**
     * Top bar with the title of the window and the back button.
     */
    toolBar: ColumnLayout {
        width: parent.width
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
                    id: backmouse
                    anchors.fill: parent
                    anchors.margins: -10
                    onClicked: stackView.pop()
                }
            }

            // Title
            ULabel {
                anchors.verticalCenter: parent.verticalCenter
                x: backButton.x + backButton.width + 10*u
                Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
                font.pixelSize: 30*u
                color: "black"
                text: "Ubuntu One" // TODO To a property
            }
        }

        // Bottom separator
        Rectangle {
            id: bottomSeparator
            anchors.top: toolBarArea.bottom
            Layout.minimumHeight: 3*u
            Layout.maximumHeight: 3*u
            Layout.fillWidth: true
            gradient: Gradient {
                GradientStop { position: 0; color: Qt.rgba(213/255, 213/255, 213/255, 1) }
                GradientStop { position: 1; color: Qt.rgba(176/255, 176/255, 176/255, 1) }
            }
        }

    }

    /**
     * Main stack view where all the screens of the application are pushed.
     */
    StackView {
        id: stackView
        objectName: "stackView"
        anchors.fill: parent
    }

}
