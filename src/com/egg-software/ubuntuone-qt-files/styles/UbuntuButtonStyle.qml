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
import "qrc:/js/Util.js" as Util

Component {
    id: ubuntuButtonStyle
    ButtonStyle {
        background: Rectangle {
            property Gradient normalGradient: Gradient {
                GradientStop { position: 0 ; color: Qt.rgba(190/255, 67/255, 42/255, 1) }
                GradientStop { position: 1 ; color: Qt.rgba(190/255, 97/255, 53/255, 1) }
            }
            property Gradient pressedGradient: Gradient {
                GradientStop { position: 0 ; color: Qt.rgba(170/255, 47/255, 22/255, 1) }
                GradientStop { position: 1 ; color: Qt.rgba(170/255, 77/255, 33/255, 1) }
            }

            implicitWidth: Util.u(50)
            implicitHeight: Util.u(40)
            border.color: Qt.rgba(190/255, 67/255, 42/255, 1)
            radius: 6
            gradient: control.pressed ? pressedGradient : normalGradient
        }

        label: ULabel {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            text: control.text
            color: control.pressed ? "gray" : "white"
        }
    }
}
