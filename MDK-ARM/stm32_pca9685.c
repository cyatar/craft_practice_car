
#include "math.h"
#include "i2c.h"
#include "stm32_pca9685.h"

uint8_t pca_read(uint8_t startAddress) {
    //Send address to start reading from.
    uint8_t tx[1];
    uint8_t buffer[1];
    tx[0]=startAddress;

    HAL_I2C_Master_Transmit(&hi2c1,pca_adrr, tx,1,3000); // 100000
    HAL_I2C_Master_Receive(&hi2c1,pca_adrr,buffer,1,3000);
    return buffer[0];
}

void pca_write(uint8_t startAddress, uint8_t buffer) {
    //Send address to start reading from.
    uint8_t tx[2];
    tx[0]=startAddress;
    tx[1]=buffer;
    HAL_I2C_Master_Transmit(&hi2c1,pca_adrr, tx,2,3000);

}

void pca_setfreq(float freq)//����PWMƵ��
{
		uint8_t prescale,oldmode,newmode;
		double prescaleval;
		freq *= 0.92; 
		prescaleval = 25000000;
		prescaleval /= 4096;
		prescaleval /= freq;
		prescaleval -= 1;
		prescale =floor(prescaleval + 0.5f);

		oldmode = pca_read(pca_mode1);
	
		newmode = (oldmode&0x7F) | 0x10; // sleep
	
		pca_write(pca_mode1, newmode); // go to sleep
	
		pca_write(pca_pre, prescale); // set the prescaler
	
		pca_write(pca_mode1, oldmode);
		HAL_Delay(2);
	
		pca_write(pca_mode1, oldmode | 0xa1); 
}

void pca_setpwm(uint8_t num, uint32_t on, uint32_t off)
{
		pca_write(LED0_ON_L+4*num,on);
		pca_write(LED0_ON_H+4*num,on>>8);
		pca_write(LED0_OFF_L+4*num,off);
		pca_write(LED0_OFF_H+4*num,off>>8);
}

void PCA_MG9XX_Init(float hz,uint8_t angle)
{
	uint32_t off=0;
//	IIC_Init();
	pca_write(pca_mode1,0x0);
	pca_setfreq(hz);//����PWMƵ��
	off=(uint32_t)(145+angle*2.4);
	pca_setpwm(0,0,off);pca_setpwm(1,0,off);pca_setpwm(2,0,off);pca_setpwm(3,0,off);
	pca_setpwm(4,0,off);pca_setpwm(5,0,off);pca_setpwm(6,0,off);pca_setpwm(7,0,off);
	pca_setpwm(8,0,off);pca_setpwm(9,0,off);pca_setpwm(10,0,off);pca_setpwm(11,0,off);
	pca_setpwm(12,0,off);pca_setpwm(13,0,off);pca_setpwm(14,0,off);pca_setpwm(15,0,off);
	HAL_Delay(500);
}


void PCA_MG9XX(uint8_t num,uint8_t end_angle)
{
	uint32_t off=0;
	
	off=(uint32_t)(158+end_angle*2.2);
	pca_setpwm(num,0,off);
}









