#ifndef LAMP_IMAGEDEF_H
#define LAMP_IMAGEDEF_H

#include "../config.h"

namespace Lamp
{
    typedef enum _ActType
    {
        AT_Edge = 0,
        AT_Blade,
        AT_Unknown = -1
    } ActType, *PActType;

    typedef struct _ImgData
    {
        cv::Mat iOriImg;
        cv::Mat iMdfImg;
        cv::Mat iDspImg;
    } ImgData, *PImgData;
}

#endif // LAMP_IMAGEDEF_H
