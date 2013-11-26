HEADERS += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.h
SOURCES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.cpp
OTHER_FILES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.qml \
    src/com/egg-software/ubuntuone-qt-files/gui/LoadingSpinner.qml \
    src/com/egg-software/ubuntuone-qt-files/gui/MainWindowToolbar.qml

INCLUDEPATH += $$PWD

include(styles/ubuntuone-qt-files.gui.styles.pri)
include(login/ubuntuone-qt-files.gui.login.pri)
include(nodelist/ubuntuone-qt-files.gui.nodelist.pri)
