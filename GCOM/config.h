#ifndef LAMP_CONFIG_H
#define LAMP_CONFIG_H

#include "libcfg.h"
#include <windows.h>

namespace Lamp
{
    // number parameters
    const ULONG FLOAT_PRECISION     = 6;
    const FLOAT FLOAT_EPSILON       = 0.000001f;
    const ULONG DOUBLE_PRECISION    = 12;
    const DOUBLE DOUBLE_EPSILON     = 0.000000000001;
    const DOUBLE ANGLE_EPSILON      = 0.05;
    const DOUBLE RAD2DEG            = 57.295779513082320876846364344191;
    const DOUBLE SQRT_2             = 1.4142135623730950488016887242097;
    const DOUBLE SQRT_3             = 1.7320508075688772935274463415059;
    const DOUBLE SQRT_5             = 2.2360679774997896964091736687313;
    const DOUBLE SQRT_7             = 2.6457513110645905905016157536393;
}

#endif // LAMP_CONFIG_H
