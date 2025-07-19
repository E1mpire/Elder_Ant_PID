#ifndef __AS5600_H__
#define __AS5600_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

#define AS5600_ADDR 0X36
#define CONF_ADDR 0X07


  uint16_t AS5600_ReadAngle(void);
  uint16_t AS5600_IIC_Read_Byte(uint8_t deviceaddr,uint8_t readaddr);
  uint16_t AS5600_IIC_Read_OneByte(uint8_t deviceaddr,uint8_t readaddr);

#ifdef __cplusplus
}
#endif

#endif /* __TIM_H__ */