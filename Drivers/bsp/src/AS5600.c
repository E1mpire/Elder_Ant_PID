#include "AS5600.h"


extern I2C_HandleTypeDef hi2c1;


 uint16_t AS5600_ReadAngle(void) {
    uint8_t angle_reg = 0x0E;
    uint8_t buf[2] = {0};

    // ���ͼĴ�����ַ
    if (HAL_I2C_Master_Transmit(&hi2c1, AS5600_ADDR, &angle_reg, 1, 4095) != HAL_OK) {
        return 0xFFFF; // ������
    }

    // ��ȡ�����ֽ�
    if (HAL_I2C_Master_Receive(&hi2c1, AS5600_ADDR, buf, 2, 4095) != HAL_OK) {
        return 0xFFFF; // ������
    }

    // ��ϸߵ��ֽڳ�12λ�Ƕ�
    uint16_t angle = ((uint16_t)(buf[0] << 8)) | buf[1];
    return angle & 0x0FFF; // ������12λ
}
