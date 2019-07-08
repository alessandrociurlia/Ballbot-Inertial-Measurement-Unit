/* Authors: Alessandro Ciurlia, Human Mahdavidaronkola, Giacomo D'Amicantonio, Simone Marroncelli, Raffaele Berchicci */

/*******************************************************************************
Includes: <System Includes> , "Project Includes"
*******************************************************************************/
#include <stdbool.h>
#include "main.h"
#include "r_riic_rx600.h"

/*******************************************************************************
Defines
*******************************************************************************/
#define M_PI  								3.14159
#define RIIC_CHANNEL            			CHANNEL_0
#define MPU_ADDRESS 						0xD0
#define MASTER_IIC_ADDRESS_LO				0x20
#define MASTER_IIC_ADDRESS_HI				0x00
#define RW_BIT                  			0x01
#define CHANNEL								0
#define NUM_BYTES							1
#define IIO_VAL_INT 						1
#define IIO_VAL_INT_PLUS_MICRO 				2
#define IIO_VAL_INT_PLUS_NANO 				3
#define IIO_VAL_INT_PLUS_MICRO_DB 			4
#define IIO_VAL_FRACTIONAL 					10
#define IIO_VAL_FRACTIONAL_LOG2 			11
#define INV_MPU6050_BYTES_PER_3AXIS_SENSOR  6
#define INV_MPU6050_FIFO_COUNT_BYTE         2
#define INV_MPU6050_FIFO_THRESHOLD          500
#define INV_MPU6050_POWER_UP_TIME           100
#define INV_MPU6050_TEMP_UP_TIME            100
#define INV_MPU6050_SENSOR_UP_TIME          30
#define INV_MPU6050_REG_UP_TIME             5
#define INV_MPU6050_TEMP_OFFSET	            12421
#define INV_MPU6050_TEMP_SCALE              2941
#define INV_MPU6050_MAX_GYRO_FS_PARAM       3
#define INV_MPU6050_MAX_ACCL_FS_PARAM       3
#define INV_MPU6050_THREE_AXIS              3
#define INV_MPU6050_GYRO_CONFIG_FSR_SHIFT   3
#define INV_MPU6050_ACCL_CONFIG_FSR_SHIFT   3
#define INV_MPU6050_OUTPUT_DATA_SIZE        24
#define INV_MPU6050_INIT_FIFO_RATE          100
#define INV_MPU6050_TIME_STAMP_TOR          5
#define INV_MPU6050_MAX_FIFO_RATE           1000
#define INV_MPU6050_MIN_FIFO_RATE           4
#define INV_MPU6050_ONE_K_HZ                1000
#define INV_MPU6050_REG_SAMPLE_RATE_DIV     0x19
#define INV_MPU6050_REG_CONFIG              0x1A
#define INV_MPU6050_REG_GYRO_CONFIG         0x1B
#define INV_MPU6050_REG_ACCEL_CONFIG	    0x1C
#define INV_MPU6050_REG_FIFO_EN             0x23
#define INV_MPU6050_BIT_ACCEL_OUT           0x08
#define INV_MPU6050_BITS_GYRO_OUT           0x70
#define INV_MPU6050_REG_INT_ENABLE          0x38
#define INV_MPU6050_BIT_DATA_RDY_EN         0x01
#define INV_MPU6050_BIT_DMP_INT_EN          0x02
#define INV_MPU6050_REG_RAW_ACCEL           0x3B
#define INV_MPU6050_REG_RAW_ACCEL_X			0x3B
#define INV_MPU6050_REG_RAW_ACCEL_Y			0x3D
#define INV_MPU6050_REG_RAW_ACCEL_Z			0x3F
#define INV_MPU6050_REG_TEMPERATURE         0x41
#define INV_MPU6050_REG_RAW_GYRO            0x43
#define INV_MPU6050_REG_USER_CTRL           0x6A
#define INV_MPU6050_REG_RAW_GYRO_X          0x43
#define INV_MPU6050_REG_RAW_GYRO_Y          0x45
#define INV_MPU6050_REG_RAW_GYRO_Z          0x47
#define INV_MPU6050_BIT_FIFO_RST            0x04
#define INV_MPU6050_BIT_DMP_RST             0x08
#define INV_MPU6050_BIT_I2C_MST_EN          0x20
#define INV_MPU6050_BIT_FIFO_EN             0x40
#define INV_MPU6050_BIT_DMP_EN              0x80
#define INV_MPU6050_REG_PWR_MGMT_1          0x6B
#define INV_MPU6050_BIT_H_RESET             0x80
#define INV_MPU6050_BIT_SLEEP               0x40
#define INV_MPU6050_BIT_CLK_MASK            0x7
#define INV_MPU6050_REG_PWR_MGMT_2          0x6C
#define INV_MPU6050_BIT_PWR_ACCL_STBY       0x38
#define INV_MPU6050_BIT_PWR_GYRO_STBY       0x07
#define INV_MPU6050_REG_FIFO_COUNT_H        0x72
#define INV_MPU6050_REG_FIFO_R_W            0x74
#define INV_MPU6050_REG_WHO_AM_I			0x75
#define INV_MPU6050_DEVICE_ID				0x68

/*******************************************************************************
Definizione strutture
*******************************************************************************/
IMU_data_struct x;

riic_config_t riic_master_config =  {RIIC_CHANNEL,
									 RIIC_MASTER_CONFIG,
                                     0,
                                     0,
                                     0,
                                     0,
                                     MASTER_IIC_ADDRESS_LO,
                                     MASTER_IIC_ADDRESS_HI};

/*******************************************************************************
Definizione variabili
*******************************************************************************/
unsigned char ERROR_HEAD_WRITE = 0;
unsigned char ERROR_WRITE = 0;
unsigned char ERROR_HEAD_READ = 0;
unsigned char ERROR_READ = 0;
int ERR_COUNT = 0;

enum inv_mpu6050_filter_e {
	INV_MPU6050_FILTER_256HZ_NODLPF = 0,
	INV_MPU6050_FILTER_188HZ,
	INV_MPU6050_FILTER_98HZ,
	INV_MPU6050_FILTER_42HZ,
	INV_MPU6050_FILTER_20HZ,
	INV_MPU6050_FILTER_10HZ,
	INV_MPU6050_FILTER_5HZ,
	INV_MPU6050_FILTER_2100HZ_NODLPF,
	NUM_MPU6050_FILTER
};

enum inv_mpu6050_accl_fs_e {
	INV_MPU6050_FS_02G = 0,
	INV_MPU6050_FS_04G,
	INV_MPU6050_FS_08G,
	INV_MPU6050_FS_16G,
	NUM_ACCL_FSR
};

enum inv_mpu6050_fsr_e {
	INV_MPU6050_FSR_250DPS = 0,
	INV_MPU6050_FSR_500DPS,
	INV_MPU6050_FSR_1000DPS,
	INV_MPU6050_FSR_2000DPS,
	NUM_MPU6050_FSR
};

/*******************************************************************************
Prototipi funzioni
*******************************************************************************/
static riic_ret_t IMU_write (uint8_t riic_channel, uint8_t slave_addr, uint8_t register_number, uint8_t *source_buff, uint32_t num_bytes);
static riic_ret_t IMU_read (uint8_t riic_channel, uint8_t slave_addr, uint8_t register_number, uint8_t *dest_buff, uint32_t num_bytes);
static int16_t  IMU_axis_read (uint8_t axis);
void Accel_init (IMU_data_struct *x);
void Gyro_init (IMU_data_struct *x);
static riic_ret_t IMU_config(void);
riic_ret_t IMU_set_power(bool power_on);


