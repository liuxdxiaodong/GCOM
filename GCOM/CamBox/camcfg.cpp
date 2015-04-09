#include "camcfg.h"

namespace Lamp
{
    CamType CamCfg::CAM_TYPE            = CT_130;
    INT CamCfg::IMAGE_WIDTH             = Cam130::IMAGE_WIDTH;
    INT CamCfg::IMAGE_HEIGHT            = Cam130::IMAGE_HEIGHT;
    INT CamCfg::IMAGE_LENGTH            = Cam130::IMAGE_LENGTH;
    INT CamCfg::ZOOM                    = Cam130::ZOOM;
    INT CamCfg::ZOOM_IMAGE_WIDTH        = Cam130::ZOOM_IMAGE_WIDTH;
    INT CamCfg::ZOOM_IMAGE_HEIGHT       = Cam130::ZOOM_IMAGE_HEIGHT;
    INT CamCfg::ZOOM_IMAGE_LENGTH       = Cam130::ZOOM_IMAGE_LENGTH;
    ULONG CamCfg::IMAGE_CYCLE           = Cam130::IMAGE_CYCLE;
    
    void updateCamCfg(
        const CamType& camType
        )
    {
        CamCfg::CAM_TYPE = camType;
        switch(camType)
        {
        case CT_130:
            {
                CamCfg::IMAGE_WIDTH         = Cam130::IMAGE_WIDTH;
                CamCfg::IMAGE_HEIGHT        = Cam130::IMAGE_HEIGHT;
                CamCfg::IMAGE_LENGTH        = Cam130::IMAGE_LENGTH;
                CamCfg::ZOOM                = Cam130::ZOOM;
                CamCfg::ZOOM_IMAGE_WIDTH    = Cam130::ZOOM_IMAGE_WIDTH;
                CamCfg::ZOOM_IMAGE_HEIGHT   = Cam130::ZOOM_IMAGE_HEIGHT;
                CamCfg::ZOOM_IMAGE_LENGTH   = Cam130::ZOOM_IMAGE_LENGTH;
                CamCfg::IMAGE_CYCLE         = Cam130::IMAGE_CYCLE;
            }
            break;
        case CT_500:
            {
                CamCfg::IMAGE_WIDTH         = Cam500::IMAGE_WIDTH;
                CamCfg::IMAGE_HEIGHT        = Cam500::IMAGE_HEIGHT;
                CamCfg::IMAGE_LENGTH        = Cam500::IMAGE_LENGTH;
                CamCfg::ZOOM                = Cam500::ZOOM;
                CamCfg::ZOOM_IMAGE_WIDTH    = Cam500::ZOOM_IMAGE_WIDTH;
                CamCfg::ZOOM_IMAGE_HEIGHT   = Cam500::ZOOM_IMAGE_HEIGHT;
                CamCfg::ZOOM_IMAGE_LENGTH   = Cam500::ZOOM_IMAGE_LENGTH;
                CamCfg::IMAGE_CYCLE         = Cam500::IMAGE_CYCLE;
            }
            break;
        case CT_1400:
            {
                CamCfg::IMAGE_WIDTH         = Cam1400::IMAGE_WIDTH;
                CamCfg::IMAGE_HEIGHT        = Cam1400::IMAGE_HEIGHT;
                CamCfg::IMAGE_LENGTH        = Cam1400::IMAGE_LENGTH;
                CamCfg::ZOOM                = Cam1400::ZOOM;
                CamCfg::ZOOM_IMAGE_WIDTH    = Cam1400::ZOOM_IMAGE_WIDTH;
                CamCfg::ZOOM_IMAGE_HEIGHT   = Cam1400::ZOOM_IMAGE_HEIGHT;
                CamCfg::ZOOM_IMAGE_LENGTH   = Cam1400::ZOOM_IMAGE_LENGTH;
                CamCfg::IMAGE_CYCLE         = Cam1400::IMAGE_CYCLE;
            }
            break;
        default:
            break;
        }
    }
}
