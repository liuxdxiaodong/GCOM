#ifndef LAMP_CAMCFG_H
#define LAMP_CAMCFG_H

#include "cambox_global.h"
#include "camdef.h"
#include <KSJApi.h>

namespace Lamp
{
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
    class CAMBOX_EXPORT CamCfg
    {
    public:
        static CamType CAM_TYPE;
        static INT IMAGE_WIDTH;
        static INT IMAGE_HEIGHT;
        static INT IMAGE_LENGTH;
        static INT ZOOM;
        static INT ZOOM_IMAGE_WIDTH;
        static INT ZOOM_IMAGE_HEIGHT;
        static INT ZOOM_IMAGE_LENGTH;
        static ULONG IMAGE_CYCLE;
    };

    CAMBOX_EXPORT void updateCamCfg(
        const CamType& camType
        );
    // camera adapter
    const ULONG KSJ_PARAM_NUM = KSJ_BLACKLEVEL_THRESHOLD_HI + 1;
    typedef struct _CamAdpt
    {
        ULONG iIndex;
        ULONG iCamId;
        HANDLE iRecMutex;
        volatile bool iIsRec;
        cv::Mat iImage;
        INT iParam[KSJ_PARAM_NUM];
    } CamAdpt, *PCamAdpt;
}

#endif // LAMP_CAMCFG_H
