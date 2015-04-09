#ifndef LAMP_CAMDEF_H
#define LAMP_CAMDEF_H

#include "../config.h"

namespace Lamp
{
    const ULONG CAM_WAIT_TIMEOUT    = 1000;
    const ULONG CAM_MAX_NUM         = 2;
    // grab mode
    typedef enum _GrabMode
    {
        GM_FreeRunning = 0,
        GM_TriggeredExt,
        GM_Unknown = -1
    } GrabMode, *PGrabMode;
    // camera type
    typedef enum _CamType
    {
        CT_130 = 0,
        CT_500,
        CT_1400,
        CT_Unknown = -1
    } CamType, *PCamType;
    // IMAGE -----------------------------------------
    //       | ROI -----------------------------     |
    //       |     | AREA ---------------      |     |
    //       |     |      |             |      |     |
    //       |     |      |             |      |     |
    //       |     |      |             |      |     |
    //       |     |      |             |      |     |
    //       |     |      ---------------      |     |
    //       |     -----------------------------     |
    //       -----------------------------------------
    namespace Cam130
    {
        const INT IMAGE_WIDTH       = 1280;
        const INT IMAGE_HEIGHT      = 1024;
        const INT IMAGE_LENGTH      = IMAGE_WIDTH * IMAGE_HEIGHT;
        const INT ZOOM              = 2;
        const INT ZOOM_IMAGE_WIDTH  = IMAGE_WIDTH / ZOOM;
        const INT ZOOM_IMAGE_HEIGHT = IMAGE_HEIGHT / ZOOM;
        const INT ZOOM_IMAGE_LENGTH = ZOOM_IMAGE_WIDTH * ZOOM_IMAGE_HEIGHT * 3;
        const ULONG IMAGE_CYCLE     = 130;
    }
    namespace Cam500
    {
        const INT IMAGE_WIDTH       = 2592;
        const INT IMAGE_HEIGHT      = 1944;
        const INT IMAGE_LENGTH      = IMAGE_WIDTH * IMAGE_HEIGHT;
        const INT ZOOM              = 4;
        const INT ZOOM_IMAGE_WIDTH  = IMAGE_WIDTH / ZOOM;
        const INT ZOOM_IMAGE_HEIGHT = IMAGE_HEIGHT / ZOOM;
        const INT ZOOM_IMAGE_LENGTH = ZOOM_IMAGE_WIDTH * ZOOM_IMAGE_HEIGHT * 3;
        const ULONG IMAGE_CYCLE     = 167;
    }
    namespace Cam1400
    {
        const INT IMAGE_WIDTH       = 4384;
        const INT IMAGE_HEIGHT      = 3288;
        const INT IMAGE_LENGTH      = IMAGE_WIDTH * IMAGE_HEIGHT;
        const INT ZOOM              = 8;
        const INT ZOOM_IMAGE_WIDTH  = IMAGE_WIDTH / ZOOM;
        const INT ZOOM_IMAGE_HEIGHT = IMAGE_HEIGHT / ZOOM;
        const INT ZOOM_IMAGE_LENGTH = ZOOM_IMAGE_WIDTH * ZOOM_IMAGE_HEIGHT * 3;
        const ULONG IMAGE_CYCLE     = 200;
    }
}

#endif // LAMP_CAMDEF_H
