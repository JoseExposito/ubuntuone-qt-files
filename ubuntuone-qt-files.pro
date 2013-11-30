QT    += qml quick widgets network sql
TARGET = ubuntuoneqtfiles

VERSION = 0.1
DEFINES += VERSION=\\\"$$VERSION\\\"

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(deploy/android/deploy.android.pri)
