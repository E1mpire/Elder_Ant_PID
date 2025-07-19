/**
  ******************************************************************************
  * @file    i2c.h
  * @author  张文超 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    此程序为ARM中IIC的底层编程
  ******************************************************************************
  */

#ifndef __CH_LIB_IIC_H__
#define __CH_LIB_IIC_H__
														
#ifdef __cplusplus
 extern "C" {
#endif
	
#define u8 uint8_t
   
#include "main.h"
#include "gpio.h"
   
#define IIC_SDA_GPIO_Port GPIOA
#define IIC_SDA_Pin GPIO_PIN_10
   
#define IIC_SCL_GPIO_Port GPIOA
#define IIC_SCL_Pin GPIO_PIN_9

   //IO方向设置
#define SDA_IN    GPIO_MODE_SET(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_MODE_INPUT)
#define SDA_OUT   GPIO_MODE_SET(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_MODE_OUTPUT_PP)

//IO操作函数	 
#define IIC_SCL_H    HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_SET) //SCL
#define IIC_SCL_L    HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_RESET) //SCL
#define IIC_SDA_H    HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_SET) //SCL
#define IIC_SDA_L    HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_RESET) //SCL

   
#define READ_SDA     HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port,IIC_SDA_Pin)

//IIC所有操作函数
void IIC_Init(void);                //初始化IIC的IO口				 
void IIC_Start(void);				//发送IIC开始信号
void IIC_Stop(void);	  			//发送IIC停止信号
void IIC_Send_Byte(uint8_t txd);			//IIC发送一个字节
uint8_t IIC_Read_Byte(unsigned char ack);//IIC读取一个字节
uint8_t IIC_Wait_Ack(void); 				//IIC等待ACK信号
void IIC_Ack(void);					//IIC发送ACK信号
void IIC_NAck(void);				//IIC不发送ACK信号

#endif
