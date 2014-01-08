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
    id: loadingSpinner
    anchors.fill: parent

    property string loadingSpinnerText: ""

    Item {
        id: loadingSpinnerBox
        width:  200*u
        height: 100*u
        anchors.centerIn: parent

        Rectangle {
            id: backgroundBox
            anchors.fill: parent
            color: Qt.rgba(0, 0, 0, 0.2)
            radius: 6*u
        }

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: 15*u

            BusyIndicator {
                width:  35*u
                height: 35*u
                Layout.alignment: Qt.AlignHCenter
            }

            ULabel {
                Layout.alignment: Qt.AlignHCenter
                Layout.fillWidth: true
                text: loadingSpinnerText
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
            }
        }
    }

}
