#ifndef LAMP_NCDEF_H
#define LAMP_NCDEF_H

#include "ncengine_global.h"
#include <QtCore/QString>
#include <QtCore/QStringList>

namespace Lamp
{
    const QString LOCAL_HOST = "127.0.0.1";
    //const QString LOCAL_HOST = "192.168.1.104";
    const quint16 DEFAULT_PORT = 62937;
    const double TRANS_STEP = 0.001;
    const double ROTAT_STEP = 0.001;
    const QString SHARED_FOLDER = "GNCShared";
    const QString JOB_FILENAME = "NCJob.nc";

    typedef enum _NCWorkMode
    {
        NCWM_Man = 0,
        NCWM_Auto,
        NCWM_Max = NCWM_Auto,
        NCWM_Unknown = -1
    } NCWorkMode, *PNCWorkMode;
}

#endif // LAMP_NCDEF_H
