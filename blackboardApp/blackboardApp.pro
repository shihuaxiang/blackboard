#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T12:12:41
#
#-------------------------------------------------

QT       += core gui
CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blackboardApp
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    +=

RESOURCES += \
    images.qrc

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
LIBS += -lblackboardCore
