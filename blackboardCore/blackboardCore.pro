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
    BbScene.cpp \
    BbView.cpp \
    BbLine.cpp \
    BbUtil.cpp \
    BbText.cpp

HEADERS += BlackboardCore.h\
        blackboardcore_global.h \
    BbScene.h \
    BbView.h \
    BbLine.h \
    BbUtil.h \
    BbText.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../debug
    MOC_DIR += $$PWD/GeneratedFiles/debug
    OBJECTS_DIR += $$PWD/GeneratedFiles/debug
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles

    #libs
    LIBS += -L$$PWD/../debug
}

RESOURCES += \
    images.qrc
