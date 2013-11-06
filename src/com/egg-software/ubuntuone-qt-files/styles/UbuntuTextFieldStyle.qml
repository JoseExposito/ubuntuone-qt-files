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

    TextFieldStyle {

        FontLoader { source: "qrc:/fonts/Ubuntu.ttf" }

        textColor: Qt.rgba(85/255, 85/255, 85/255, 1)
        placeholderTextColor: Qt.rgba(155/255, 155/255, 155/255, 1)
        selectionColor: Qt.rgba(155/255, 155/255, 155/255, 0.2)
        font.pixelSize: 16*u
        font.family: "Ubuntu"

        background: Rectangle {
            implicitWidth: 50*u
            implicitHeight: 40*u
            color: Qt.rgba(202/255, 202/255, 202/255, 1)
            radius: 6*u
        }
    }

}
