// Self-Test Registers
#define MPU6050_SELF_TEST_X 0x0D
#define MPU6050_SELF_TEST_Y 0x0E
#define MPU6050_SELF_TEST_Z 0x0F
#define MPU6050_SELF_TEST_A 0x10

// Sample Rate Divider
#define MPU6050_SMPLRT_DIV 0x19

// Configuration
#define MPU6050_CONFIG 0x1A

// Gyro Configuration
#define MPU6050_GYRO_CONFIG 0x1B

// Accelerometer Configuration
#define MPU6050_ACCEL_CONFIG 0x1C

// Free-fall
#define MPU6050_FF_THR 0x1D
#define MPU6050_FF_DUR 0x1E

// Motion Detection
#define MPU6050_MOT_THR 0x1F
#define MPU6050_MOT_DUR 0x20

// Zero Motion Detection
#define MPU6050_ZRMOT_THR 0x21
#define MPU6050_ZRMOT_DUR 0x22

// FIFO Enable
#define MPU6050_FIFO_EN 0x23

// I2C Master Control
#define MPU6050_I2C_MST_CTRL 0x24

// I2C Slave 0
#define MPU6050_I2C_SLV0_ADDR 0x25
#define MPU6050_I2C_SLV0_REG 0x26
#define MPU6050_I2C_SLV0_CTRL 0x27

// I2C Slave 1
#define MPU6050_I2C_SLV1_ADDR 0x28
#define MPU6050_I2C_SLV1_REG 0x29
#define MPU6050_I2C_SLV1_CTRL 0x2A

// I2C Slave 2
#define MPU6050_I2C_SLV2_ADDR 0x2B
#define MPU6050_I2C_SLV2_REG 0x2C
#define MPU6050_I2C_SLV2_CTRL 0x2D

// I2C Slave 3
#define MPU6050_I2C_SLV3_ADDR 0x2E
#define MPU6050_I2C_SLV3_REG 0x2F
#define MPU6050_I2C_SLV3_CTRL 0x30

// I2C Slave 4
#define MPU6050_I2C_SLV4_ADDR 0x31
#define MPU6050_I2C_SLV4_REG 0x32
#define MPU6050_I2C_SLV4_DO 0x33
#define MPU6050_I2C_SLV4_CTRL 0x34
#define MPU6050_I2C_SLV4_DI 0x35

// I2C Master Status
#define MPU6050_I2C_MST_STATUS 0x36

// Interrupt PIN / Bypass Enable Configuration
#define MPU6050_INT_PIN_CFG 0x37

// Interrupt Enable
#define MPU6050_INT_ENABLE 0x38

// Interrupt Status
#define MPU6050_INT_STATUS 0x3A

// Accelerometer Measurements
#define MPU6050_ACCEL_XOUT_H 0x3B
#define MPU6050_ACCEL_XOUT_L 0x3C
#define MPU6050_ACCEL_YOUT_H 0x3D
#define MPU6050_ACCEL_YOUT_L 0x3E
#define MPU6050_ACCEL_ZOUT_H 0x3F
#define MPU6050_ACCEL_ZOUT_L 0x40

// Temperature Measurement
#define MPU6050_TEMP_OUT_H 0x41
#define MPU6050_TEMP_OUT_L 0x42

// Gyroscope Measurements
#define MPU6050_GYRO_XOUT_H 0x43
#define MPU6050_GYRO_XOUT_L 0x44
#define MPU6050_GYRO_YOUT_H 0x45
#define MPU6050_GYRO_YOUT_L 0x46
#define MPU6050_GYRO_ZOUT_H 0x47

// who am i
#define MPU6050_WHO_AM_I 0x75