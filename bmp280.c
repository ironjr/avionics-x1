/* 
 * File:   bmp280.c
 * Author: Jaerin Lee
 * Comments: BMP280 sensor driver
 * Revision history: 
 */

#include <xc.h>
#include <stdint.h>

#include "bmp280.h"

uint8_t bmp280_i2c_init(bmp280 *bmp) {
    uint8_t chip_id = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CHIPID);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT || chip_id != BMP280_CHIPID)
        return 1;
    
    i2c1_readDataBlock(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_DGT1_MSB,
            (char *)(&bmp->calib),
            24);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_ctrl(bmp280 *bmp, uint8_t osrs_t, uint8_t osrs_p, uint8_t mode) {
    uint8_t ctrl = (uint8_t)(((osrs_t & 0x7) << 5) |
            ((osrs_p & 0x7) << 2) |
            (mode & 0x3));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL,
            ctrl);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    return 0;
}

uint8_t bmp280_i2c_set_conf(bmp280 *bmp, uint8_t t_sb, uint8_t filter) {
    uint8_t cfg;
    cfg = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    cfg = (uint8_t)(((t_sb & 0x7) << 5) |
            ((filter & 0x7) << 2) |
            (cfg & 0x3));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG,
            cfg);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_osrs_t(bmp280 *bmp, uint8_t osrs_t) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    ctrl = (uint8_t)((ctrl & 0x1F) |
            ((osrs_t & 0x7) << 5));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL,
            ctrl);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_osrs_p(bmp280 *bmp, uint8_t osrs_p) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    ctrl = (uint8_t)((ctrl & 0xE3) |
            ((osrs_p & 0x7) << 2));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL,
            ctrl);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_mode(bmp280 *bmp, uint8_t mode) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    ctrl = (uint8_t)((ctrl & 0xFC) |
            (mode & 0x3));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL,
            ctrl);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_t_sb(bmp280 *bmp, uint8_t t_sb) {
    uint8_t cfg;
    cfg = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;

    cfg = (uint8_t)((cfg & 0x1F) | 
            ((t_sb & 0x7) << 5));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG,
            cfg);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_set_filter(bmp280 *bmp, uint8_t filter) {
    uint8_t cfg;
    cfg = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;

    cfg = (uint8_t)((cfg & 0xE3) |
            ((filter & 0x7) << 2));
    i2c1_write1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG,
            cfg);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

uint8_t bmp280_i2c_get_osrs_t(bmp280 *bmp, uint8_t *osrs_t) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    *osrs_t = (uint8_t)((ctrl & 0xE0) >> 5);
    return 0;
}

uint8_t bmp280_i2c_get_osrs_p(bmp280 *bmp, uint8_t *osrs_p) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    *osrs_p = (uint8_t)((ctrl & 0x1C) >> 2);
    return 0;
}

uint8_t bmp280_i2c_get_mode(bmp280 *bmp, uint8_t *mode) {
    uint8_t ctrl;
    ctrl = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONTROL);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    *mode = (uint8_t)(ctrl & 0x03);
    return 0;
}

uint8_t bmp280_i2c_get_t_sb(bmp280 *bmp, uint8_t *t_sb) {
    uint8_t cfg;
    cfg = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    *t_sb = (uint8_t)((cfg & 0xE0) >> 5);
    return 0;
}

uint8_t bmp280_i2c_get_filter(bmp280 *bmp, uint8_t *filter) {
    uint8_t cfg;
    cfg = i2c1_read1ByteRegister(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;

    *filter = (uint8_t)((cfg & 0x1C) >> 2);
    return 0;
}

uint8_t bmp280_i2c_read_temp_i32(bmp280 *bmp, int32_t *T) {
    /* Request for the temperature register value. */
    /* Read from the consecutive registers. */
    int32_t adc_T;
    uint8_t t_read[3];
    i2c1_readDataBlock(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_TEMP_MSB,
            (char *)t_read,
            3);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    adc_T = ((int32_t)t_read[0]) << 12 |
            ((int32_t)t_read[1]) << 4 |
            (t_read[2] >> 4) & 0x0F;
    
    int32_t temp1;
    int32_t temp2;
    int32_t temp3;
    temp1 = ((((adc_T >> 3) - ((int32_t)bmp->calib.dig_T1 << 1))) *
            ((int32_t)bmp->calib.dig_T2)) >> 11;
    temp2 = (adc_T >> 4) - ((int32_t)bmp->calib.dig_T1);
    temp3 = (((temp2 * temp2) >> 12) * ((int32_t)bmp->calib.dig_T3)) >> 14;
    bmp->t_fine = temp1 + temp3;
    
    *T = (bmp->t_fine * 5 + 128) >> 8;
    return 0;
}

 uint8_t bmp280_i2c_read_press_raw(bmp280 *bmp, int32_t *P) {
    /* Request for the temperature register value. */
    /* Read from the consecutive registers. */
    uint8_t p_read[3];
    i2c1_readDataBlock(
            BMP280_I2C_ADDR | bmp->addr,
            BMP280_REG_PRESS_MSB,
            (char *)p_read,
            3);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    *P = ((int32_t)p_read[0]) << 12 |
            ((int32_t)p_read[1]) << 4 |
            (p_read[2] >> 4) & 0x0F;
    return 0;
}

/* Note that this 32-bit integer configuration may introduce 1 Pa (1-sigma) of
 * noise to the output, degrading overall performance.
 */
uint8_t bmp280_i2c_read_press_i32(bmp280 *bmp, uint32_t *P) {
    int32_t adc_P;
    if (bmp280_i2c_read_press_raw(bmp, &adc_P))
        return 1;
    
    int32_t var1;
    int32_t var2;
    var1 = (((int32_t)bmp->t_fine) >> 1) - (int32_t)64000;
    var2 = (((var1 >> 2) * (var1 >> 2)) >> 11 ) * ((int32_t)bmp->calib.dig_P6);
    var2 = var2 + ((var1 * ((int32_t)bmp->calib.dig_P5)) << 1);
    var2 = (var2 >> 2) + (((int32_t)bmp->calib.dig_P4) << 16);
    var1 = (((bmp->calib.dig_P3 * (((var1 >> 2) * (var1 >> 2)) >> 13 )) >> 3) +
            ((((int32_t)bmp->calib.dig_P2) * var1) >> 1)) >> 18;
    var1 = ((((32768 + var1)) * ((int32_t)bmp->calib.dig_P1)) >> 15);
    
    /* Avoid exception caused by division by zero */
    if (var1 == 0)
        return 2;
    
    /* Pressure overflow handling */
    *P = (((uint32_t)(((int32_t)1048576) - adc_P) - ((uint32_t)var2 >> 12))) * 3125;
    if (*P < 0x80000000)
        *P = (*P << 1) / ((uint32_t)var1);
    else
        *P = (*P / (uint32_t)var1) * 2;

    var1 = (((int32_t)bmp->calib.dig_P9) *
            ((int32_t)(((*P >> 3) * (*P >> 3)) >> 13))) >> 12;
    var2 = (((int32_t)(*P >> 2)) * ((int32_t)bmp->calib.dig_P8)) >> 13;
    *P = (uint32_t)((int32_t)*P + ((var1 + var2 + bmp->calib.dig_P7) >> 4));
    return 0;
}

#if 0
int64_t bmp280_i2c_read_press_i64(void) {
    /* Request for the temperature register value. */
    /* Read from the consecutive registers. */
    int32_t adc_P;
    i2c1_readDataBlock(
            BMP280_I2C_ADDR,
            BMP280_PRESS_MSB,
            (char *)(&adc_P),
            3);
    adc_P >>= 4;
    
    int64_t var1;
	int64_t var2;
	int64_t P;
	var1 = ((int64_t)bmp280_t_fine) - 128000;
	var2 = var1 * var1 * (int64_t)bmp280_calib.dig_P6;
	var2 = var2 + ((var1 * (int64_t)bmp280_calib.dig_P5) << 17);
	var2 = var2 + (((int64_t)bmp280_calib.dig_P4) << 35);
	var1 = ((var1 * var1 * (int64_t)bmp280_calib.dig_P3) >> 8) +
            ((var1 * (int64_t)bmp280_calib.dig_P2) << 12);
	var1 = (((((int64_t)1) << 47) + var1)) *
            ((int64_t)bmp280_calib.dig_P1) >> 33;

	// avoid exception caused by division by zero
	if (var1 == 0)
		return 0;
	
	P = 1048576 - adc_P;
	P = (((P << 31) - var2) * 3125) / var1;
	var1 = (((int64_t)bmp280_calib.dig_P9) * (P >> 13) * (P >> 13)) >> 25;
	var2 = (((int64_t)bmp280_calib.dig_P8) * P) >> 19;
	P = ((P + var1 + var2) >> 8) + (((int64_t)bmp280_calib.dig_P7) << 4);
	
	return (uint64_t)P;
}
#endif