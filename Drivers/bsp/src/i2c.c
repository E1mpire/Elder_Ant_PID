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
	
#include "i2c.h"
#include "Delay.h"

void GPIO_MODE_SET(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Mode)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}

 /**
 * @brief   		产生IIC起始信号
 */
void IIC_Start(void)
{
	SDA_OUT;     																																					//sda线输出
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	Delay_us(4);
 	IIC_SDA_L;																																							//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_L;																																							//钳住I2C总线，准备发送或接收数据 
}	  

/**
 * @brief   		产生IIC停止信号
 */
void IIC_Stop(void)
{
	SDA_OUT;																																							//sda线输出
	IIC_SCL_L;
	IIC_SDA_L;																																							//STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;																																							//发送I2C总线结束信号
	Delay_us(4);
}

/**
 * @brief    		等待应答信号到来
 * @return			返回值：1，接收应答失败     0，接收应答成功
 */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN;      																																				//SDA设置为输入  
	IIC_SDA_H;
	Delay_us(1);
	IIC_SCL_H;
	Delay_us(1);	
	while(READ_SDA)
	{
		ucErrTime++;
		if(ucErrTime>250)
		{
			IIC_Stop();
			return 1;
		}
	}
	IIC_SCL_L;																																					//时钟输出0 	   
	return 0;  
} 

/**
 * @brief    		产生ACK应答
 */
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_L;
	Delay_us(5);
	IIC_SCL_H;
	Delay_us(5);
	IIC_SCL_L;
}

/**
 * @brief    		不产生ACK应答
 */
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_H;
	Delay_us(5);
	IIC_SCL_H;
	Delay_us(5);
	IIC_SCL_L;
}					 				     

/**
 * @brief    		IIC发送一个字节
 * @param[in]   txd : 需要发送的数据
 * @date：      返回从机有无应答  1，有应答  0，无应答			
 */
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
		SDA_OUT; 	    
    IIC_SCL_L;																																										//拉低时钟开始数据传输
    for(t=0;t<8;t++)
    {              
																																																	//IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		txd<<=1; 	  
		Delay_us(5);
		IIC_SCL_H;
		Delay_us(5);
		IIC_SCL_L;	
		Delay_us(5);
    }	 
} 	    

/**
 * @brief    		IIC读一个字节
 * @param[in]   ack    ack=1时，发送ACK，ack=0，发送nACK   
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN;																																														//SDA设置为输入
  for(i=0;i<8;i++ )
	{
    IIC_SCL_L; 
		Delay_us(5);
		IIC_SCL_H;
    receive<<=1;
    if(READ_SDA)receive++;   
		Delay_us(1);
  }					 
    if (!ack)
        IIC_NAck();																																									//发送nACK
    else
        IIC_Ack(); 																																									//发送ACK   
    return receive;
}

