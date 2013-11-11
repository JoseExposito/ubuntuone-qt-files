QT    += qml quick widgets network sql
TARGET = ubuntuoneqtfiles

VERSION = 0.1
DEFINES += VERSION=\\\"$$VERSION\\\"

include(src/com/egg-software/ubuntuone-qt-files/ubuntuone-qt-files.pri)
include(resources/resources.pri)
include(third-party/o2/third-party.o2.pri)
