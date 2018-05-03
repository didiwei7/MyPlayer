#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T02:45:02
#
#-------------------------------------------------

QT       -= gui

TARGET = Video
TEMPLATE = lib
DESTDIR   = ../../bin

DEFINES += VIDEO_LIBRARY

SOURCES += video.cpp

HEADERS += video.h\
        video_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
