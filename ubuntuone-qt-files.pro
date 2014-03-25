QT      += qml quick network sql widgets
TARGET   = U1Files
VERSION  = 0.5
DEFINES += VERSION=\\\"$$VERSION\\\"

# Android
android: QT += androidextras

# iOS
ios: QT += gui gui-private # To get a UIView from a QML view http://stackoverflow.com/a/15556178/1204395
ios: QTPLUGIN +=  qsqlite # https://bugreports.qt-project.org/browse/QTBUG-35195
ios: LIBS += -framework UIKit

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(android/android.pri)
include(ios/ios.pri)
