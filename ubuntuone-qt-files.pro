QT    += qml quick network sql
android: QT += androidextras
TARGET = U1Files

VERSION = 0.1
DEFINES += VERSION=\\\"$$VERSION\\\"

# To update the translations:
# $ lupdate src -ts translations/es_ES.ts
# And to compile them:
# $ lrelease translations/*.ts ; mv translations/*.qm resources

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/liboauthcpp/third-party.liboauthcpp.pri)
include(android/android.pri)
