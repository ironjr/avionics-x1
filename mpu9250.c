/* 
 * File:   mpu9250.h
 * Author: Jaerin Lee
 * Comments: MPU9250 with AK8963 sensor driver
 * Revision history: 
 */

#include <xc.h>
#include <stdint.h>

#include "mpu9250.h"

/*
 * mpu9250_i2c_init
 * Initialize mpu9250 chip with continuous performance-oriented mode.
 */
uint8_t mpu9250_i2c_init(mpu9250 *mpu) {
    /*
     * Set gyroscope and accelerometer
     */
    
    uint8_t chip_id = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_WHO_AM_I);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT || chip_id != MPU9250_CHIPID)
        return 1;
    
    /* Hardware reset */
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_PWR_MGMT_1,
            0x80);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    __delay_ms(50);
    
    bit rst_complete = 0;
    do {
        uint8_t rst = i2c1_read1ByteRegister(
                MPU9250_I2C_ADDR | mpu->addr,
                MPU9250_PWR_MGMT_1);
        rst_complete = rst >> 7;
        __delay_ms(50);
    } while (rst_complete);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 3;
    
    /* Auto-select clock source */
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_PWR_MGMT_1,
            0x01);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 4;
    __delay_ms(200);
    
    /*
     * Now for AK8963 magnetometer
     */
    
    /* Power down mode */
    i2c1_write1ByteRegister(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            0x00);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 5;
    __delay_ms(50);
    
    /* Fuse ROM access mode */
    i2c1_write1ByteRegister(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            0x0F);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 6;
    __delay_ms(50);
    
    /* Fuse ROM access mode */
    i2c1_write1ByteRegister(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            0x0F);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 7;
    __delay_ms(50);
    
    /* Read coefficient data */
    uint8_t mag_coef[3];
    i2c1_readDataBlock(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_ASAX,
            (char *)mag_coef,
            3);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 8;
    mpu->mag_factor.x = mag_coef[0] + 128;
    mpu->mag_factor.y = mag_coef[1] + 128;
    mpu->mag_factor.z = mag_coef[2] + 128;
        
    /* Power down mode */
    i2c1_write1ByteRegister(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            0x00);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 9;
    __delay_ms(50);
 
    /* Power down mode */
    i2c1_write1ByteRegister(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            0x00);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 5;
    __delay_ms(50);
    
    return 0;
}

/*
 * mpu9250_i2c_config_dlpf
 * Set current configuration for digital low pass filter for gyro and accel.
 */
uint8_t mpu9250_i2c_config_dlpf(mpu9250 *mpu, dlpf_cfg cfg) {
    uint8_t temp;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ACCEL_CONFIG_2);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ACCEL_CONFIG_2,
            temp & 0xF0 | cfg.a_fchoice_b << 3 | cfg.a_dlpf_cfg);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_GYRO_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 3;
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_GYRO_CONFIG,
            temp & 0xFC | cfg.g_fchoice_b);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 4;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 5;
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_CONFIG,
            temp & 0xF8 | cfg.g_dlpf_cfg);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 6;
    
    return 0;
}

/*
 * mpu9250_i2c_config_fs
 * Set current configuration for only full scale data of gyro and accel.
 */
uint8_t mpu9250_i2c_config_fs(mpu9250 *mpu, full_scale fs) {
    uint8_t temp;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ACCEL_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ACCEL_CONFIG,
            temp & 0xE7 | fs.a_fs << 3);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_GYRO_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 3;
    i2c1_write1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_GYRO_CONFIG,
            temp & 0xE7 | fs.g_fs);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 4;
    
    return 0;
}

/*
 * mpu9250_i2c_get_fs
 * Get current configuration for only full scale data of gyro and accel.
 */
uint8_t mpu9250_i2c_get_fs(mpu9250 *mpu, full_scale *fs) {
    uint8_t temp;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ACCEL_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    fs->a_fs = (temp >> 3) & 0x03;
    temp = i2c1_read1ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_GYRO_CONFIG);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    fs->g_fs = (temp >> 3) & 0x03;
    
    return 0;
}

/*
 * mpu9250_i2c_update_gyro_offset
 * Provide user-specified offset for gyroscope.
 * The offset values become 0 when reset.
 */
uint8_t mpu9250_i2c_update_gyro_offset(mpu9250 *mpu, vector3_16u *gyro) {
    i2c1_write2ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_XG_OFFSET_H,
            gyro->x);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    i2c1_write2ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_YG_OFFSET_H,
            gyro->y);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    i2c1_write2ByteRegister(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_ZG_OFFSET_H,
            gyro->z);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    
    return 0;
}

/*
 * mpu9250_i2c_dump_config
 * Get all the current configuration of the sensor.
 */
uint8_t mpu9250_i2c_dump_config(mpu9250 *mpu, mpu9250_cfg *cfg) {
    i2c1_readDataBlock(
            MPU9250_I2C_ADDR | mpu->addr,
            MPU9250_CONFIG,
            cfg,
            4);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 1;
    i2c1_readDataBlock(
            AK8963_I2C_ADDR | mpu->addr,
            AK8963_CNTL1,
            &(cfg->magneto_cntl1),
            2);
    if (i2c1_getLastError() == I2C1_FAIL_TIMEOUT)
        return 2;
    
    return 0;
}

void mpu9250_i2c_read_gyro(mpu9250 *mpu, vector3 *gyro) {
    
}

void mpu9250_i2c_read_accel(mpu9250 *mpu, vector3 *accel) {
    
}

void mpu9250_i2c_read_magneto(mpu9250 *mpu, vector3 *magneto) {
    
}

void mpu9250_i2c_read_axes6(mpu9250 *mpu, axes6 *data) {
    
}

void mpu9250_i2c_read_axes9(mpu9250 *mpu, axes9 *data) {
    
}