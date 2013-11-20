HEADERS += \
    third-party/liboauthcpp/base64.h \
    third-party/liboauthcpp/HMAC_SHA1.h \
    third-party/liboauthcpp/liboauthcpp/liboauthcpp.h \
    third-party/liboauthcpp/SHA1.h \
    third-party/liboauthcpp/urlencode.h

SOURCES += \
    third-party/liboauthcpp/base64.cpp \
    third-party/liboauthcpp/HMAC_SHA1.cpp \
    third-party/liboauthcpp/liboauthcpp.cpp \
    third-party/liboauthcpp/SHA1.cpp \
    third-party/liboauthcpp/urlencode.cpp

INCLUDEPATH += $$PWD
