#ifndef LAMP_COMPORT_H
#define LAMP_COMPORT_H

#include "comport_global.h"
#include "comdef.h"
#include <QtCore/QList>
#include <QtCore/QMutex>
#include <QtCore/QSemaphore>
#include <QtCore/QThread>

namespace Lamp
{
    class COMPORT_EXPORT ComPort : public QObject
    {
        Q_OBJECT

    public:
        ComPort();
        ~ComPort();

    public:
        bool open();
        bool close();
        bool isOpened() const;
        void sendCommand(
            const UCHAR* cmd,
            DWORD length
            );
        void sendCommand(
            const CB_UNO_CMD& cmd
            );
        void makeCheckSum(
            CB_UNO_CMD& cmd
            );
        void startTrigger();
        void stopTrigger();
        void changeFPS(
            USHORT fps
            );

    private:
        static void errMsg(
            const PTCHAR message
            );
        bool initialize();

    private:
        bool iIsOpened;
        HANDLE iComHandle;
    };
}

#endif // LAMP_COMPORT_H
