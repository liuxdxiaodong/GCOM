#ifndef CAMBOX_GLOBAL_H
#define CAMBOX_GLOBAL_H

#include "../config.h"
#include <QtCore/qglobal.h>

#ifdef CAMBOX_LIB
# define CAMBOX_EXPORT Q_DECL_EXPORT
#else
# define CAMBOX_EXPORT Q_DECL_IMPORT
#endif

#endif // CAMBOX_GLOBAL_H
