#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T12:14:15
#
#-------------------------------------------------

QT       += widgets
CONFIG += c++11

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

CONFIG(debug, debug|release) {
    deploy_type = debug
} else {
    deploy_type = release
}

DESTDIR = $$PWD/../$$deploy_type
MOC_DIR += $$PWD/GeneratedFiles/$$deploy_type
OBJECTS_DIR += $$PWD/GeneratedFiles/$$deploy_type
UI_DIR += $$PWD/GeneratedFiles
RCC_DIR += $$PWD/GeneratedFiles

#libs
LIBS += -L$$PWD/../$$deploy_type

RESOURCES += \
    images.qrc
