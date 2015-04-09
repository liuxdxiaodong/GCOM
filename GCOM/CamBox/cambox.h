#ifndef LAMP_CAMBOX_H
#define LAMP_CAMBOX_H

#include "cambox_global.h"
#include "camcfg.h"
#include <QtCore/QFile>
#include <QtCore/QObject>

namespace Lamp
{
    class CAMBOX_EXPORT CamBox : public QObject
    {
        Q_OBJECT

    signals:
        void sendImg0(
            const cv::Mat* image
            );
        void sendImg1(
            const cv::Mat* image
            );

    public:
        CamBox(
            const ULONG& count
            );
        ~CamBox();

    public:
        bool open(
            const GrabMode& mode,
            ULONG idMap[]
            );
        bool close();
        void start();
        void stop();
        bool isOpened() const;
        GrabMode grabMode(
            const ULONG& index
            ) const;
        ULONG deviceId(
            const ULONG& index
            ) const;
        // camera parameters
        bool readId(
            const ULONG& index,
            DWORD& id
            );
        bool currentParam(
            const ULONG& index,
            INT param[]
            );
        bool updateParam(
            const ULONG& index,
            INT param[]
            );
        // image record
        void startRec(
            const ULONG& index
            );
        void stopRec(
            const ULONG& index
            );
        bool isRec(
            const ULONG& index
            ) const;

    private:
        static void errMsg(
            const PTCHAR message
            );

    private:
        // for thread
        HANDLE iOpenMutex;
        volatile bool iIsOpened;
        // for image
        ULONG iCount;
        CamAdpt iCamAdpt[CAM_MAX_NUM]; // 0: left, 1: right

        friend VOID WINAPI cam0ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param);
        friend VOID WINAPI cam1ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param);
    };

    VOID WINAPI cam0ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param);
    VOID WINAPI cam1ImgGrabbed(PUCHAR data, INT width, INT height, INT bitCnt, LPVOID param);
}

#endif // LAMP_CAMBOX_H
