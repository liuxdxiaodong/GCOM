#include "comport.h"
#include <devguid.h>
#include <setupapi.h>
#include <tchar.h>
#include <strsafe.h>

namespace Lamp
{
    ComPort::ComPort()
        : QObject(),
        iIsOpened(false),
        iComHandle(NULL)
    {
    }

    ComPort::~ComPort()
    {
        this->close();
    }

    bool ComPort::open()
    {
        if(this->iIsOpened)
        {
            if(!this->close())
            {
                return false;
            }
        }
        if(!this->initialize())
        {
            return false;
        }
        this->startTrigger();
        this->iIsOpened = true;
        return true;
    }

    bool ComPort::close()
    {
        if(this->iComHandle)
        {
            this->stopTrigger();
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
        }
        this->iIsOpened = false;
        return true;
    }

    bool ComPort::isOpened() const
    {
        return this->iIsOpened;
    }

    void ComPort::sendCommand(
        const UCHAR* cmd,
        DWORD length
        )
    {
        if(!this->iComHandle)
        {
            return;
        }
        BOOL result = WriteFile(
            this->iComHandle,
            cmd,
            length,
            &length,
            NULL);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to send COM data!");
        }
        Sleep(COM_CMD_TIME_DELAY);
        UCHAR buf[16] = {0};
        result = ReadFile(
            this->iComHandle,
            buf,
            16,
            &length,
            NULL);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to recv COM data!");
        }
    }

    void ComPort::sendCommand(
        const CB_UNO_CMD& cmd
        )
    {
        UCHAR buf[NUM_BYTE_OF_CMD] = {0};
        CopyMemory(&buf[0], &cmd.ucPre, 1);
        CopyMemory(&buf[1], &cmd.ucFunctionMode, 1);
        CopyMemory(&buf[2], &cmd.ucStart, 1);
        CopyMemory(&buf[3], &cmd.usTriggerSpeed, 2);
        CopyMemory(&buf[5], &cmd.ucCheckSum, 1);
        CopyMemory(&buf[6], &cmd.usPulseNum, 2);
        CopyMemory(&buf[8], &cmd.ucEnd, 1);
        this->sendCommand(buf, NUM_BYTE_OF_CMD);
    }

    void ComPort::makeCheckSum(
        CB_UNO_CMD& cmd
        )
    {
        cmd.ucCheckSum = 0;
        if(cmd.ucPre != 'C' || cmd.ucEnd != 'B')
        {
            return;
        }
        cmd.ucCheckSum = (UCHAR)(cmd.ucFunctionMode + cmd.ucStart + cmd.usTriggerSpeed + cmd.usPulseNum);
    }

    void ComPort::startTrigger()
    {
        CB_UNO_CMD cmd = {0};
        cmd.ucPre = 'C';
        cmd.ucFunctionMode = 0;
        cmd.ucStart = 1; // 0-Í£Ö¹£¬1-Æô¶¯£¬2-ÉèÖÃ
        cmd.usTriggerSpeed = 0;
        cmd.usPulseNum = 0;
        cmd.ucEnd = 'B';
        this->makeCheckSum(cmd);
        this->sendCommand(cmd);
    }

    void ComPort::stopTrigger()
    {
        CB_UNO_CMD cmd = {0};
        cmd.ucPre = 'C';
        cmd.ucFunctionMode = 0;
        cmd.ucStart = 0; // 0-Í£Ö¹£¬1-Æô¶¯£¬2-ÉèÖÃ
        cmd.usTriggerSpeed = 0;
        cmd.usPulseNum = 0;
        cmd.ucEnd = 'B';
        this->makeCheckSum(cmd);
        this->sendCommand(cmd);
    }

    void ComPort::changeFPS(
        USHORT fps
        )
    {
        this->stopTrigger();
        CB_UNO_CMD cmd = {0};
        cmd.ucPre = 'C';
        cmd.ucFunctionMode = 0;
        cmd.ucStart = 2; // 0-Í£Ö¹£¬1-Æô¶¯£¬2-ÉèÖÃ
        cmd.usTriggerSpeed = fps;
        cmd.usPulseNum = 65535;
        cmd.ucEnd = 'B';
        this->makeCheckSum(cmd);
        this->sendCommand(cmd);
        this->startTrigger();
    }

    void ComPort::errMsg(
        const PTCHAR message
        )
    {
        MessageBox(NULL, message, L"ComPort", MB_ICONERROR);
    }

    bool ComPort::initialize()
    {
        // enumerate ports to find COM port
        BOOL result = FALSE;
        bool isFound = false;
        HDEVINFO devInfo = NULL;
        devInfo = SetupDiGetClassDevs(
            &GUID_DEVCLASS_PORTS,
            NULL,
            NULL,
            DIGCF_PRESENT);
        if(INVALID_HANDLE_VALUE == devInfo)
        {
            ComPort::errMsg(L"Fail to find COM class!");
            return false;
        }
        // enumerate through all devices in set
        SP_DEVINFO_DATA devInfoData;
        ULONG devIdx = 0;
        std::wstring portName = L"\\\\.\\";
        while(TRUE)
        {
            devInfoData.cbSize = sizeof(SP_DEVINFO_DATA);
            result = SetupDiEnumDeviceInfo(
                devInfo,
                devIdx,
                &devInfoData);
            if(FALSE == result)
            {
                break;
            }
            ULONG dataType = 0;
            WCHAR buffer[256] = {0};
            ULONG bufferSize = 256;
            result = SetupDiGetDeviceRegistryProperty(
                devInfo,
                &devInfoData,
                SPDRP_FRIENDLYNAME,
                &dataType,
                (PBYTE)buffer,
                bufferSize,
                &bufferSize);
            if(FALSE == result)
            {
                continue;
            }
            std::wstring name = buffer;
            int index = name.find(L"CBAT328-IO602 (COM");
            if(index >= 0)
            {
                isFound = true;
                int start = name.find(L"(COM") + 1;
                int end = name.find(L")", start);
                portName += name.substr(start, end - start);
                break;
            }
            ++devIdx;
        }
        // cleanup
        SetupDiDestroyDeviceInfoList(devInfo);
        if(!isFound)
        {
            ComPort::errMsg(L"Fail to find COM!");
            return false;
        }
        // create file
        this->iComHandle = CreateFile(
            portName.c_str(), // COM port
            GENERIC_READ | GENERIC_WRITE, // enable read and write
            0, // no share mode
            NULL,
            OPEN_EXISTING, // open existing COM port, not create
            0, // synchronous mode
            NULL);
        if(INVALID_HANDLE_VALUE == this->iComHandle)
        {
            ComPort::errMsg(L"Fail to open COM!");
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
            return false;
        }
        // set state
        DCB dcb;
        result = GetCommState(this->iComHandle, &dcb);
        dcb.BaudRate = CBR_115200;
        dcb.Parity = NOPARITY;
        dcb.ByteSize = 8;
        dcb.StopBits = ONESTOPBIT;
        result = SetCommState(this->iComHandle, &dcb);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to set COM state!");
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
            return false;
        }
        // setup port
        result = SetupComm(
            this->iComHandle,
            16,
            16);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to setup COM!");
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
            return false;
        }
        // set timeouts
        COMMTIMEOUTS TimeOuts;
        // set read timeouts
        TimeOuts.ReadIntervalTimeout = 1000;
        TimeOuts.ReadTotalTimeoutMultiplier = 500;
        TimeOuts.ReadTotalTimeoutConstant = 5000;
        // set write timeouts
        TimeOuts.WriteTotalTimeoutMultiplier = 500;
        TimeOuts.WriteTotalTimeoutConstant = 5000;
        result = SetCommTimeouts(
            this->iComHandle,
            &TimeOuts);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to set COM timeouts!");
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
            return false;
        }
        // purge port
        result = PurgeComm(
            this->iComHandle,
            PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR);
        if(FALSE == result)
        {
            ComPort::errMsg(L"Fail to purge COM!");
            CloseHandle(this->iComHandle);
            this->iComHandle = NULL;
            return false;
        }
        return true;
    }
}
