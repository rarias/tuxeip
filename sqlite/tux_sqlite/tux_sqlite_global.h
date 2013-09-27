#ifndef TUX_SQLITE_GLOBAL_H
#define TUX_SQLITE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(TUX_SQLITE_LIBRARY)
#  define TUX_SQLITESHARED_EXPORT Q_DECL_EXPORT
#else
#  define TUX_SQLITESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // TUX_SQLITE_GLOBAL_H
