#-------------------------------------------------
#
# Project created by QtCreator 2018-04-15T02:45:15
#
#-------------------------------------------------

QT       -= gui

TARGET = Music
TEMPLATE = lib
DESTDIR   = ../../bin

DEFINES += MUSIC_LIBRARY

SOURCES += music.cpp

HEADERS += music.h\
        music_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
