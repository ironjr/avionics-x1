/*
 * File:   main.c
 * Author: Jaerin Lee
 *
 * Created on 2018? 11? 2? (?), ?? 5:49
 */

#include <xc.h>
#include "mcc_generated_files/mcc.h"

#include "bmp280.h"

void main(void) {
    SYSTEM_Initialize();
    
    bmp280 bmp;
    bmp280_i2c_init(&bmp);
    bmp280_i2c_set_ctrl(&bmp, BMP280_OSRS2, BMP280_OSRS4, BMP280_MODE_NORMAL);
    bmp280_i2c_set_conf(&bmp, BMP280_TSB0_5, BMP280_FILTER4);
    
    int32_t temp;
    int32_t press;
    while (1) {
        temp = bmp280_i2c_read_temp_i32(&bmp);
        press = bmp280_i2c_read_press_i32(&bmp);
        
    }
    
    return;
}
