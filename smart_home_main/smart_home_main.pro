QT -= gui
QT += network

TARGET = smart_home
CONFIG += c++17 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        main.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../smart_home_lib/release/ -lsmart_home_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../smart_home_lib/debug/ -lsmart_home_lib
else:unix: LIBS += -L$$OUT_PWD/../smart_home_lib/ -lsmart_home_lib

INCLUDEPATH += $$PWD/../smart_home_lib
DEPENDPATH += $$PWD/../smart_home_lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../smart_home_lib/release/libsmart_home_lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../smart_home_lib/debug/libsmart_home_lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../smart_home_lib/release/smart_home_lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../smart_home_lib/debug/smart_home_lib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../smart_home_lib/libsmart_home_lib.a

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:unix: LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed

INCLUDEPATH += $$PWD/../qhttp-embed
DEPENDPATH += $$PWD/../qhttp-embed
