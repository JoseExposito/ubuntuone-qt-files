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
import QtQuick.Dialogs 1.1
import "qrc:/."

/**
 * Application main window with the stack where all the screens of the application are pushed.
 */
ApplicationWindow {

    signal popStackView()

    id: applicationWindow
    width:  320
    height: 480
    color:  Qt.rgba(232/255, 232/255, 232/255, 1)

    // Implements back key navigation on Android
    Item {
        id: backKeyNavigationItem
        focus: (platform === "ANDROID")
        Keys.onReleased: {
            if (event.key === Qt.Key_Back) {
                if (stackView.depth > 1) {
                    if (!stackView.busy && !loadingSpinner.visible)
                        popStackView();
                    event.accepted = true;
                } else {
                    Qt.quit();
                }
            }
        }
    }

    Component.onCompleted: {
        if (platform === "ANDROID") {
            Qt.inputMethod.visibleChanged.connect(function() { backKeyNavigationItem.focus = !Qt.inputMethod.visible; });
        }
    }

    /**
     * Top bar with the title of the window and the back button.
     */
    toolBar: MainWindowToolbar {
        id: mainWindowToolbar
        enabled: !loadingSpinner.visible
        toolBarTitle: stackView.currentItem == null ? "" : stackView.currentItem.toolBarTitle
        onMenuButtonClicked: stackView.currentItem.toolBarMenu.popupFromToolbar()
    }

    /**
     * Main stack view where all the screens of the application are pushed.
     */
    StackView {
        id: stackView
        objectName: "stackView"
        anchors.fill: parent
        enabled: !loadingSpinner.visible
    }

    /**
     * Loading spinner shown while the application is busy.
     */
    U1Spinner {
        id: loadingSpinner
        objectName: "loadingSpinner"
        visible: false
    }

    /**
     * About dialog showed when the option is selected in the context menu.
     */
    function showAboutDialog() { aboutDialog.visible = true }
    MessageDialog {
        id: aboutDialog
        title: qsTr("Ubuntu One Qt Files")
        text: qsTr("Copyright (C) 2013 José Expósito\n<jose.exposito89@gmail.com>\n\n" +
                   "Source code available under GPLv3 license at:\n" +
                   "https://github.com/JoseExposito/ubuntuone-qt-files\n\n" +
                   "Follow the project on Twitter:\n" +
                   "https://twitter.com/Jose__Exposito")
        standardButtons: StandardButton.Help | StandardButton.Ok
        onHelp: Qt.openUrlExternally("https://github.com/JoseExposito/ubuntuone-qt-files")
    }
}
