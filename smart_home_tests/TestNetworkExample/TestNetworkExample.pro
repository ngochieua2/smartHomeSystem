QT += testlib
QT -= gui
QT += network

CONFIG += c++17 qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

HEADERS += \
    examplerequestmessage.h \
    exampleresponsemessage.h

SOURCES +=  tst_testnetworkexample.cpp \
    examplerequestmessage.cpp \
    exampleresponsemessage.cpp

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../xbin/ -lqhttp-embed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../xbin/ -lqhttp-embed
else:unix: LIBS += -L$$OUT_PWD/../../xbin/ -lqhttp-embed

INCLUDEPATH += $$PWD/../../qhttp-embed
DEPENDPATH += $$PWD/../../qhttp-embed

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../../smart_home_lib/release/ -lsmart_home_lib
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../../smart_home_lib/debug/ -lsmart_home_lib
else:unix: LIBS += -L$$OUT_PWD/../../smart_home_lib/ -lsmart_home_lib

INCLUDEPATH += $$PWD/../../smart_home_lib
DEPENDPATH += $$PWD/../../smart_home_lib

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../smart_home_lib/release/libsmart_home_lib.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../smart_home_lib/debug/libsmart_home_lib.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../smart_home_lib/release/smart_home_lib.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../../smart_home_lib/debug/smart_home_lib.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../../smart_home_lib/libsmart_home_lib.a
