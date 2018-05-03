#ifndef MUSIC_GLOBAL_H
#define MUSIC_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MUSIC_LIBRARY)
#  define MUSICSHARED_EXPORT Q_DECL_EXPORT
#else
#  define MUSICSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // MUSIC_GLOBAL_H
