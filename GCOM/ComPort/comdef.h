#ifndef LAMP_COMDEF_H
#define LAMP_COMDEF_H

#include "../config.h"

namespace Lamp
{
    const DWORD COM_CMD_TIME_DELAY  = 50;
    typedef struct _CB_UNO_CMD
    {
        UCHAR ucPre; // ���ֽڣ��ַ�C��CatchBest��C
        UCHAR ucFunctionMode; // ����ģʽ��0-�����ڲ�����źţ���������
        UCHAR ucStart; // 0-ֹͣ��1-������2-���ã���ucFunctionMode = 0ʱ����ֹͣ���͡���������Ч����ucFunctionMode = 1ʱ�������á���Ч�������á����֮��ȴ��ⴥ���ź�
        USHORT usTriggerSpeed; // ��������ٶȣ���ÿ����������������Ϊ0ʱ�����壬��СΪ1�����10K
        UCHAR ucCheckSum; // У��ͣ�ucCheckSum = (UCHAR)(ucFunctionMode + ucStart + usTriggerSpeed + usPulseNum)
        USHORT usPulseNum; // ����usPulseNum�����壬����Ϊ65535ʱ���������޸�
        UCHAR ucEnd; // β�ֽڣ��ַ�B��CatchBest��B
    } CB_UNO_CMD, *PCB_UNO_CMD;
    const DWORD NUM_BYTE_OF_CMD = 9;
}

#endif // LAMP_COMDEF_H
