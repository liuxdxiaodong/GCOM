#ifndef COMPORT_GLOBAL_H
#define COMPORT_GLOBAL_H

#include "../config.h"
#include <QtCore/qglobal.h>

#ifdef COMPORT_LIB
# define COMPORT_EXPORT Q_DECL_EXPORT
#else
# define COMPORT_EXPORT Q_DECL_IMPORT
#endif

#endif // COMPORT_GLOBAL_H
