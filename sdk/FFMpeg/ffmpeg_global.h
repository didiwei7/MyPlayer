#ifndef FFMPEG_GLOBAL_H
#define FFMPEG_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(FFMPEG_LIBRARY)
#  define FFMPEGSHARED_EXPORT Q_DECL_EXPORT
#else
#  define FFMPEGSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // FFMPEG_GLOBAL_H
