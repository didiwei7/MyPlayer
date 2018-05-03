QT       += core
QT       += gui
QT       += concurrent
QT       += winextras
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET    = MyPlayer
TEMPLATE  = app
DESTDIR   = ../bin

CONFIG   += c++11

VERSION   = 1.0.0.0
QMAKE_TARGET_PRODUCT = MyPlayer
QMAKE_TARGET_COMPANY = Didiwei.com
QMAKE_TARGET_DESCRIPTION = Didiwei Player
QMAKE_TARGET_COPYRIGHT   = Didiwei

SOURCES  += main.cpp \
            mainwindow/mainwindow.cpp \
            photo/photo.cpp \
            video/video.cpp \
            mainwindow/mainwidget.cpp

HEADERS  += \
            mainwindow/mainwindow.h \
            photo/photo.h \
            video/video.h \
            mainwindow/mainwidget.h

RESOURCES += \
             ui.qrc


# QFlex
INCLUDEPATH += C:/Qt/QtMyCtrls/include/QFlex
win32: LIBS += C:/Qt/QtMyCtrls/lib/QFlex.lib

# QNavigationBar
INCLUDEPATH += C:/Qt/QtMyCtrls/include/QNavigationBar
win32: LIBS += C:/Qt/QtMyCtrls/lib/QNavigationBar.lib

# QMySlider
INCLUDEPATH += C:/Qt/QtMyCtrls/include/QMySlider
win32: LIBS += C:/Qt/QtMyCtrls/lib/QMySlider.lib

# OpenCV
INCLUDEPATH += C:/opencv300/opencv/build/include
INCLUDEPATH += C:/opencv300/opencv/build/include/opencv/
INCLUDEPATH += C:/opencv300/opencv/build/include/opencv2/
win32:CONFIG(debug, debug|release): LIBS += C:/opencv300/opencv/build/x86/vc12/lib/opencv_world300d.lib
else:win32:CONFIG(release, debug|release): LIBS += C:/opencv300/opencv/build/x86/vc12/lib/opencv_world300.lib

#INCLUDEPATH += C:/opencv331/opencv/build/include
#INCLUDEPATH += C:/opencv331/opencv/build/include/opencv/
#INCLUDEPATH += C:/opencv331/opencv/build/include/opencv2/
#win32:CONFIG(debug, debug|release): LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331d.lib
#else:win32:CONFIG(release, debug|release): LIBS += C:/opencv331/opencv/build/x64/vc14/lib/opencv_world331.lib

# QtAV
INCLUDEPATH += C:/Qt/QtAV/include
win32: LIBS += C:/Qt/QtAV/lib/QtAV1.lib
win32: LIBS += C:/Qt/QtAV/lib/QtAVWidgets1.lib

#win32:{
#    LIBS  += ../bin/QFlex.lib
#}

# QtAV
#INCLUDEPATH += C:/QtAV/include
#win32:{
#    LIBS += -LC:/QtAV/lib/avcodec.lib
#    LIBS += -LC:/QtAV/lib/avdevice.lib
#    LIBS += -LC:/QtAV/lib/avfilter.lib
#    LIBS += -LC:/QtAV/lib/avformat.lib
#    LIBS += -LC:/QtAV/lib/avresample.lib
#    LIBS += -LC:/QtAV/lib/avutil.lib
#    LIBS += -LC:/QtAV/lib/swresample.lib
#    LIBS += -LC:/QtAV/lib/swscale.lib
#}

# FFMpeg
#INCLUDEPATH += C:/ffmpeg/x86/dev/include
#win32:{
#    LIBS += C:/ffmpeg/x86/dev/lib/avcodec.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/avdevice.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/avfilter.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/avformat.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/avutil.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/postproc.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/swresample.lib
#    LIBS += C:/ffmpeg/x86/dev/lib/swscale.lib
#}

# SDL
#INCLUDEPATH += C:/sdl/include
#win32: LIBS += C:/sdl/lib/SDL2.lib

# QFlex
#INCLUDEPATH += C:/Qt/MyControls/include/QFlex
#win32:CONFIG(release, debug|release): LIBS += C:/Qt/MyControls/bin/QFlex.lib
#else:win32:CONFIG(debug, debug|release): LIBS += C:/Qt/MyControls/bin/QFlexd.lib








