HEADERS += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.h
SOURCES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.cpp
OTHER_FILES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.qml

INCLUDEPATH += $$PWD

include(styles/ubuntuone-qt-files.gui.styles.pri)
include(login/ubuntuone-qt-files.gui.login.pri)
