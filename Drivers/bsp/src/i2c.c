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
 * @brief   		2úéúIIC?eê?D?o?
 */
void IIC_Start(void)
{
	SDA_OUT;     																																					//sda??ê?3?
	IIC_SDA_H;	  	  
	IIC_SCL_H;
	Delay_us(4);
 	IIC_SDA_L;																																							//START:when CLK is high,DATA change form high to low 
	Delay_us(4);
	IIC_SCL_L;																																							//?ˉ×?I2C×ü??￡?×?±?·￠?í?ò?óê?êy?Y 
}	  

/**
 * @brief   		2úéúIICí￡?1D?o?
 */
void IIC_Stop(void)
{
	SDA_OUT;																																							//sda??ê?3?
	IIC_SCL_L;
	IIC_SDA_L;																																							//STOP:when CLK is high DATA change form low to high
	Delay_us(4);
	IIC_SCL_H; 
	IIC_SDA_H;																																							//·￠?íI2C×ü???áê?D?o?
	Delay_us(4);
}

/**
 * @brief    		μè′yó|′eD?o?μ?à′
 * @return			·μ???μ￡o1￡??óê?ó|′eê§°ü     0￡??óê?ó|′e3é1|
 */
u8 IIC_Wait_Ack(void)
{
	u8 ucErrTime=0;
	SDA_IN;      																																				//SDAéè???aê?è?  
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
	IIC_SCL_L;																																					//ê±?óê?3?0 	   
	return 0;  
} 

/**
 * @brief    		2úéúACKó|′e
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
 * @brief    		2?2úéúACKó|′e
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
 * @brief    		IIC·￠?íò???×??ú
 * @param[in]   txd : Dèòa·￠?íμ?êy?Y
 * @date￡o      ·μ??′ó?úóD?Tó|′e  1￡?óDó|′e  0￡??Tó|′e			
 */
void IIC_Send_Byte(u8 txd)
{                        
    u8 t;   
		SDA_OUT; 	    
    IIC_SCL_L;																																										//à-μíê±?ó?aê?êy?Y′?ê?
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
 * @brief    		IIC?áò???×??ú
 * @param[in]   ack    ack=1ê±￡?·￠?íACK￡?ack=0￡?·￠?ínACK   
 */
u8 IIC_Read_Byte(unsigned char ack)
{
	unsigned char i,receive=0;
	SDA_IN;																																														//SDAéè???aê?è?
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
        IIC_NAck();																																									//·￠?ínACK
    else
        IIC_Ack(); 																																									//·￠?íACK   
    return receive;
}