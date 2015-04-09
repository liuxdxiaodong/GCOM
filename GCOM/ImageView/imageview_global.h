#ifndef IMAGEVIEW_GLOBAL_H
#define IMAGEVIEW_GLOBAL_H

#include "../config.h"
#include <QtCore/qglobal.h>

#ifdef IMAGEVIEW_LIB
# define IMAGEVIEW_EXPORT Q_DECL_EXPORT
#else
# define IMAGEVIEW_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGEVIEW_GLOBAL_H
