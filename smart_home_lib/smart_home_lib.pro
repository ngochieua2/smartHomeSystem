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
        basicmeasurement.cpp \
        controllermenu.cpp \
        controllerproxy.cpp \
        csvfile.cpp \
        devicefactory.cpp \
        deviceinfo.cpp \
        filter.cpp \
        lightswitch.cpp \
        lightswitchfactory.cpp \
        lightswitchmenu.cpp \
        lightswitchproxy.cpp \
        mainmenu.cpp \
        measurement.cpp \
        network/defaultmessagefactory.cpp \
        network/message.cpp \
        network/networkmanager.cpp \
        network/qthttpnetworkmanager.cpp \
        network/requestmessage.cpp \
        network/responsemessage.cpp \
        realcontroller.cpp \
        reallightswitch.cpp \
        realsprinklersystem.cpp \
        realthermostat.cpp \
        smarthomecontroller.cpp \
        smarthomedevice.cpp \
        sprinklersystem.cpp \
        sprinklersystemfactory.cpp \
        sprinklersystemmenu.cpp \
        sprinklersystemproxy.cpp \
        switchstatus.cpp \
        temperature.cpp \
        thermostat.cpp \
        thermostatfactory.cpp \
        thermostatmenu.cpp \
        thermostatproxy.cpp

HEADERS += \
        basicmeasurement.h \
        controllermenu.h \
        controllerproxy.h \
        csvfile.h \
        devicefactory.h \
        deviceinfo.h \
        filter.h \
        lightswitch.h \
        lightswitchfactory.h \
        lightswitchmenu.h \
        lightswitchproxy.h \
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
        realcontroller.h \
        reallightswitch.h \
        realsprinklersystem.h \
        realthermostat.h \
        smarthomecontroller.h \
        smarthomedevice.h \
        sprinklersystem.h \
        sprinklersystemfactory.h \
        sprinklersystemmenu.h \
        sprinklersystemproxy.h \
        switchstatus.h \
        temperature.h \
        thermostat.h \
        thermostatfactory.h \
        thermostatmenu.h \
        thermostatproxy.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed
else:unix: LIBS += -L$$OUT_PWD/../xbin/ -lqhttp-embed

INCLUDEPATH += $$PWD/../qhttp-embed
DEPENDPATH += $$PWD/../qhttp-embed
