QT       -= gui

TARGET    = FFMpeg
TEMPLATE  = lib
DESTDIR   = ../../bin

DEFINES  += FFMPEG_LIBRARY

SOURCES  += ffmpeg.cpp

HEADERS  += ffmpeg.h\
            ffmpeg_global.h

# FFMpeg
INCLUDEPATH += C:/ffmpeg/x86/dev/include
win32:{
    LIBS += C:/ffmpeg/x86/dev/lib/avcodec.lib
    LIBS += C:/ffmpeg/x86/dev/lib/avdevice.lib
    LIBS += C:/ffmpeg/x86/dev/lib/avfilter.lib
    LIBS += C:/ffmpeg/x86/dev/lib/avformat.lib
    LIBS += C:/ffmpeg/x86/dev/lib/avutil.lib
    LIBS += C:/ffmpeg/x86/dev/lib/postproc.lib
    LIBS += C:/ffmpeg/x86/dev/lib/swresample.lib
    LIBS += C:/ffmpeg/x86/dev/lib/swscale.lib
}

# SDL
INCLUDEPATH += C:/sdl/include
win32:{
    LIBS += C:/sdl/lib/SDL2.lib
}

unix {
    target.path = /usr/lib
    INSTALLS += target
}
