HEADERS += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.h \
    src/com/egg-software/ubuntuone-qt-files/gui/BaseWindow.h

SOURCES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.cpp \
    src/com/egg-software/ubuntuone-qt-files/gui/BaseWindow.cpp

OTHER_FILES += src/com/egg-software/ubuntuone-qt-files/gui/MainWindow.qml \
    src/com/egg-software/ubuntuone-qt-files/gui/MainWindowToolbar.qml

INCLUDEPATH += $$PWD

include(util/ubuntuone-qt-files.gui.util.pri)
include(login/ubuntuone-qt-files.gui.login.pri)
include(nodelist/ubuntuone-qt-files.gui.nodelist.pri)
