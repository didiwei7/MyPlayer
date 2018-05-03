#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T02:44:40
#
#-------------------------------------------------

QT       -= gui

TARGET = OpenCV
TEMPLATE = lib
DESTDIR   = ../../bin

DEFINES += OPENCV_LIBRARY

SOURCES += opencv.cpp

HEADERS += opencv.h\
        opencv_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
