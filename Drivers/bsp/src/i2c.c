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
	
#include "ch_lib_i2c.h"
#include "Delay.h"

void GPIO_MODE_SET(GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t Mode)
{
    HAL_GPIO_WritePin(GPIOx, GPIO_Pin, GPIO_PIN_SET);

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = GPIO_Pin;
    GPIO_InitStruct.Mode = Mode;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(GPIOx, &GPIO_InitStruct);
}
/**
 * @brief   		2������IIC?e��?D?o?
 */
void IIC_Start(void)
{
	SDA_OUT;     																																					//sda??��?3?
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	Delay_us(4);
 	IIC_SDA_L;																																							//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_L;																																							//?����?I2C����??��?��?��?����?��?��?����?��y?Y 
}	  

/**
 * @brief   		2������IIC����?1D?o?
 */
void IIC_Stop(void)
{
	SDA_OUT;																																							//sda??��?3?
	IIC_SCL_L;
	IIC_SDA_L;																																							//STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;																																							//����?��I2C����???����?D?o?
	Delay_us(4);
}

/**
 * @brief    		�̨���y��|��eD?o?��?����
 * @return			����???�̡�o1��??����?��|��e����㨹     0��??����?��|��e3��1|
 */
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN;      																																				//SDA����???a��?��?  
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
	IIC_SCL_L;																																					//����?����?3?0 	   
	return 0;  
} 

/**
 * @brief    		2������ACK��|��e
 */
void IIC_Ack(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_L;
	Delay_us(2);
	IIC_SCL_H;
	Delay_us(2);
	IIC_SCL_L;
}

/**
 * @brief    		2?2������ACK��|��e
 */
void IIC_NAck(void)
{
	IIC_SCL_L;
	SDA_OUT;
	IIC_SDA_H;
	Delay_us(2);
	IIC_SCL_H;
	Delay_us(2);
	IIC_SCL_L;
}					 				     

/**
 * @brief    		IIC����?����???��??��
 * @param[in]   txd : D����a����?����?��y?Y
 * @date��o      ����??�䨮?����D?T��|��e  1��?��D��|��e  0��??T��|��e			
 */
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT; 	    
    IIC_SCL_L;																																										//��-�̨�����?��?a��?��y?Y��?��?
    for(t=0;t<8;t++)
    {              
																																																	//IIC_SDA=(txd&0x80)>>7;
		if((txd&0x80)>>7)
			IIC_SDA_H;
		else
			IIC_SDA_L;
		txd<<=1; 	  
		Delay_us(2);
		IIC_SCL_H;
		Delay_us(2);
		IIC_SCL_L;	
		Delay_us(2);
    }	 
} 	    

/**
 * @brief    		IIC?����???��??��
 * @param[in]   ack    ack=1������?����?��ACK��?ack=0��?����?��nACK   
 */
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN;																																														//SDA����???a��?��?
  for(i=0;i<8;i++ )
	{
    IIC_SCL_L; 
		Delay_us(2);
		IIC_SCL_H;
    receive<<=1;
    if(READ_SDA)receive++;   
		Delay_us(1);
  }					 
    if (!ack)
        IIC_NAck();																																									//����?��nACK
    else
        IIC_Ack(); 																																									//����?��ACK   
    return receive;
}