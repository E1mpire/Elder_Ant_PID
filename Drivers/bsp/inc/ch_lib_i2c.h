/**
  ******************************************************************************
  * @file    i2c.h
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.8.21
  * @note    �˳���ΪARM��IIC�ĵײ���
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

   //IO��������
#define SDA_IN    GPIO_MODE_SET(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_MODE_INPUT)
#define SDA_OUT   GPIO_MODE_SET(IIC_SDA_GPIO_Port, IIC_SDA_Pin, GPIO_MODE_OUTPUT_PP)

//IO��������	 
#define IIC_SCL_H    HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_SET) //SCL
#define IIC_SCL_L    HAL_GPIO_WritePin(IIC_SCL_GPIO_Port,IIC_SCL_Pin,GPIO_PIN_RESET) //SCL
#define IIC_SDA_H    HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_SET) //SCL
#define IIC_SDA_L    HAL_GPIO_WritePin(IIC_SDA_GPIO_Port,IIC_SDA_Pin,GPIO_PIN_RESET) //SCL

   
#define READ_SDA     HAL_GPIO_ReadPin(IIC_SDA_GPIO_Port,IIC_SDA_Pin)

//IIC���в�������
void IIC_Init(void);                //��ʼ��IIC��IO��				 
void IIC_Start(void);				//����IIC��ʼ�ź�
void IIC_Stop(void);	  			//����IICֹͣ�ź�
void IIC_Send_Byte(uint8_t txd);			//IIC����һ���ֽ�
uint8_t IIC_Read_Byte(unsigned char ack);//IIC��ȡһ���ֽ�
uint8_t IIC_Wait_Ack(void); 				//IIC�ȴ�ACK�ź�
void IIC_Ack(void);					//IIC����ACK�ź�
void IIC_NAck(void);				//IIC������ACK�ź�

#endif
