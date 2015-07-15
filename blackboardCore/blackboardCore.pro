#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T12:14:15
#
#-------------------------------------------------

QT       += widgets

TARGET = blackboardCore
TEMPLATE = lib

DEFINES += BLACKBOARDCORE_LIBRARY

SOURCES += BlackboardCore.cpp \
    BbScene.cpp

HEADERS += BlackboardCore.h\
        blackboardcore_global.h \
    BbScene.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
