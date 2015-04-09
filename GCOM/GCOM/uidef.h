#ifndef LAMP_UIDEF_H
#define LAMP_UIDEF_H

#include "../config.h"
#include <QtGui/QColor>

namespace Lamp
{
    const QColor DISABLED_COLOR(255, 170, 0);
    const QColor ENABLED_COLOR(0, 170, 0);

    typedef enum _GTBtnId
    {
        GTBI_ZoomFit = 0x0000,
        GTBI_ZoomIn,
        GTBI_ZoomOut,
        GTBI_LightOn,
        GTBI_LightOff,
        GTBI_AxisUp = 0x0100,
        GTBI_AxisDown,
        GTBI_AxisLeft,
        GTBI_AxisRight,
        GTBI_Max = GTBI_AxisRight,
        GTBI_Unknown = -1
    } GTBtnId, *PGTBtnId;

    typedef enum _GCBtnId
    {
        GCBI_Home = 0x0000,
        GCBI_Main1 = 0x0100,
        GCBI_Main2,
        GCBI_Main3,
        GCBI_Main4,
        GCBI_Cutter1 = 0x0200,
        GCBI_Cutter2,
        GCBI_Cutter3,
        GCBI_Measure1 = 0x0300,
        GCBI_Measure2,
        GCBI_Measure3,
        GCBI_Window1 = 0x0400,
        GCBI_Window2,
        GCBI_Window3,
        GCBI_CAD1 = 0x0500,
        GCBI_CAD2,
        GCBI_CAD3,
        GCBI_CAD4,
        GCBI_Max = GCBI_CAD4,
        GCBI_Unknown = -1
    } GCBtnId, *PGCBtnId;
}

#endif // LAMP_UIDEF_H
