#ifndef TEST_DLL2_GLOBAL_H
#define TEST_DLL2_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TEST_DLL2_LIBRARY)
#  define TEST_DLL2_EXPORT Q_DECL_EXPORT
#else
#  define TEST_DLL2_EXPORT Q_DECL_IMPORT
#endif

#endif // TEST_DLL2_GLOBAL_H
