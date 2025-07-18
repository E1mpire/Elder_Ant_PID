/*
 * Delay.c
 *
 *  Created on: Dec 27, 2021
 *      Author: 张西凯
 */

#include "Delay.h"


/******************************************************************************************************
* 函 数 名: delay_us
* 入口参数: delay - 延时时间
* 返 回 值: 无
* 函数功能: us延时
* 说    明: 使用时需要先更改对应主频
*******************************************************************************************************/
void Delay_us(int delay)
{
 int last, curr, val;
    int temp;
    while (delay != 0)
    {
        temp = delay > 900 ? 900 : delay;
        last = SysTick->VAL;
        curr = last - CPU_FREQUENCY_MHZ * temp;
        if (curr >= 0)
        {
            do
            {
                val = SysTick->VAL;
            }
            while ((val < last) && (val >= curr));
        }
        else
        {
            curr += CPU_FREQUENCY_MHZ * 1000;
            do
            {
                val = SysTick->VAL;
            }
            while ((val <= last) || (val > curr));
        }
        delay -= temp;
    }
}
