#ifndef LAMP_COMDEF_H
#define LAMP_COMDEF_H

#include "../config.h"

namespace Lamp
{
    const DWORD COM_CMD_TIME_DELAY  = 50;
    typedef struct _CB_UNO_CMD
    {
        UCHAR ucPre; // 首字节，字符C，CatchBest的C
        UCHAR ucFunctionMode; // 功能模式，0-根据内部软件信号，其他待定
        UCHAR ucStart; // 0-停止，1-启动，2-设置，当ucFunctionMode = 0时，“停止”和“启动”有效；当ucFunctionMode = 1时，“设置”有效，“设置”完成之后等待外触发信号
        USHORT usTriggerSpeed; // 脉冲输出速度，即每秒输出的脉冲个数，为0时无脉冲，最小为1，最大10K
        UCHAR ucCheckSum; // 校验和，ucCheckSum = (UCHAR)(ucFunctionMode + ucStart + usTriggerSpeed + usPulseNum)
        USHORT usPulseNum; // 发送usPulseNum个脉冲，当设为65535时，发送无限个
        UCHAR ucEnd; // 尾字节，字符B，CatchBest的B
    } CB_UNO_CMD, *PCB_UNO_CMD;
    const DWORD NUM_BYTE_OF_CMD = 9;
}

#endif // LAMP_COMDEF_H
