#include "AS5600.h"


uint8_t AS5600_IIC_Read_OneByte(uint8_t deviceaddr,uint8_t readaddr)
{
  uint8_t temp;
  IIC_Start();
  IIC_Send_Byte(deviceaddr&0xfe);
  IIC_Wait_Ack();
  IIC_Send_Byte(readaddr);
  IIC_Wait_Ack();

  IIC_Start();
  IIC_Send_Byte(deviceaddr|0x01);
  IIC_Wait_Ack();
  temp=IIC_Read_Byte(0);
  IIC_Stop();
  return temp;
}