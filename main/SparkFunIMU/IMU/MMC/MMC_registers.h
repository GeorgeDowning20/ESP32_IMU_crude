#ifndef MMC_REGISTERS_H
#define MMC_REGISTERS_H

// Address of the registers
#define MMC5983MA_XOUT0            0x00
#define MMC5983MA_XOUT1            0x01
#define MMC5983MA_YOUT0            0x02
#define MMC5983MA_YOUT1            0x03
#define MMC5983MA_ZOUT0            0x04
#define MMC5983MA_ZOUT1            0x05
#define MMC5983MA_XYZOUT2          0x06
#define MMC5983MA_TOUT             0x07
#define MMC5983MA_STATUS           0x08
#define MMC5983MA_INTERNAL_CTRL_0  0x09
#define MMC5983MA_INTERNAL_CTRL_1  0x0A
#define MMC5983MA_INTERNAL_CTRL_2  0x0B
#define MMC5983MA_INTERNAL_CTRL_3  0x0C
#define MMC5983MA_PRODUCT_ID       0x2F

// Status Register Bits
#define MMC5983MA_OTP_RD_DONE      (1 << 6)
#define MMC5983MA_MEAS_T_DONE      (1 << 2)
#define MMC5983MA_MEAS_M_DONE      (1 << 1)

// Internal Control 0 Register Bits
#define MMC5983MA_OTP_READ         (1 << 6)
#define MMC5983MA_AUTO_SR_EN       (1 << 5)
#define MMC5983MA_RESET            (1 << 4)
#define MMC5983MA_SET              (1 << 3)
#define MMC5983MA_INT_MEAS_DONE_EN (1 << 2)
#define MMC5983MA_TM_T             (1 << 1)
#define MMC5983MA_TM_M             (1 << 0)

// Internal Control 1 Register Bits
// BW0 and BW1 are used together to set bandwidth
#define MMC5983MA_SW_RST           (1 << 7)
#define MMC5983MA_YZ_INHIBIT       (1 << 5) // Apply to both Y and Z inhibit bits
#define MMC5983MA_X_INHIBIT        (1 << 4)
#define MMC5983MA_BW1              (1 << 1)
#define MMC5983MA_BW0              (1 << 0)

// Internal Control 2 Register Bits
// CM_FREQ and PRD_SET are used together for frequency and periodic set settings
#define MMC5983MA_EN_PRD_SET       (1 << 7)
#define MMC5983MA_CMM_EN           (1 << 3)

// Internal Control 3 Register Bits
#define MMC5983MA_SPI_3W           (1 << 6)
#define MMC5983MA_ST_ENM           (1 << 4)
#define MMC5983MA_ST_ENP           (1 << 3)

// Device ID for MMC5983MA
#define MMC5983MA_DEVICE_ID 0x30 // Example value, verify with actual device

#endif // MMC_REGISTERS_H
