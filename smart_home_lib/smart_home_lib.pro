#-------------------------------------------------
#
# Project created by QtCreator 2020-10-05T01:30:13
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = smart_home_lib
TEMPLATE = lib
CONFIG += c++17 staticlib

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        csvfile.cpp \
        deviceinfo.cpp \
        mainmenu.cpp \
        measurement.cpp \
        network/defaultmessagefactory.cpp \
        network/message.cpp \
        network/networkmanager.cpp \
        network/qthttpnetworkmanager.cpp \
        network/requestmessage.cpp \
        network/responsemessage.cpp \
        smart_home_lib.cpp

HEADERS += \
        csvfile.h \
        deviceinfo.h \
        mainmenu.h \
        measurement.h \
        network/connection.h \
        network/defaultmessagefactory.h \
        network/message.h \
        network/messagefactory.h \
        network/networkmanager.h \
        network/qthttpnetworkmanager.h \
        network/requestmessage.h \
        network/responsemessage.h \
        smart_home_lib.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:unix: LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed

INCLUDEPATH += $$PWD/../qhttp-embed
DEPENDPATH += $$PWD/../qhttp-embed
