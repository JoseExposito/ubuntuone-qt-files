HEADERS += \
    src/com/egg-software/ubuntuone-qt-files/platform/PlatformFactory.h \
    src/com/egg-software/ubuntuone-qt-files/platform/PlatformUtils.h \
    src/com/egg-software/ubuntuone-qt-files/platform/AndroidUtils.h \
    src/com/egg-software/ubuntuone-qt-files/platform/iOSUtils.h

SOURCES += \
    src/com/egg-software/ubuntuone-qt-files/platform/PlatformFactory.cpp \
    src/com/egg-software/ubuntuone-qt-files/platform/PlatformUtils.cpp \
    src/com/egg-software/ubuntuone-qt-files/platform/AndroidUtils.cpp

OBJECTIVE_SOURCES += \
    src/com/egg-software/ubuntuone-qt-files/platform/iOSUtils.mm

INCLUDEPATH += $$PWD
