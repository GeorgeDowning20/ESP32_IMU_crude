
#ifndef ISM330DHCX_REGISTERS_H
#define ISM330DHCX_REGISTERS_H

#define ISM330DHCX_ADDRESS             0x6B

// ISM330DHCX Device Identification
#define ISM330DHCX_WHO_AM_I           0x0F

// ISM330DHCX Control Registers
#define ISM330DHCX_CTRL1_XL           0x10
#define ISM330DHCX_CTRL2_G            0x11
#define ISM330DHCX_CTRL3_C            0x12
#define ISM330DHCX_CTRL4_C            0x13
#define ISM330DHCX_CTRL5_C            0x14
#define ISM330DHCX_CTRL6_C            0x15
#define ISM330DHCX_CTRL7_G            0x16
#define ISM330DHCX_CTRL8_XL           0x17
#define ISM330DHCX_CTRL9_XL           0x18
#define ISM330DHCX_CTRL10_C           0x19

// ISM330DHCX Status Registers
#define ISM330DHCX_STATUS_REG         0x1E

// ISM330DHCX Output Registers
#define ISM330DHCX_OUT_TEMP_L         0x20
#define ISM330DHCX_OUT_TEMP_H         0x21
#define ISM330DHCX_OUTX_L_G           0x22
#define ISM330DHCX_OUTX_H_G           0x23
#define ISM330DHCX_OUTY_L_G           0x24
#define ISM330DHCX_OUTY_H_G           0x25
#define ISM330DHCX_OUTZ_L_G           0x26
#define ISM330DHCX_OUTZ_H_G           0x27
#define ISM330DHCX_OUTX_L_A           0x28
#define ISM330DHCX_OUTX_H_A           0x29
#define ISM330DHCX_OUTY_L_A           0x2A
#define ISM330DHCX_OUTY_H_A           0x2B
#define ISM330DHCX_OUTZ_L_A           0x2C
#define ISM330DHCX_OUTZ_H_A           0x2D

// ISM330DHCX FIFO Registers
#define ISM330DHCX_FIFO_CTRL1         0x07
#define ISM330DHCX_FIFO_CTRL2         0x08
#define ISM330DHCX_FIFO_CTRL3         0x09
#define ISM330DHCX_FIFO_CTRL4         0x0A
#define ISM330DHCX_FIFO_CTRL5         0x0B
#define ISM330DHCX_FIFO_DATA_OUT_L    0x3E
#define ISM330DHCX_FIFO_DATA_OUT_H    0x3F

// ISM330DHCX Interrupt Registers
#define ISM330DHCX_INT1_CTRL          0x0D
#define ISM330DHCX_INT2_CTRL          0x0E

// Additional definitions can be added as needed

#endif // ISM330DHCX_REGISTERS_H
