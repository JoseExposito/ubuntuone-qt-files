QT    += qml quick network sql widgets
android: QT += androidextras

# In iOS the modules are not added automatically
# http://qt-project.org/wiki/Qt_for_iOS_known_issues -> https://bugreports.qt-project.org/browse/QTBUG-35195
# https://bugreports.qt-project.org/browse/QTBUG-35690
ios: QTPLUGIN +=  qsqlite

TARGET = U1Files

VERSION = 0.2
DEFINES += VERSION=\\\"$$VERSION\\\"

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(android/android.pri)
