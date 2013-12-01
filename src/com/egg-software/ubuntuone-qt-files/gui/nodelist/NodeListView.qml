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

    // Navigation signals
    signal openFolder(string path)
    signal openFile(string path)

    // Folder & files action signals
    signal renameNode(string path, string newName)
    signal deleteNode(string path)

    // File action signals
    signal downloadFile(string path)
    signal publishFile(string path, bool publish)
    signal copyPublicLink(string path)

    /**
     * Popup menu for folders, excluding volumes.
     */
    Menu {
        id: folderMenu
        property string filePath: ""

        MenuItem {
            text: qsTr("Rename")
            onTriggered: { renameNode(folderMenu.filePath, "New name") } // TODO Show a message box
        }
        MenuItem {
            text: qsTr("Delete")
            onTriggered: { deleteNode(folderMenu.filePath) }
        }
    }

    /**
     * Popup menu for files.
     */
    Menu {
        id: fileMenu
        property string filePath: ""
        property bool isPublic: false

        MenuItem {
            text: qsTr("Download")
            onTriggered: { downloadFile(fileMenu.filePath) }
        }
        MenuItem {
            text: fileMenu.isPublic ? qsTr("Unpublish file") : qsTr("Publish file")
            onTriggered: { publishFile(fileMenu.filePath, !fileMenu.isPublic) }
        }
        MenuItem {
            visible: fileMenu.isPublic
            text: qsTr("Copy publick link")
            onTriggered: { copyPublicLink(fileMenu.filePath) }
        }
        MenuItem {
            text: qsTr("Rename")
            onTriggered: { renameNode(fileMenu.filePath, "New name") } // TODO Show a message box
        }
        MenuItem {
            text: qsTr("Delete")
            onTriggered: { deleteNode(fileMenu.filePath) }
        }
    }

    /**
     * Delegate for the node list view.
     */
    Component {
        id: nodeListDelegate

        Item {
            width: parent.width
            height: 60*u

            MouseArea {
                id: cellMouseArea
                anchors.fill: parent
                onClicked: { model.isFile ? openFile(model.filePath) : openFolder(model.filePath) }
                onPressAndHold: {
                    if (model.isFile) {
                        fileMenu.filePath = model.filePath
                        fileMenu.isPublic = model.isPublic
                        fileMenu.popup()
                    } else if (model.isDirectory) {
                        folderMenu.filePath = model.filePath
                        folderMenu.popup()
                    }
                }
            }

            // Area with the file name, file size...
            Rectangle {
                anchors.top: parent.top
                anchors.bottom: separator.bottom
                width: parent.width
                color: cellMouseArea.pressed ? Qt.rgba(190/255, 190/255, 190/255, 1) : "transparent"

                // Icon
                Image {
                    id: nodeIcon
                    anchors {
                        left: parent.left
                        top: parent.top
                        bottom: parent.bottom
                        leftMargin: 10*u
                    }
                    width: 24*u
                    height: 24*u

                    source: model.icon
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                }

                // Filename
                ULabel {
                    id: nodeFilename
                    anchors {
                        left: nodeIcon.right
                        right: parent.right
                        top: parent.top
                        leftMargin: 10*u
                        topMargin: 10*u
                        rightMargin: 10*u
                    }

                    text: model.fileName
                    maximumLineCount: 1
                    wrapMode: Text.Wrap
                    elide: Text.ElideMiddle
                    font.bold: true
                }

                // Last modified
                ULabel {
                    id: nodeLastModified
                    anchors {
                        left: nodeIcon.right
                        right: nodeSize.left
                        bottom: parent.bottom
                        leftMargin: 10*u
                        rightMargin: 10*u
                        bottomMargin: 10*u
                    }

                    text: model.isFile ? qsTr("Last modified: ") + model.lastModified : "..."
                    color: Qt.rgba(109/255, 109/255, 109/255, 1)
                    maximumLineCount: 1
                    wrapMode: Text.Wrap
                    elide: Text.ElideMiddle
                    font.pixelSize: 13*u
                }

                // Size
                ULabel {
                    id: nodeSize
                    anchors {
                        right: parent.right
                        bottom: parent.bottom
                        rightMargin: 10*u
                        bottomMargin: 10*u
                    }

                    text: model.isFile ? model.fileSize : ""
                    color: Qt.rgba(109/255, 109/255, 109/255, 1)
                    font.pixelSize: 13*u
                }
            }

            // Separator
            Rectangle {
                id: separator
                anchors.bottom: parent.bottom
                width: parent.width
                height: 2*u
                color: cellMouseArea.pressed ? "transparent" : Qt.rgba(203/255, 203/255, 203/255, 1)
            }
        }
    }

    ListView {
        anchors.fill: parent
        delegate: nodeListDelegate
        model: nodeListModel
    }

}
