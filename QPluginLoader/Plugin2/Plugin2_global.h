#ifndef PLUGIN2_GLOBAL_H
#define PLUGIN2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGIN2_LIBRARY)
#  define PLUGIN2_EXPORT Q_DECL_EXPORT
#else
#  define PLUGIN2_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGIN2_GLOBAL_H
