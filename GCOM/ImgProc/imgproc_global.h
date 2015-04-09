#ifndef IMGPROC_GLOBAL_H
#define IMGPROC_GLOBAL_H

#include "../config.h"
#include <QtCore/qglobal.h>

#ifdef IMGPROC_LIB
# define IMGPROC_EXPORT Q_DECL_EXPORT
#else
# define IMGPROC_EXPORT Q_DECL_IMPORT
#endif

#endif // IMGPROC_GLOBAL_H
