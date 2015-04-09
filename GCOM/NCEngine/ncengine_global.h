#ifndef NCENGINE_GLOBAL_H
#define NCENGINE_GLOBAL_H

#include "../config.h"
#include <QtCore/qglobal.h>

#ifdef NCENGINE_LIB
# define NCENGINE_EXPORT Q_DECL_EXPORT
#else
# define NCENGINE_EXPORT Q_DECL_IMPORT
#endif

#endif // NCENGINE_GLOBAL_H
