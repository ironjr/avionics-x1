/*
 * File:   main.c
 * Author: Jaerin Lee
 *
 * Created on 2018? 11? 2? (?), ?? 5:49
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"

#include "bmp280.h"
#include "mpu9250.h"

/*
typedef struct {
    float x;
    float y;
    float z;
} vector3_sp;

vector3_sp accel;
vector3_sp gyro;
*/

axes6_raw ax6raw;

void interrupt isr(void) {
    if (SOSIF == 1) {
        uint8_t temp[6];
        SPI1_Exchange8bitBuffer(temp, sizeof(vector3_16s), (uint8_t *)&(ax6raw.accel));
        SPI1INTF = 0;
    }
}

void main(void) {
    SYSTEM_Initialize();
    
    bmp280 bmp;
    bmp.addr = 0;
    bmp280_i2c_init(&bmp);
    bmp280_i2c_set_ctrl(&bmp, BMP280_OSRS2, BMP280_OSRS4, BMP280_MODE_NORMAL);
    bmp280_i2c_set_conf(&bmp, BMP280_TSB0_5, BMP280_FILTER4);
    
    mpu9250 mpu;
    mpu.addr = 0;
    mpu.scale.a_fs = MPU9250_AFS_16G;
    mpu.scale.g_fs = MPU9250_GFS_500;
    mpu.scale.m_fs = AK8963_BIT_16;
    mpu9250_i2c_init(&mpu, 0);
    mpu9250_i2c_config_fs(&mpu, 0); // 6-axis only
    
    int32_t temp;
    uint32_t press;
    
    mpu9250_gyro_zeroadj(&mpu, 16, 50);
    
    GIE = 1;
    SPI1IE = 1;
    
    while (1) {
        bmp280_i2c_read_temp_i32(&bmp, &temp);
        bmp280_i2c_read_press_i32(&bmp, &press);

        SOSIE = 0;
        mpu9250_i2c_read_axes6_raw(&mpu, &ax6raw);
        SPI1INTF = 0;
        SOSIE = 1;
    }
    
    return;
}
