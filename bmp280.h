/* 
 * File:   bmp280.h
 * Author: Jaerin Lee
 * Comments: BMP280 sensor driver
 * Revision history: 
 */

#ifndef BMP280_H
#define	BMP280_H

#ifdef __cplusplus
//extern "C" {
#endif
    
#include "mcc_generated_files/i2c1.h"

#define BMP280_I2C_ADDR 0b1110110 /* 0b111011X, where X is SDO */

/* Register addresses */
#define BMP280_REG_DGT1_MSB 0x88

#define BMP280_REG_CHIPID 0xD0
#define BMP280_REG_VERSION 0xD1
#define BMP280_REG_SOFTRESET 0xE0

#define BMP280_REG_CAL26 0xE1 /* R calibration stored in 0xE1-0xF0 */

#define BMP280_REG_CONTROL 0xF4
#define BMP280_REG_CONFIG 0xF5
#define BMP280_REG_PRESS_MSB 0xF7
#define BMP280_REG_TEMP_MSB 0xFA

/* Chip data */
#define BMP280_CHIPID 0x58

/* Oversampling rate */
#define BMP280_OSRS0 0x0
#define BMP280_OSRS1 0x1
#define BMP280_OSRS2 0x2
#define BMP280_OSRS4 0x3
#define BMP280_OSRS8 0x4
#define BMP280_OSRS16 0x5

/* Operation mode */
#define BMP280_MODE_SLEEP 0x0
#define BMP280_MODE_FORCED 0x1
#define BMP280_MODE_NORMAL 0x3

/* Time to sleep (ms) */
#define BMP280_TSB0_5 0x0
#define BMP280_TSB62_5 0x1
#define BMP280_TSB125 0x2
#define BMP280_TSB250 0x3
#define BMP280_TSB500 0x4
#define BMP280_TSB1K 0x5
#define BMP280_TSB2K 0x6
#define BMP280_TSB4K 0x7

/* IIR filter coefficient */
#define BMP280_FILTER1 0x0
#define BMP280_FILTER2 0x1
#define BMP280_FILTER4 0x2
#define BMP280_FILTER8 0x3
#define BMP280_FILTER16 0x4

typedef struct {
    uint16_t dig_T1;
    int16_t dig_T2;
    int16_t dig_T3;
    
    uint16_t dig_P1;
    int16_t dig_P2;
    int16_t dig_P3;
    int16_t dig_P4;
    int16_t dig_P5;
    int16_t dig_P6;
    int16_t dig_P7;
    int16_t dig_P8;
    int16_t dig_P9;
} bmp280_calib_data;

typedef struct {
    uint8_t addr;
    bmp280_calib_data calib;
    int32_t t_fine;
} bmp280;

/* Function declaration */
uint8_t bmp280_i2c_init(bmp280 *);
uint8_t bmp280_i2c_set_ctrl(bmp280 *, uint8_t, uint8_t, uint8_t);
uint8_t bmp280_i2c_set_conf(bmp280 *, uint8_t, uint8_t);
uint8_t bmp280_i2c_set_osrs_t(bmp280 *, uint8_t);
uint8_t bmp280_i2c_set_osrs_p(bmp280 *, uint8_t);
uint8_t bmp280_i2c_set_mode(bmp280 *, uint8_t);
uint8_t bmp280_i2c_set_t_sb(bmp280 *, uint8_t);
uint8_t bmp280_i2c_set_filter(bmp280 *, uint8_t);
uint8_t bmp280_i2c_get_osrs_t(bmp280 *, uint8_t *);
uint8_t bmp280_i2c_get_osrs_p(bmp280 *, uint8_t *);
uint8_t bmp280_i2c_get_mode(bmp280 *, uint8_t *);
uint8_t bmp280_i2c_get_t_sb(bmp280 *, uint8_t *);
uint8_t bmp280_i2c_get_filter(bmp280 *, uint8_t *);
uint8_t bmp280_i2c_read_temp_i32(bmp280 *, int32_t *);
uint8_t bmp280_i2c_read_press_raw(bmp280 *, int32_t *);
uint8_t bmp280_i2c_read_press_i32(bmp280 *, uint32_t *);

#ifdef __cplusplus
//}
#endif

#endif	/* BMP280_H */

