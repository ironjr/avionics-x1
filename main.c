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
    
    axes6_raw ax6raw;
    int32_t temp;
    uint32_t press;
    while (1) {
        bmp280_i2c_read_temp_i32(&bmp, &temp);
        bmp280_i2c_read_press_i32(&bmp, &press);
        mpu9250_i2c_read_axes6_raw(&mpu, &ax6raw);
    }
    
    return;
}
