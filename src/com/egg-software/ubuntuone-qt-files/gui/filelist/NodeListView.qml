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
import QtQuick.Layouts 1.1
import "qrc:/."

Item {

    Component {
        id: nodeListDelegate

        Item {
            width: parent.width
            height: 50*u

            // Area with the file name, file size...
            Rectangle {
                id: infoArea
                anchors.top: parent.top
                anchors.bottom: separator.bottom
                width: parent.width
                color: "transparent"

                GridLayout {
                    anchors.fill: parent
                    anchors.margins: 15*u

                    ULabel {
                        Layout.fillWidth: true
                        text: model.fileName
                        font.bold: true
                    }

                    /*ULabel {
                        text: model.fileSize
                    }*/
                }
            }

            // Separator
            Rectangle {
                id: separator
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2*u
                color: Qt.rgba(203/255, 203/255, 203/255, 1)
            }
        }
    }

    ListView {
        anchors.fill: parent
        delegate: nodeListDelegate
        model: nodeListModel
    }

}
