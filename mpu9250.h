/* 
 * File:   mpu9250.h
 * Author: Jaerin Lee
 * Comments: MPU9250 with AK8963 sensor driver
 * Revision history: 
 */

#ifndef MPU9250_H
#define	MPU9250_H

#ifdef __cplusplus
//extern "C" {
#endif

#include "mcc_generated_files/device_config.h"
#include "mcc_generated_files/i2c1.h"

#define MPU9250_I2C_ADDR 0b1101000 /* 0b110100X, where X is SDO */
#define AK8963_I2C_ADDR 0b0001100 /* 0b000110X, where X is SDO */

/* MPU9250 register addresses */
#define MPU9250_SELF_TEST_X_GYRO 0x00
#define MPU9250_SELF_TEST_Y_GYRO 0x01
#define MPU9250_SELF_TEST_Z_GYRO 0x02
#define MPU9250_SELF_TEST_X_ACCEL 0x0D
#define MPU9250_SELF_TEST_Y_ACCEL 0x0E
#define MPU9250_SELF_TEST_Z_ACCEL 0x0F
#define MPU9250_XG_OFFSET_H 0x13
#define MPU9250_XG_OFFSET_L 0x14
#define MPU9250_YG_OFFSET_H 0x15
#define MPU9250_YG_OFFSET_L 0x16
#define MPU9250_ZG_OFFSET_H 0x17
#define MPU9250_ZG_OFFSET_L 0x18
#define MPU9250_SMPLRT_DIV 0x19
#define MPU9250_CONFIG 0x1A
#define MPU9250_GYRO_CONFIG 0x1B
#define MPU9250_ACCEL_CONFIG 0x1C
#define MPU9250_ACCEL_CONFIG_2 0x1D
#define MPU9250_LP_ACCEL_ODR 0x1E
#define MPU9250_WOM_THR 0x1F
#define MPU9250_FIFO_EN 0x23
#define MPU9250_I2C_MST_CTRL 0x24
#define MPU9250_I2C_SLV0_ADDR 0x25
#define MPU9250_I2C_SLV0_REG 0x26
#define MPU9250_I2C_SLV0_CTRL 0x27
#define MPU9250_I2C_SLV1_ADDR 0x28
#define MPU9250_I2C_SLV1_REG 0x29
#define MPU9250_I2C_SLV1_CTRL 0x2A
#define MPU9250_I2C_SLV2_ADDR 0x2B
#define MPU9250_I2C_SLV2_REG 0x2C
#define MPU9250_I2C_SLV2_CTRL 0x2D
#define MPU9250_I2C_SLV3_ADDR 0x2E
#define MPU9250_I2C_SLV3_REG 0x2F
#define MPU9250_I2C_SLV3_CTRL 0x30
#define MPU9250_I2C_SLV4_ADDR 0x31
#define MPU9250_I2C_SLV4_REG 0x32
#define MPU9250_I2C_SLV4_DO 0x33
#define MPU9250_I2C_SLV4_CTRL 0x34
#define MPU9250_I2C_SLV4_DI 0x35
#define MPU9250_I2C_MST_STATUS 0x36
#define MPU9250_INT_PIN_CFG 0x37
#define MPU9250_INT_ENABLE 0x38
#define MPU9250_INT_STATUS 0x3A
#define MPU9250_ACCEL_XOUT_H 0x3B
#define MPU9250_ACCEL_XOUT_L 0x3C
#define MPU9250_ACCEL_YOUT_H 0x3D
#define MPU9250_ACCEL_YOUT_L 0x3E
#define MPU9250_ACCEL_ZOUT_H 0x3F
#define MPU9250_ACCEL_ZOUT_L 0x40
#define MPU9250_TEMP_OUT_H 0x41
#define MPU9250_TEMP_OUT_L 0x42
#define MPU9250_GYRO_XOUT_H 0x43
#define MPU9250_GYRO_XOUT_L 0x44
#define MPU9250_GYRO_YOUT_H 0x45
#define MPU9250_GYRO_YOUT_L 0x46
#define MPU9250_GYRO_ZOUT_H 0x47
#define MPU9250_GYRO_ZOUT_L 0x48
#define MPU9250_EXT_SENS_DATA_00 0x49
#define MPU9250_EXT_SENS_DATA_01 0x4A
#define MPU9250_EXT_SENS_DATA_02 0x4B
#define MPU9250_EXT_SENS_DATA_03 0x4C
#define MPU9250_EXT_SENS_DATA_04 0x4D
#define MPU9250_EXT_SENS_DATA_05 0x4E
#define MPU9250_EXT_SENS_DATA_06 0x4F
#define MPU9250_EXT_SENS_DATA_07 0x50
#define MPU9250_EXT_SENS_DATA_08 0x51
#define MPU9250_EXT_SENS_DATA_09 0x52
#define MPU9250_EXT_SENS_DATA_10 0x53
#define MPU9250_EXT_SENS_DATA_11 0x54
#define MPU9250_EXT_SENS_DATA_12 0x55
#define MPU9250_EXT_SENS_DATA_13 0x56
#define MPU9250_EXT_SENS_DATA_14 0x57
#define MPU9250_EXT_SENS_DATA_15 0x58
#define MPU9250_EXT_SENS_DATA_16 0x59
#define MPU9250_EXT_SENS_DATA_17 0x5A
#define MPU9250_EXT_SENS_DATA_18 0x5B
#define MPU9250_EXT_SENS_DATA_19 0x5C
#define MPU9250_EXT_SENS_DATA_20 0x5D
#define MPU9250_EXT_SENS_DATA_21 0x5E
#define MPU9250_EXT_SENS_DATA_22 0x5F
#define MPU9250_EXT_SENS_DATA_23 0x60
#define MPU9250_I2C_SLV0_DO 0x63
#define MPU9250_I2C_SLV1_DO 0x64
#define MPU9250_I2C_SLV2_DO 0x65
#define MPU9250_I2C_SLV3_DO 0x66
#define MPU9250_I2C_MST_DELAY_CTRL 0x67
#define MPU9250_SIGNAL_PATH_RESET 0x68
#define MPU9250_MOT_DETECT_CTRL 0x69
#define MPU9250_USER_CTRL 0x6A
#define MPU9250_PWR_MGMT_1 0x6B
#define MPU9250_PWR_MGMT_2 0x6C
#define MPU9250_FIFO_COUNTH 0x72
#define MPU9250_FIFO_COUNTL 0x73
#define MPU9250_FIFO_R_W 0x74
#define MPU9250_WHO_AM_I 0x75
#define MPU9250_XA_OFFSET_H 0x77
#define MPU9250_XA_OFFSET_L 0x78
#define MPU9250_YA_OFFSET_H 0x7A
#define MPU9250_YA_OFFSET_L 0x7B
#define MPU9250_ZA_OFFSET_H 0x7D
#define MPU9250_ZA_OFFSET_L 0x7E

/* MPU9250 Chip ID */
#define MPU9250_CHIPID 0x71

/* Gyro full-scale option */
#define MPU9250_GFS_250  0x0 // +-250dps
#define MPU9250_GFS_500  0x1 // +-500dps
#define MPU9250_GFS_1000 0x2 // +-1000dps
#define MPU9250_GFS_2000 0x3 // +-2000dps

/* Accel full-scale option */
#define MPU9250_AFS_2G  0x0 // 2g
#define MPU9250_AFS_4G  0x1 // 4g
#define MPU9250_AFS_8G  0x2 // 8g
#define MPU9250_AFS_16G 0x3 // 16g

#define MPU9250_MAX_14S_UINT 8192
#define MPU9250_MAX_14S_FLOAT 8192.0f
#define MPU9250_MAX_16S_UINT 32768
#define MPU9250_MAX_16S_FLOAT 32768.0f

/* AK8963 register addresses */
#define AK8963_WIA 0x00
#define AK8963_INFO 0x01
#define AK8963_ST1 0x02
#define AK8963_HXL 0x03
#define AK8963_HXH 0x04
#define AK8963_HYL 0x05
#define AK8963_HYH 0x06
#define AK8963_HZL 0x07
#define AK8963_HZH 0x08
#define AK8963_ST2 0x09
#define AK8963_CNTL1 0x0A
#define AK8963_CNTL2 0x0B
#define AK8963_ASTC 0x0C
#define AK8963_TS1 0x0D
#define AK8963_TS2 0x0E
#define AK8963_I2CDIS 0x0F
#define AK8963_ASAX 0x10
#define AK8963_ASAY 0x11
#define AK8963_ASAZ 0x12
#define AK8963_RSV 0x13

/* AK8963 CNTL1 operation mode */
#define AK8963_MODE_DOWN 0x00 // Power down mode
#define AK8963_MODE_ONE 0x01 // One shot data output
#define AK8963_MODE_C8HZ 0x02 // Continous data output 8Hz
#define AK8963_MODE_C100HZ 0x06 // Continous data output 100Hz
#define AK8963_MODE_TRIG 0x04 // External trigger data output
#define AK8963_MODE_TEST 0x08 // Self test
#define AK8963_MODE_FUSE 0x0F // Fuse ROM access

/* Magneto scale option */
#define AK8963_BIT_14 0x0 // 14bit output
#define AK8963_BIT_16 0x1 // 16bit output

#define AK8963_MAX_UINT 4912
#define AK8963_MAX_FLOAT 4912.0f

typedef struct {
    unsigned a_fchoice_b : 1;
    unsigned a_dlpf_cfg : 3;
    unsigned g_fchoice_b : 2;
    unsigned g_dlpf_cfg : 3;
} dlpf_cfg;

typedef struct {
    unsigned a_fs : 2;
    unsigned g_fs : 2;
    unsigned m_fs : 1;
} full_scale;

typedef struct {
    uint8_t cfg;
    uint8_t gyro_cfg;
    uint8_t accel_cfg;
    uint8_t accel_cfg2;
    uint8_t magneto_cntl1;
    uint8_t magneto_cntl2;
} mpu9250_cfg;

typedef struct {
    int16_t x;
    int16_t y;
    int16_t z;
} vector3_16s;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t z;
} vector3_16u;

typedef struct {
    vector3_16s accel;
    uint16_t temp;
    vector3_16s gyro;
} axes6_raw;

typedef struct {
    vector3_16s accel;
    uint16_t temp;
    vector3_16s gyro;
    vector3_16s magneto;
} axes9_raw;

typedef struct {
    uint8_t addr;
    full_scale scale;
    vector3_16u mag_factor;
} mpu9250;

/* Function declaration */
uint8_t mpu9250_i2c_init(mpu9250 *, uint8_t);
uint8_t mpu9250_i2c_config_dlpf(mpu9250 *, dlpf_cfg *);
uint8_t mpu9250_i2c_config_fs(mpu9250 *, uint8_t);
uint8_t mpu9250_i2c_get_fs(mpu9250 *, full_scale *, uint8_t);
uint8_t mpu9250_i2c_update_gyro_offset(mpu9250 *, vector3_16s *);
uint8_t mpu9250_i2c_dump_config(mpu9250 *, mpu9250_cfg *);
uint8_t mpu9250_i2c_read_gyro_raw(mpu9250 *, vector3_16s *);
uint8_t mpu9250_i2c_read_accel_raw(mpu9250 *, vector3_16s *);
uint8_t mpu9250_i2c_read_magneto_raw(mpu9250 *, vector3_16s *);
uint8_t mpu9250_i2c_read_axes6_raw(mpu9250 *, axes6_raw *);
uint8_t mpu9250_i2c_read_axes9_raw(mpu9250 *, axes9_raw *);

/* More complicated tasks */
uint8_t mpu9250_gyro_zeroadj(mpu9250 *, uint8_t, uint8_t);

#ifdef __cplusplus
//}
#endif

#endif	/* MPU9250_H */

