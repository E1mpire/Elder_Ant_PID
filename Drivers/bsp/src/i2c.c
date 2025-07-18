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
 * @brief   		����IIC��ʼ�ź�
 */
void IIC_Start(void)
{
	SDA_OUT;     																																					//sda�����
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	Delay_us(4);
 	IIC_SDA_L;																																							//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_L;																																							//ǯסI2C���ߣ�׼�����ͻ�������� 
}	  

/**
 * @brief   		����IICֹͣ�ź�
 */
void IIC_Stop(void)
{
	SDA_OUT;																																							//sda�����
	IIC_SCL_L;
	IIC_SDA_L;																																							//STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;																																							//����I2C���߽����ź�
	Delay_us(4);
}

/**
 * @brief    		�ȴ�Ӧ���źŵ���
 * @return			����ֵ��1������Ӧ��ʧ��     0������Ӧ��ɹ�
 */
uint8_t IIC_Wait_Ack(void)
{
	uint8_t ucErrTime=0;
	SDA_IN;      																																				//SDA����Ϊ����  
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
	IIC_SCL_L;																																					//ʱ�����0 	   
	return 0;  
} 

/**
 * @brief    		����ACKӦ��
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
 * @brief    		������ACKӦ��
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
 * @brief    		IIC����һ���ֽ�
 * @param[in]   txd : ��Ҫ���͵�����
 * @date��      ���شӻ�����Ӧ��  1����Ӧ��  0����Ӧ��			
 */
void IIC_Send_Byte(uint8_t txd)
{                        
    uint8_t t;   
		SDA_OUT; 	    
    IIC_SCL_L;																																										//����ʱ�ӿ�ʼ���ݴ���
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
 * @brief    		IIC��һ���ֽ�
 * @param[in]   ack    ack=1ʱ������ACK��ack=0������nACK   
 */
uint8_t IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN;																																														//SDA����Ϊ����
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
        IIC_NAck();																																									//����nACK
    else
        IIC_Ack(); 																																									//����ACK   
    return receive;
}

