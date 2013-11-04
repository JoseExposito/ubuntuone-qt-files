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
import "qrc:/js/Util.js" as Util

/**
 * Application main window with the stack where all the screens of the application are pushed.
 */
ApplicationWindow {

    width:  320
    height: 480
    color:  styles.windowBackgroundColor
    property variant styles: Styles { }

    // Implements back key navigation
    // TODO It's supposed that this Rectangle is not necessary, but in the Qt 5.2 BETA this is not working
    Rectangle {
        focus: true
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
    }

    /**
     * Top bar with the title of the window and the back button.
     */
    toolBar: ColumnLayout {
        width: parent.width

        // Top orange line
        Rectangle {
            anchors.top: parent.top
            Layout.minimumHeight: Util.u(3)
            Layout.maximumHeight: Util.u(3)
            Layout.fillWidth: true
            color: Qt.rgba(215/255, 45/255, 40/255, 1)
        }

        Rectangle {
            Layout.minimumHeight: Util.u(40)
            Layout.maximumHeight: Util.u(40)

            // Back button, visible if the stack have more than one item
            Rectangle {
                id: backButton
                anchors.left: parent.left
                anchors.leftMargin: Util.u(10)
                anchors.verticalCenter: parent.verticalCenter
                width: stackView.depth > 1 ? Util.u(30) : Util.u(0)
                height: Util.u(30)
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
                x: backButton.x + backButton.width + Util.u(10)
                Behavior on x { NumberAnimation{ easing.type: Easing.OutCubic} }
                font.pixelSize: Util.u(30)
                text: "Ubuntu One" // TODO To a property
            }
        }

        // Bottom separator
        Rectangle {
            Layout.minimumHeight: Util.u(12)
            Layout.maximumHeight: Util.u(12)
            Layout.fillWidth: true
            color: Qt.rgba(165/255, 165/255, 165/255, 1)
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
