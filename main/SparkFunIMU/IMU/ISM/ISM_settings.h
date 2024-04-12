//Accelerometer Full Scale
#define ISM330DHCX_2g    0
#define ISM330DHCX_16g   1
#define ISM330DHCX_4g    2
#define ISM330DHCX_8g    3

//Gyroscope Full Scale
#define ISM330DHCX_125dps    2
#define ISM330DHCX_250dps    0
#define ISM330DHCX_500dps    4
#define ISM330DHCX_1000dps   8
#define ISM330DHCX_2000dps   12
#define ISM330DHCX_4000dps   1

//Acceleromter Output Data Rate
#define ISM330DHCX_XL_ODR_OFF     0
#define ISM330DHCX_XL_ODR_12Hz5   1
#define ISM330DHCX_XL_ODR_26Hz    2
#define ISM330DHCX_XL_ODR_52Hz    3
#define ISM330DHCX_XL_ODR_104Hz   4
#define ISM330DHCX_XL_ODR_208Hz   5
#define ISM330DHCX_XL_ODR_416Hz   6
#define ISM330DHCX_XL_ODR_833Hz   7
#define ISM330DHCX_XL_ODR_1666Hz  8
#define ISM330DHCX_XL_ODR_3332Hz  9
#define ISM330DHCX_XL_ODR_6667Hz  10
#define ISM330DHCX_XL_ODR_1Hz6    11

//Gyroscope Output Data Rate
#define ISM330DHCX_GY_ODR_OFF     0
#define ISM330DHCX_GY_ODR_12Hz    1
#define ISM330DHCX_GY_ODR_26Hz    2
#define ISM330DHCX_GY_ODR_52Hz    3
#define ISM330DHCX_GY_ODR_104Hz   4
#define ISM330DHCX_GY_ODR_208Hz   5
#define ISM330DHCX_GY_ODR_416Hz   6
#define ISM330DHCX_GY_ODR_833Hz   7
#define ISM330DHCX_GY_ODR_1666Hz  8
#define ISM330DHCX_GY_ODR_3332Hz  9
#define ISM330DHCX_GY_ODR_6667Hz  10

//Gyro Bandwidth set
#define ISM330DHCX_ULTRA_LIGHT   0
#define ISM330DHCX_VERY_LIGHT    1
#define ISM330DHCX_LIGHT         2
#define ISM330DHCX_MEDIUM        3
#define ISM330DHCX_STRONG        4
#define ISM330DHCX_VERY_STRONG   5
#define ISM330DHCX_AGGRESSIVE    6
#define ISM330DHCX_XTREME        7

// Gyro high performance filters												
#define ISM330DHCX_HP_FILTER_NONE    0x00
#define ISM330DHCX_HP_FILTER_16mHz   0x80
#define ISM330DHCX_HP_FILTER_65mHz   0x81
#define ISM330DHCX_HP_FILTER_260mHz  0x82
#define ISM330DHCX_HP_FILTER_1Hz04   0x83

//Accel Regular Performance Filter Settings
#define ISM330DHCX_HP_PATH_DISABLE_ON_OUT  0x00
#define ISM330DHCX_SLOPE_ODR_DIV_4         0x10
#define ISM330DHCX_HP_ODR_DIV_10           0x11
#define ISM330DHCX_HP_ODR_DIV_20           0x12
#define ISM330DHCX_HP_ODR_DIV_45           0x13
#define ISM330DHCX_HP_ODR_DIV_100          0x14
#define ISM330DHCX_HP_ODR_DIV_200          0x15
#define ISM330DHCX_HP_ODR_DIV_400          0x16
#define ISM330DHCX_HP_ODR_DIV_800          0x17
#define ISM330DHCX_HP_REF_MD_ODR_DIV_10    0x31
#define ISM330DHCX_HP_REF_MD_ODR_DIV_20    0x32
#define ISM330DHCX_HP_REF_MD_ODR_DIV_45    0x33
#define ISM330DHCX_HP_REF_MD_ODR_DIV_100   0x34
#define ISM330DHCX_HP_REF_MD_ODR_DIV_200   0x35
#define ISM330DHCX_HP_REF_MD_ODR_DIV_400   0x36
#define ISM330DHCX_HP_REF_MD_ODR_DIV_800   0x37
#define ISM330DHCX_LP_ODR_DIV_10           0x01
#define ISM330DHCX_LP_ODR_DIV_20           0x02
#define ISM330DHCX_LP_ODR_DIV_45           0x03
#define ISM330DHCX_LP_ODR_DIV_100          0x04
#define ISM330DHCX_LP_ODR_DIV_200          0x05
#define ISM330DHCX_LP_ODR_DIV_400          0x06
#define ISM330DHCX_LP_ODR_DIV_800          0x07

//FIFO Mode Settings
#define ISM330DHCX_BYPASS_MODE           0x00
#define ISM330DHCX_FIFO_MODE             0x01
#define ISM330DHCX_STREAM_TO_FIFO_MODE   0x03
#define ISM330DHCX_BYPASS_TO_STREAM_MODE 0x04
#define ISM330DHCX_STREAM_MODE           0x06
#define ISM330DHCX_BYPASS_TO_FIFO_MODE   0x07

//FIFO Accelerometer Batch Settings
#define ISM330DHCX_XL_NOT_BATCHED       0x00
#define ISM330DHCX_XL_BATCH_AT_12Hz5    0x01
#define ISM330DHCX_XL_BATCH_AT_26Hz     0x02
#define ISM330DHCX_XL_BATCH_AT_52Hz     0x03
#define ISM330DHCX_XL_BATCH_AT_104Hz    0x04
#define ISM330DHCX_XL_BATCH_AT_208Hz    0x05
#define ISM330DHCX_XL_BATCH_AT_417Hz    0x06
#define ISM330DHCX_XL_BATCH_AT_833Hz    0x07
#define ISM330DHCX_XL_BATCH_AT_1667Hz   0x08
#define ISM330DHCX_XL_BATCH_AT_3333Hz   0x09
#define ISM330DHCX_XL_BATCH_AT_6667Hz   0x010
#define ISM330DHCX_XL_BATCH_6Hz5        0x011

//FIFO Gyroscope Batch Settings
#define ISM330DHCX_GY_NOT_BATCHED      0x00
#define ISM330DHCX_GY_BATCH_AT_12Hz5    0x01
#define ISM330DHCX_GY_BATCH_AT_26Hz     0x02
#define ISM330DHCX_GY_BATCH_AT_52Hz     0x03
#define ISM330DHCX_GY_BATCH_AT_104Hz    0x04
#define ISM330DHCX_GY_BATCH_AT_208Hz    0x05
#define ISM330DHCX_GY_BATCH_AT_417Hz    0x06
#define ISM330DHCX_GY_BATCH_AT_833Hz    0x07
#define ISM330DHCX_GY_BATCH_AT_1667Hz   0x08
#define ISM330DHCX_GY_BATCH_AT_3333Hz   0x09
#define ISM330DHCX_GY_BATCH_AT_6667Hz   0x010
#define ISM330DHCX_GY_BATCH_6Hz5        0x011

//Decimation rate
#define ISM330DHCX_NO_DECIMATION 0x00
#define ISM330DHCX_DEC_1         0x01
#define ISM330DHCX_DEC_8         0x02
#define ISM330DHCX_DEC_32        0x03

//Interrupt pin notification settings.
#define ISM330DHCX_ALL_INT_PULSED            0x00
#define ISM330DHCX_BASE_LATCHED_EMB_PULSED   0x01
#define ISM330DHCX_BASE_PULSED_EMB_LATCHED   0x02
#define ISM330DHCX_ALL_INT_LATCHED           0x03

#define ISM330DHCX_SH_ODR_104Hz 0x00
#define ISM330DHCX_SH_ODR_52Hz  0x01
#define ISM330DHCX_SH_ODR_26Hz  0x02
#define ISM330DHCX_SH_ODR_13Hz  0x03