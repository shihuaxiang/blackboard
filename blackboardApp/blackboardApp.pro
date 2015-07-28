#-------------------------------------------------
#
# Project created by QtCreator 2015-07-15T12:12:41
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = blackboardApp
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp

HEADERS  += MainWindow.h

FORMS    +=

RESOURCES += \
    images.qrc

CONFIG(debug, debug|release){
    DESTDIR = $$PWD/../debug
    MOC_DIR += $$PWD/GeneratedFiles/debug
    OBJECTS_DIR += $$PWD/GeneratedFiles/debug
    UI_DIR += $$PWD/GeneratedFiles
    RCC_DIR += $$PWD/GeneratedFiles

    #libs
    LIBS += -L$$PWD/../debug
    LIBS += -lblackboardCore
}
