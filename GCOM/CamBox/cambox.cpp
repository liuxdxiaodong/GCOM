#include "cambox.h"

#pragma comment(lib, "KSJApi.lib")

namespace Lamp
{
    CamBox::CamBox(
        const ULONG& count
        )
        : iOpenMutex(NULL),
        iIsOpened(false),
        iCount(count)
    {
        this->iOpenMutex = CreateMutex(NULL, FALSE, NULL);
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            this->iCamAdpt[caIdx].iIndex = -1;
            this->iCamAdpt[caIdx].iCamId = -1;
            this->iCamAdpt[caIdx].iRecMutex = CreateMutex(NULL, FALSE, NULL);
            this->iCamAdpt[caIdx].iIsRec = false;
            ZeroMemory(this->iCamAdpt[caIdx].iParam, sizeof(int) * KSJ_PARAM_NUM);
        }
    }

    CamBox::~CamBox()
    {
        this->close();
        CloseHandle(this->iOpenMutex);
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            CloseHandle(this->iCamAdpt[caIdx].iRecMutex);
        }
    }

    bool CamBox::open(
        const GrabMode& mode,
        ULONG idMap[]
        )
    {
        // close current camera
        if(this->iIsOpened)
        {
            if(!this->close())
            {
                return false;
            }
        }
        // open camera
        KSJ_Init();
        if(KSJ_DeviceGetCount() < this->iCount)
        {
            KSJ_UnInit();
            return false;
        }
        KSJ_TRIGGERMODE triggerMode = KSJ_TRIGGER_INTERNAL;
        switch(mode)
        {
        case GM_FreeRunning:
            triggerMode = KSJ_TRIGGER_INTERNAL;
            break;
        case GM_TriggeredExt:
            triggerMode = KSJ_TRIGGER_EXTERNAL;
            break;
        default:
            return false;
        }
        bool isOK = true;
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            this->iCamAdpt[caIdx].iIndex = caIdx;
            isOK = this->readId(caIdx, this->iCamAdpt[caIdx].iCamId);
            if(!isOK)
            {
                return false;
            }
            idMap[this->iCamAdpt[caIdx].iCamId] = caIdx;
            this->iCamAdpt[caIdx].iImage = cv::Mat::zeros(CamCfg::IMAGE_HEIGHT, CamCfg::IMAGE_WIDTH, CV_8UC3);
            // load camera parameter
            QString fileName = "CAM";
            fileName += QString::number(this->iCamAdpt[caIdx].iCamId);
            fileName += "_PARAM.ini";
            if(!QFile::exists(fileName))
            {
                return false;
            }
            FILE* file = NULL;
            fopen_s(&file, fileName.toStdString().c_str(), "r");
            for(ULONG idx = 0; idx < KSJ_PARAM_NUM; ++idx)
            {
                fscanf_s(file, "%i", &this->iCamAdpt[caIdx].iParam[idx]);
            }
            fclose(file);
            KSJ_SetParam(caIdx, KSJ_EXPOSURE, this->iCamAdpt[caIdx].iParam[KSJ_EXPOSURE]);
            KSJ_SetParam(caIdx, KSJ_RED, this->iCamAdpt[caIdx].iParam[KSJ_RED]);
            KSJ_SetParam(caIdx, KSJ_GREEN, this->iCamAdpt[caIdx].iParam[KSJ_GREEN]);
            KSJ_SetParam(caIdx, KSJ_BLUE, this->iCamAdpt[caIdx].iParam[KSJ_BLUE]);
            KSJ_SetParam(caIdx, KSJ_GAMMA, this->iCamAdpt[caIdx].iParam[KSJ_GAMMA]);
            KSJ_PreviewSetFieldOfView(caIdx, this->iCamAdpt[caIdx].iParam[KSJ_PREVIEW_COLUMNSTART], this->iCamAdpt[caIdx].iParam[KSJ_PREVIEW_ROWSTART], CamCfg::IMAGE_WIDTH, CamCfg::IMAGE_HEIGHT, KSJ_SKIPNONE, KSJ_SKIPNONE);
            KSJ_CaptureSetFieldOfView(caIdx, this->iCamAdpt[caIdx].iParam[KSJ_CAPTURE_COLUMNSTART], this->iCamAdpt[caIdx].iParam[KSJ_CAPTURE_ROWSTART], CamCfg::IMAGE_WIDTH, CamCfg::IMAGE_HEIGHT, KSJ_SKIPNONE, KSJ_SKIPNONE);
            KSJ_SetParam(caIdx, KSJ_HORIZONTALBLANK, this->iCamAdpt[caIdx].iParam[KSJ_HORIZONTALBLANK]);
            KSJ_SetParam(caIdx, KSJ_VERTICALBLANK, this->iCamAdpt[caIdx].iParam[KSJ_VERTICALBLANK]);
            KSJ_SetParam(caIdx, KSJ_FLIP, this->iCamAdpt[caIdx].iParam[KSJ_FLIP]);
            //KSJ_SetParam(caIdx, KSJ_BIN, this->iCamAdpt[caIdx].iParam[KSJ_BIN]);
            //KSJ_SetParam(caIdx, KSJ_MIRROR, this->iCamAdpt[caIdx].iParam[KSJ_MIRROR]);
            //KSJ_SetParam(caIdx, KSJ_CONTRAST, this->iCamAdpt[caIdx].iParam[KSJ_CONTRAST]);
            //KSJ_SetParam(caIdx, KSJ_BRIGHTNESS, this->iCamAdpt[caIdx].iParam[KSJ_BRIGHTNESS]);
            //KSJ_SetParam(caIdx, KSJ_VGAGAIN, this->iCamAdpt[caIdx].iParam[KSJ_VGAGAIN]);
            //KSJ_SetParam(caIdx, KSJ_CLAMPLEVEL, this->iCamAdpt[caIdx].iParam[KSJ_CLAMPLEVEL]);
            //KSJ_SetParam(caIdx, KSJ_CDSGAIN, this->iCamAdpt[caIdx].iParam[KSJ_CDSGAIN]);
            //KSJ_SetParam(caIdx, KSJ_RED_SHIFT, this->iCamAdpt[caIdx].iParam[KSJ_RED_SHIFT]);
            //KSJ_SetParam(caIdx, KSJ_GREEN_SHIFT, this->iCamAdpt[caIdx].iParam[KSJ_GREEN_SHIFT]);
            //KSJ_SetParam(caIdx, KSJ_BLUE_SHIFT, this->iCamAdpt[caIdx].iParam[KSJ_BLUE_SHIFT]);
            //KSJ_SetParam(caIdx, KSJ_COMPANDING, this->iCamAdpt[caIdx].iParam[KSJ_COMPANDING]);
            KSJ_GetParam(caIdx, KSJ_EXPOSURE_LINES, &this->iCamAdpt[caIdx].iParam[KSJ_EXPOSURE_LINES]);
            //KSJ_SetParam(caIdx, KSJ_SATURATION, this->iCamAdpt[caIdx].iParam[KSJ_SATURATION]);
            //KSJ_SetParam(caIdx, KSJ_TRIGGERDELAY, this->iCamAdpt[caIdx].iParam[KSJ_TRIGGERDELAY]);
            //KSJ_SetParam(caIdx, KSJ_STROBEDELAY, this->iCamAdpt[caIdx].iParam[KSJ_STROBEDELAY]);
            KSJ_SetParam(caIdx, KSJ_TRIGGER_MODE, triggerMode);
            this->iCamAdpt[caIdx].iParam[KSJ_TRIGGER_MODE] = triggerMode;
            KSJ_SetParam(caIdx, KSJ_TRIGGER_METHOD, this->iCamAdpt[caIdx].iParam[KSJ_TRIGGER_METHOD]);
            //KSJ_SetParam(caIdx, KSJ_BLACKLEVEL, this->iCamAdpt[caIdx].iParam[KSJ_BLACKLEVEL]);
            //KSJ_SetParam(caIdx, KSJ_BLACKLEVEL_THRESHOLD_AUTO, this->iCamAdpt[caIdx].iParam[KSJ_BLACKLEVEL_THRESHOLD_AUTO]);
            //KSJ_SetParam(caIdx, KSJ_BLACKLEVEL_THRESHOLD_LO, this->iCamAdpt[caIdx].iParam[KSJ_BLACKLEVEL_THRESHOLD_LO]);
            //KSJ_SetParam(caIdx, KSJ_BLACKLEVEL_THRESHOLD_HI, this->iCamAdpt[caIdx].iParam[KSJ_BLACKLEVEL_THRESHOLD_HI]);
        }
        if(this->iCount < CAM_MAX_NUM)
        {
            KSJ_PreviewSetCallback(0, cam0ImgGrabbed, this);
        }
        else
        {
            KSJ_PreviewSetCallback(0, cam0ImgGrabbed, this);
            KSJ_PreviewSetCallback(1, cam1ImgGrabbed, this);
        }
        this->iIsOpened = true;
        return true;
    }

    bool CamBox::close()
    {
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            KSJ_PreviewSetCallback(caIdx, NULL, NULL);
            KSJ_PreviewPause(caIdx, true);
            this->stopRec(caIdx);
        }
        this->iIsOpened = false;
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            KSJ_DeviceClose(caIdx);
            this->iCamAdpt[caIdx].iIndex = -1;
            this->iCamAdpt[caIdx].iCamId = -1;
            this->iCamAdpt[caIdx].iIsRec = false;
        }
        KSJ_UnInit();
        return true;
    }

    void CamBox::start()
    {
        if(!this->iIsOpened)
        {
            CamBox::errMsg(L"Camera isn't available!");
            return;
        }
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            KSJ_PreviewStart(caIdx, true);
        }
    }

    void CamBox::stop()
    {
        for(ULONG caIdx = 0; caIdx < this->iCount; ++caIdx)
        {
            KSJ_PreviewPause(caIdx, true);
        }
    }

    bool CamBox::isOpened() const
    {
        return this->iIsOpened;
    }

    GrabMode CamBox::grabMode(
        const ULONG& index
        ) const
    {
        if(this->iIsOpened)
        {
            KSJ_TRIGGERMODE triggerMode;
            KSJ_TriggerModeGet(this->iCamAdpt[index].iIndex, &triggerMode);
            GrabMode mode = GM_Unknown;
            switch(triggerMode)
            {
            case KSJ_TRIGGER_INTERNAL:
                mode = GM_FreeRunning;
                break;
            case KSJ_TRIGGER_EXTERNAL:
                mode = GM_TriggeredExt;
                break;
            default:
                break;
            }
            return mode;
        }
        else
        {
            return GM_Unknown;
        }
    }

    ULONG CamBox::deviceId(
        const ULONG& index
        ) const
    {
        if(this->iIsOpened)
        {
            return this->iCamAdpt[index].iCamId;
        }
        else
        {
            return -1;
        }
    }
    // camera parameters
    bool CamBox::readId(
        const ULONG& index,
        DWORD& id
        )
    {
        if(index >= this->iCount)
        {
            return false;
        }
        KSJ_DEVICETYPE deviceType = (KSJ_DEVICETYPE)-1;
        INT deviceIndex = -1;
        USHORT firmwareVersion = -1;
        KSJ_DeviceGetInformation(index, &deviceType, &deviceIndex, &firmwareVersion);
        id = deviceIndex;
        this->iCamAdpt[index].iCamId = id;
        return true;
    }

    bool CamBox::currentParam(
        const ULONG& index,
        INT param[]
        )
    {
        if(index >= this->iCount)
        {
            return false;
        }
        if(!this->iIsOpened)
        {
            return false;
        }
        CopyMemory(param, this->iCamAdpt[index].iParam, sizeof(INT) * KSJ_PARAM_NUM);
        return true;
    }

    bool CamBox::updateParam(
        const ULONG& index,
        INT param[]
        )
    {
        if(index >= this->iCount)
        {
            return false;
        }
        if(!this->iIsOpened)
        {
            return false;
        }
        for(ULONG idx = 0; idx < KSJ_PARAM_NUM; ++idx)
        {
            if(param[idx] != this->iCamAdpt[index].iParam[idx])
            {
                if(RET_SUCCESS != KSJ_SetParam(index, (KSJ_PARAM)idx, param[idx]))
                {
                    return false;
                }
                this->iCamAdpt[index].iParam[idx] = param[idx];
                switch(idx)
                {
                case KSJ_EXPOSURE:
                    KSJ_GetParam(index, KSJ_EXPOSURE_LINES, &param[KSJ_EXPOSURE_LINES]);
                    break;
                case KSJ_EXPOSURE_LINES:
                    KSJ_GetParam(index, KSJ_EXPOSURE, &param[KSJ_EXPOSURE]);
                    break;
                default:
                    break;
                }

            }
        }
        QString fileName = "CAM";
        fileName += QString::number(this->iCamAdpt[index].iCamId);
        fileName += "_PARAM.ini";
        FILE* file = NULL;
        fopen_s(&file, fileName.toStdString().c_str(), "w");
        for(ULONG idx = 0; idx < KSJ_PARAM_NUM; ++idx)
        {
            fprintf_s(file, "%i\n", this->iCamAdpt[index].iParam[idx]);
        }
        fclose(file);
        return true;
    }

    void CamBox::startRec(
        const ULONG& index
        )
    {
        if(index >= this->iCount)
        {
            return;
        }
        if(this->iCamAdpt[index].iIsRec)
        {
            return;
        }
        WaitForSingleObject(this->iCamAdpt[index].iRecMutex, INFINITE);
        this->iCamAdpt[index].iIsRec = true;
        ReleaseMutex(this->iCamAdpt[index].iRecMutex);
    }

    void CamBox::stopRec(
        const ULONG& index
        )
    {
        if(index >= this->iCount)
        {
            return;
        }
        if(!this->iCamAdpt[index].iIsRec)
        {
            return;
        }
        WaitForSingleObject(this->iCamAdpt[index].iRecMutex, INFINITE);
        this->iCamAdpt[index].iIsRec = false;
        ReleaseMutex(this->iCamAdpt[index].iRecMutex);
    }

    bool CamBox::isRec(
        const ULONG& index
        ) const
    {
        if(index >= this->iCount)
        {
            return false;
        }
        return this->iCamAdpt[index].iIsRec;
    }

    void CamBox::errMsg(
        const PTCHAR message
        )
    {
#ifdef SHOW_ERRMSG
        MessageBox(NULL, message, L"CamBox", MB_ICONERROR);
#endif // SHOW_ERRMSG
    }

    VOID WINAPI cam0ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param)
    {
        CamBox* camBox = static_cast<CamBox*>(param);
        WaitForSingleObject(camBox->iCamAdpt[0].iRecMutex, INFINITE);
        bool isRec = camBox->iCamAdpt[0].iIsRec;
        ReleaseMutex(camBox->iCamAdpt[0].iRecMutex);
        if(isRec)
        {
            CopyMemory(camBox->iCamAdpt[0].iImage.data, data, CamCfg::IMAGE_LENGTH);
            emit camBox->sendImg0(&camBox->iCamAdpt[0].iImage);
        }
    }

    VOID WINAPI cam1ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param)
    {
        CamBox* camBox = static_cast<CamBox*>(param);
        WaitForSingleObject(camBox->iCamAdpt[1].iRecMutex, INFINITE);
        bool isRec = camBox->iCamAdpt[1].iIsRec;
        ReleaseMutex(camBox->iCamAdpt[1].iRecMutex);
        if(isRec)
        {
            CopyMemory(camBox->iCamAdpt[1].iImage.data, data, CamCfg::IMAGE_LENGTH);
            emit camBox->sendImg1(&camBox->iCamAdpt[1].iImage);
        }
    }
}
