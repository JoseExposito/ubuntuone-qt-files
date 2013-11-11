SOURCES     += src/com/egg-software/ubuntuone-qt-files/main.cpp
OTHER_FILES += src/com/egg-software/ubuntuone-qt-files/qmldir
RESOURCES   += src/com/egg-software/ubuntuone-qt-files/qml.qrc

INCLUDEPATH += $$PWD

include(gui/ubuntuone-qt-files.gui.pri)
include(network/ubuntuone-qt-files.network.pri)
include(database/ubuntuone-qt-files.database.pri)
