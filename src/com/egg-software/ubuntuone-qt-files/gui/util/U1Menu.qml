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

/**
 * In Qt 5.2 the standard Menu component is not working on iOS. Due to this, this QML components implements an
 * alternative.
 * https://bugreports.qt-project.org/browse/QTBUG-37470
 */
MouseArea {
    id: menu
    anchors.fill: parent
    z: 1

    // https://bugreports.qt-project.org/browse/QTBUG-26810
    property list<MenuItem> menuItems
    default property alias items: menu.menuItems

    property bool shownFromToolbar: true

    function popupFromToolbar() {
        if (visible) {
            hide();
        } else {
            menu.shownFromToolbar = true;
            show();
        }
    }

    function popup() {
        menu.shownFromToolbar = false;
        show();
    }

    function show() {
        model.clear();
        for (var i=0; i<items.length; ++i) {
            if (items[i].visible)
                model.append(items[i]);
        }

        opacity = 1;
        visible = true;
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

    // If the user click outside of the menu
    onClicked: { hide() }

    Rectangle {
        id: menuBox
        width: 250*u
        height: 40*u * model.count
        color: Qt.rgba(36/255, 36/255, 36/255, 1)
        clip: true

        anchors.top:   shownFromToolbar ? parent.top : undefined
        anchors.right: shownFromToolbar ? parent.right : undefined
        anchors.topMargin:   shownFromToolbar ? 10*u : 0
        anchors.rightMargin: shownFromToolbar ? 10*u : 0

        anchors.centerIn: shownFromToolbar ? undefined : parent

        ListModel { id: model }
        ListView {
            anchors.fill: parent
            model: model
            delegate: MouseArea {
                width: parent.width
                height: 40*u

                onClicked: {
                    items[model.index].triggered();
                    hide();
                }

                Rectangle {
                    id: onPressedBackgroud
                    visible: parent.pressed
                    anchors.fill: parent
                    color: Qt.rgba(15/255, 15/255, 15/255, 1)
                }

                U1Label {
                    id: menuEntryText
                    anchors.fill: parent
                    anchors.left: parent.left
                    anchors.right: parent.right
                    text: model.text
                    verticalAlignment: Text.AlignVCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: Qt.rgba(235/255, 235/255, 235/255, 1)
                }

                Rectangle {
                    id: separator
                    anchors.top: menuEntryText.bottom
                    anchors.left: parent.left
                    anchors.right: parent.right
                    color: Qt.rgba(45/255, 45/255, 45/255, 1)
                    width: parent.width
                    height: 2*u
                }
            }

        }
    }

}
