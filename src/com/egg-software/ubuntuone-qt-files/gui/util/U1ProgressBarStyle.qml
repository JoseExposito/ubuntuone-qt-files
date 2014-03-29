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

Component {

    ProgressBarStyle {

        background: Rectangle {
            color: Qt.rgba(213/255, 213/255, 213/255, 1)
            radius: 6*u
            border.width: 1*u
            border.color: Qt.rgba(158/255, 158/255, 158/255, 1)
        }

        progress: control.indeterminate ? indeterminateProgress : determinateProgress

        property Component determinateProgress: Rectangle {
            color: Qt.rgba(213/255, 213/255, 213/255, 1)
            radius: 6*u
            border.width: 1*u
            border.color: Qt.rgba(158/255, 158/255, 158/255, 1)
        }

        property Component indeterminateProgress: Rectangle {
            id: indeterminateProgress
            color: "transparent"
            anchors.fill: parent
            anchors.leftMargin:  2*u
            anchors.rightMargin: 2*u
            radius: 6*u
            clip: true

            property int posX: 0
            Row {
                x: parent.posX
                anchors.verticalCenter: parent.verticalCenter
                spacing: 10*u
                Repeater {
                    model: Math.ceil(parent.parent.width / 9*u)
                    Rectangle {
                        width: 3*u
                        height: indeterminateProgress.height + 20*u
                        color: Qt.rgba(158/255, 158/255, 158/255, 1)
                        rotation: 45
                        smooth: true
                    }
                }
            }
            Timer {
                interval:30
                repeat: true
                running: true
                onTriggered: if (parent.posX++ > 10*u) parent.posX = 0
            }
        }

    }

}
