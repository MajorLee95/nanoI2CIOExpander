/**
* @file config.h
* @author J.SORANZO
* @date 03/12/2018
* @copyright 2018 MIT
* @version git versionning
* @brief nanoI2CIOexpander porject configuration file
*/

/**
* @def MA_VERSION
* @brief project version not file version

This version is manualy udated

* @def MI_VERSION
* @brief Minor version

*/
#define MA_VERSION 1 /**< The major part of version number*/
#define MI_VERSION 1 /**< The minor Part of the version*/

/**
* @def MAXREG
* @brief Maximum number of register

- 0x00 : Major version (RO)
- 0x01 : R/W test reg 1
- 0x02 : R/W test reg 2
- 0x03 : 0x55 (RO)
- 0x04 : DDR (R/W) 1 for output, default 0
- 0x05 : digital DATA (R/W) a write on input bit has no effect
- 0x06 : Minor version (RO)
- 0x07 : puulup reg (R/W) : 1 pullup is enable, default = 0
- 0x08 to 0x0F : reserved (read data 0xA5)


- 0x10, 0x11 : A0 low, high (RO)
- 0x12, 0x13 : A1 low, high (RO)
- 0x14, 0x15 : A2 low, high (RO)
- 0x16, 0x17 : A3 low, high (RO)
- 0x18, 0x19 : 0xCA low, 0xFE high (RO)
- 0x1A, 0x1B : 0xFE low, 0xCA high (RO)
- 0x1C, 0x1D : A6 low, high (RO)
- 0x1E, 0x1F : A7 low, high (RO)

RO : Read Only
R/W : Read and Write enabled registers

Writable registers are : 1,2,4,5 and 7
*/
#define MAXREG 32



/**
* @def I2CADD
* @brief I2C base address to be completed by D12..D10 pin states

This number is ored with D12..D10 state to obtain full I2C address

Warning D12 to D10 are internaly pulluped

*/
#define I2CADD 0x58
#define I2CHIGHADD 12
#define I2CMIDADD 11
#define I2CLOWADD 10


/**
* @def ARDUINO_TYPE
* @brief Only for debug display
*/
#define ARDUINO_TYPE    "MEGA"
