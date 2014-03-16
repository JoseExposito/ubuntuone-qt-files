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

    property string toolBarTitle: "Ubuntu One"
    property Menu toolBarMenu: (viewPath === "/~/") ? toolBarMenuVolumes : toolBarMenuNoVolumes

    signal menuCreateFolder(string folderName)
    signal menuRefresh()
    signal menuAbout()

    // Navigation signals
    signal openFolder(int nodeIndex)
    signal openFile(int nodeIndex)

    // Folder & files action signals
    signal renameNode(int nodeIndex, string newName)
    signal deleteNode(int nodeIndex)

    // File action signals
    signal publishFile(int nodeIndex, bool publish)
    signal copyPublicLink(int nodeIndex)

    /**
     * Toolbar menus for volumes view and normal folders view.
     */
    Menu {
        id: toolBarMenuVolumes
        MenuItem { text: qsTr("Refresh");  onTriggered: { menuRefresh() } }
        MenuItem { text: qsTr("About..."); onTriggered: { menuAbout()   } }
    }

    Menu {
        id: toolBarMenuNoVolumes
        MenuItem { text: qsTr("Create folder");  onTriggered: { createFolderFunction() } }
        MenuItem { text: qsTr("Refresh");  onTriggered: { menuRefresh() } }
        MenuItem { text: qsTr("About..."); onTriggered: { menuAbout()   } }
    }

    /**
     * Popup menu for folders, excluding volumes.
     */
    Menu {
        id: folderMenu
        property int nodeIndex: -1
        property string nodeName: ""

        MenuItem {
            text: qsTr("Open")
            onTriggered: { openFolder(folderMenu.nodeIndex) }
        }
        MenuItem {
            text: qsTr("Rename")
            onTriggered: { renameNodeFunction(folderMenu.nodeIndex, folderMenu.nodeName) }
        }
        MenuItem {
            text: qsTr("Delete")
            onTriggered: { deleteNode(folderMenu.nodeIndex) }
        }
    }

    /**
     * Popup menu for files.
     */
    Menu {
        id: fileMenu
        property int nodeIndex: -1
        property bool isPublic: false
        property string nodeName: ""

        MenuItem {
            text: qsTr("Open")
            onTriggered: { openFile(fileMenu.nodeIndex) }
        }
        MenuItem {
            text: fileMenu.isPublic ? qsTr("Unpublish file") : qsTr("Publish file")
            onTriggered: { publishFile(fileMenu.nodeIndex, !fileMenu.isPublic) }
        }
        MenuItem {
            visible: fileMenu.isPublic
            text: qsTr("Share publick link")
            onTriggered: { copyPublicLink(fileMenu.nodeIndex) }
        }
        MenuItem {
            text: qsTr("Rename")
            onTriggered: { renameNodeFunction(fileMenu.nodeIndex, fileMenu.nodeName) }
        }
        MenuItem {
            text: qsTr("Delete")
            onTriggered: { deleteNode(fileMenu.nodeIndex) }
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
                onClicked: { model.isFile ? openFile(model.index) : openFolder(model.index) }
                onPressAndHold: {
                    if (model.isFile) {
                        fileMenu.nodeIndex = model.index;
                        fileMenu.isPublic  = model.isPublic;
                        fileMenu.nodeName  = model.fileName;
                        fileMenu.popup();
                    } else if (model.isDirectory) {
                        folderMenu.nodeIndex = model.index;
                        folderMenu.nodeName  = model.fileName;
                        folderMenu.popup();
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
                        right: nodePublicIndicator.left
                        top: parent.top
                        leftMargin: 10*u
                        topMargin: 10*u
                    }

                    text: model.fileName
                    maximumLineCount: 1
                    wrapMode: Text.Wrap
                    elide: Text.ElideMiddle
                    font.bold: true
                }

                // Published indicator
                Image {
                    id: nodePublicIndicator
                    anchors {
                        right: nodeDownloadedIndicator.left
                        top: parent.top
                        leftMargin: 10*u
                        topMargin: 10*u
                        rightMargin: nodeDownloadedIndicator.visible ? 10*u : 0
                    }
                    width: 16*u
                    height: 16*u

                    source: "qrc:/icons/published_indicator.png"
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
                    visible: model.isPublic
                }

                // Downloaded indicator
                Image {
                    id: nodeDownloadedIndicator
                    anchors {
                        right: parent.right
                        top: parent.top
                        topMargin: 10*u
                        rightMargin: 10*u
                    }
                    visible: model.downloadedStatus
                    width: model.downloadedStatus ? 16*u : 0
                    height: 16*u

                    source: "qrc:/icons/saved_indicator.png"
                    fillMode: Image.PreserveAspectFit
                    antialiasing: true
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

                    visible: !model.downloadingStatus
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

                    visible: !model.downloadingStatus
                    text: model.isFile ? model.fileSize : ""
                    color: Qt.rgba(109/255, 109/255, 109/255, 1)
                    font.pixelSize: 13*u
                }

                // Download ProgressBar
                ProgressBar {
                    id: nodeDownloadProgressBar
                    anchors {
                        left: nodeIcon.right
                        right: parent.right
                        bottom: parent.bottom
                        leftMargin: 10*u
                        rightMargin: 10*u
                        bottomMargin: 10*u
                    }

                    visible: model.downloadingStatus
                    minimumValue: 0
                    maximumValue: 100
                    value: model.downloadProgress
                    height: nodeLastModified.height
                    indeterminate: (model.downloadProgress <= 0)

                    style: UbuntuProgressBarStyle { }
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

    function renameNodeFunction(nodeIndex, nodeName) {
        inputDialog.show(qsTr("Rename"), nodeName, qsTr("Rename file"), qsTr("Cancel"));
        inputDialog.dialogAccepted.connect(function callback() {
            inputDialog.hide();
            renameNode(nodeIndex, inputDialog.userInputText);
            inputDialog.dialogAccepted.disconnect(callback);
        });
    }

    function createFolderFunction(nodeIndex) {
        inputDialog.show(qsTr("Create folder"), qsTr("New folder"), qsTr("Create"), qsTr("Cancel"));
        inputDialog.dialogAccepted.connect(function callback() {
            inputDialog.hide();
            menuCreateFolder(inputDialog.userInputText);
            inputDialog.dialogAccepted.disconnect(callback);
        });
    }

    ListView {
        anchors.fill: parent
        delegate: nodeListDelegate
        model: nodeListModel

        U1InputDialog {
            id: inputDialog
            visible: false
            anchors.fill: parent
            onDialogCanceled: inputDialog.hide()
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
