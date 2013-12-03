QT    += qml quick widgets network sql
android: QT += androidextras
TARGET = U1-Files

VERSION = 0.1
DEFINES += VERSION=\\\"$$VERSION\\\"

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(android/android.pri)
