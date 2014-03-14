QT      += qml quick network sql widgets
TARGET   = U1Files
VERSION  = 0.4
DEFINES += VERSION=\\\"$$VERSION\\\"

# Android
android: QT += androidextras

# iOS
ios: QTPLUGIN +=  qsqlite # https://bugreports.qt-project.org/browse/QTBUG-35195
ios: LIBS += -framework UIKit

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(android/android.pri)
include(ios/ios.pri)
