#ifndef MMC_SETTINGS_H
#define MMC_SETTINGS_H

// Bandwidth and Measurement Time Settings
// These settings define the bandwidth and measurement time based on Internal Control 1 Register
#define BW_100HZ_8MS     0x00
#define BW_200HZ_4MS     0x01
#define BW_400HZ_2MS     0x02
#define BW_800HZ_05MS    0x03

// Continuous Measurement Mode Frequencies
// These settings define the continuous measurement mode frequency based on Internal Control 2 Register
#define CMM_OFF          0x00
#define CMM_1HZ          0x01
#define CMM_10HZ         0x02
#define CMM_20HZ         0x03
#define CMM_50HZ         0x04
#define CMM_100HZ        0x05
#define CMM_200HZ_BW01   0x06
#define CMM_1000HZ_BW11  0x07

// Periodic Set Options
// These settings control the periodic set operation based on Internal Control 2 Register
#define PRD_SET_1        0x00
#define PRD_SET_25       0x01
#define PRD_SET_75       0x02
#define PRD_SET_100      0x03
#define PRD_SET_250      0x04
#define PRD_SET_500      0x05
#define PRD_SET_1000     0x06
#define PRD_SET_2000     0x07

// Auto Set/Reset Enable
#define AUTO_SR_DISABLED 0x00
#define AUTO_SR_ENABLED  0x01

// Measurement Mode
#define MEASURE_TEMPERATURE 0x01
#define MEASURE_MAGNETIC    0x00

// Channel Inhibit
#define CHANNEL_ALL_ENABLED 0x00
#define CHANNEL_X_INHIBITED 0x01
#define CHANNEL_YZ_INHIBITED 0x03 // Assumes Y and Z inhibit bits are adjacent

// Software Reset
#define SW_RESET_EXECUTE 0x01

// SPI 3-Wire Mode
#define SPI_4WIRE_MODE   0x00
#define SPI_3WIRE_MODE   0x01

#endif // MMC_SETTINGS_H
