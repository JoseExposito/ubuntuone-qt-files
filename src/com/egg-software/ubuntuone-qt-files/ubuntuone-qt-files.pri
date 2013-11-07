SOURCES += src/com/egg-software/ubuntuone-qt-files/main.cpp \
    src/com/egg-software/ubuntuone-qt-files/MainWindow.cpp

OTHER_FILES += src/com/egg-software/ubuntuone-qt-files/qmldir \
    src/com/egg-software/ubuntuone-qt-files/MainWindow.qml
RESOURCES   += src/com/egg-software/ubuntuone-qt-files/qml.qrc

INCLUDEPATH += $$PWD

include(gui/ubuntuone-qt-files.gui.pri)
include(util/ubuntuone-qt-files.util.pri)
include(styles/ubuntuone-qt-files.styles.pri)
include(network/ubuntuone-qt-files.network.pri)

HEADERS += \
    src/com/egg-software/ubuntuone-qt-files/MainWindow.h
