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

    property string slideImage: ""
    property string slideTitle: ""
    property string slideContent: ""

    Behavior on opacity { NumberAnimation{} }
    anchors.fill: parent

    Image {
        fillMode: Image.PreserveAspectFit
        source: slideImage
        antialiasing: true

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.maximumWidth: 400*u
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
    }

    ULabel {
        id: slideTitleID
        text: slideTitle
        font.bold: true

        Layout.fillWidth: true
        Layout.maximumWidth: 600*u
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
    }

    ULabel {
        id: slideContentID
        text: slideContent
        horizontalAlignment: Text.AlignJustify
        font.pixelSize: 14*u

        Layout.fillWidth: true
        Layout.maximumWidth: 600*u
        Layout.alignment: Qt.AlignVCenter | Qt.AlignHCenter
    }

}
