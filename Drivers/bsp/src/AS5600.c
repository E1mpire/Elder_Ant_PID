#include "AS5600.h"
#include "i2c.h"

/*
uint16_t AS5600_IIC_Read_OneByte(uint8_t deviceaddr,uint8_t readaddr)
{
  uint16_t temp;
  IIC_Start();
  IIC_Send_Byte(deviceaddr&0xfe);
  if(IIC_Wait_Ack())
    return 0;
  IIC_Send_Byte(readaddr);
  if(IIC_Wait_Ack())
    return 0;
  
  IIC_Start();
  IIC_Send_Byte(deviceaddr|0x01);
  if(IIC_Wait_Ack())
    return 0;
  temp=IIC_Read_Byte(1);
  temp = (temp<<8) | IIC_Read_Byte(0);
  IIC_Stop();
  return temp;
}
*/
uint16_t AS5600_IIC_Read_Byte(uint8_t deviceaddr,uint8_t readaddr)
{
  uint8_t temp[2];
  uint16_t result;
  HAL_I2C_Mem_Read(&hi2c1, 0x36 << 1, 0x0e, 
                         I2C_MEMADD_SIZE_8BIT, temp, 2, 100);
    
  
  //HAL_I2C_Master_Transmit(&hi2c1,(0X36<<1),&readaddr,1,4095);
  //HAL_I2C_Master_Receive(&hi2c1,(0x36<<1),temp,2,4095);
  result = (temp[0]<<8)|temp[1];
  return  result;
}



void AS5600_Init(uint8_t SF,uint8_t FTH)
{
  uint8_t value;
  uint8_t deviceaddr = 0x36<<1;
  IIC_Start();
  IIC_Send_Byte(deviceaddr&0xfe);
  IIC_Wait_Ack();
  IIC_Send_Byte(CONF_ADDR);
  IIC_Wait_Ack();
  value  = IIC_Read_Byte(0);
  value = value & 0x10;  //ȡ5λ
  value = value | (FTH<<2) | SF ;
  
  IIC_Start();
  IIC_Send_Byte(CONF_ADDR|0X01);
  IIC_Wait_Ack();
  IIC_Send_Byte(value);
  
  IIC_Stop();
  
  
  
  
}


