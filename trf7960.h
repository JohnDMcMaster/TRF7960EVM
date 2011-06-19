/*
trf7960evm port
Original code Copyright (C) 2006-2007 Texas Instruments, Inc.
Modifications copyright 2011 John McMaster <JohnDMcMaster@gmail.com>
See COPYING for details
*/

/*
host.h had many similar defines
They were mostly unused and also didn't follow C naming conventions
*/

#ifndef TRF7960_H
#define TRF7960_H

/*
Upper bit field
*/
//Write a single register
#define REG_WRITE(reg)					(reg)
//Continuous
#define REG_WRITEC(reg)					((reg) | 0x20)
//Read a single register
#define REG_READ(reg)					((reg) | 0x40)
//Continuous
#define REG_READC(reg)					((reg) | 0x60)
//Commands require upper bit set and next upper 2 clear
#define CMD(command)					((command) | 0x80)

/*
Commands
Commands are up to 5 bits
*/
/*
Command Code (hex) Command                                    Comments
*/
//00          Idle
#define CMD_IDLE				0x00
//03          Software Initialization                         Software initialization, same as power on reset
#define CMD_INIT				0x03
//0F          Reset
#define CMD_RESET				0x0F
//10          Transmission without CRC
#define CMD_WO_CRC				0x10
//11          Transmission with CRC
#define CMD_W_CRC				0x11
//12          Delayed transmission without CRC
#define CMD_DELAYED_TX_WO_CRC	0x12
//13          Delayed transmission with CRC
#define CMD_DELAYED_TX_W_CRC	0x13
//14          Transmit next time slot                         ISO15693, Tag-It
#define CMD_TX_NEXT				0x14
//16          Block receiver
#define CMD_DISABLE_RX			0x16
//17          Enable receiver
#define CMD_ENABLE_RX			0x17
//18          Test internal RF (RSSI at RX input with TX ON)
#define CMD_TEST_INTERNAL_RF	0x18
//19          Test external RF (RSSI at RX input with TX OFF)
#define CMD_TEST_EXTERNAL_RF	0x19
//1A           Receiver gain adjust
#define	CMD_RX_GAIN_ADJUST		0x1A


/*
Registers
*/
/*
Adr (hex)    Register                                      Read/Write
*/
/*
Main Control Registers
*/
//00           Chip status control                            R/W
#define REG_CHIP_STATUS_CONTROL			0x00
//Standby/active
#define REG_CHIP_STATUS_CONTROL_STANDBY			0x80
#define REG_CHIP_STATUS_CONTROL_ACTIVE			0x00
//Sub-carrier/decoded
#define REG_CHIP_STATUS_CONTROL_SUB_CARRIER		0x40
#define REG_CHIP_STATUS_CONTROL_DECODED			0x00
//RF active/inactive
#define REG_CHIP_STATUS_CONTROL_RF_ACTIVE		0x20
#define REG_CHIP_STATUS_CONTROL_RF_INACTIVE		0x00
//Half/full TX power
//8 ohm driver
#define REG_CHIP_STATUS_CONTROL_HALF_TX_POWER	0x10
//4 ohm driver
#define REG_CHIP_STATUS_CONTROL_FULL_TX_POWER	0x00
//PM/AM
//PM signal input on IN2
#define REG_CHIP_STATUS_CONTROL_RX_PM			0x80
//AM signal input on IN1
#define REG_CHIP_STATUS_CONTROL_RX_AM			0x00
//AGC
#define REG_CHIP_STATUS_CONTROL_AGC_ON			0x40
#define REG_CHIP_STATUS_CONTROL_AGC_OFF			0x00
//Receiver enable for external field
#define REG_CHIP_STATUS_CONTROL_RX_MEAURE_ON	0x20
#define REG_CHIP_STATUS_CONTROL_RX_MEAURE_OFF	0x00
//Vdd range
#define REG_CHIP_STATUS_CONTROL_VRS_5			0x10
#define REG_CHIP_STATUS_CONTROL_VRS_3			0x00				


//01           ISO control                                    R/W
#define REG_ISO_CONTROL				0x01
#define REG_ISO_CONTROL_RX_WO_CRC				0x80
#define REG_ISO_CONTROL_RX_W_CRC				0x00
#define REG_ISO_CONTROL_DIR_MODE_SUB_CARRIER	0x40
#define REG_ISO_CONTROL_DIR_MODE_BIT			0x00
//high bit always 0
#define REG_ISO_CONTROL_RFID_MODE(mode)			(mode)
//SO14443A bit rate 106 kbps
#define REG_ISO_CONTROL_RFID_MODE_ISO14443A_106	0x08

/*
Protocol Sub-Setting Registers
*/
//02           ISO14443B TX options                           R/W
#define REG_14443B_TX_OPTIONS			0x02
//03           ISO 14443A high bit rate options               R/W
#define REG_14443A_OPTIONS				0x03
//04           TX timer setting, H-byte                       R/W
#define REG_TX_TIMER_H					0x04
//05           TX timer setting, L-byte                       R/W
#define REG_TX_TIMER_L					0x05
//06           TX pulse-length control                        R/W
#define REG_TX_PULSE_LENGTH				0x06
//07           RX no response wait                            R/W
#define REG_RX_RESPONSE_WAIT			0x07
//08           RX wait time                                   R/W
#define REG_RX_WAIT						0x08
//09           Modulator and SYS_CLK control                  R/W
#define REG_SIGNAL						0x09
//0A           RX special setting                             R/W
#define REG_RX_SPECIAL					0x0A
//0B           Regulator and I/O control                      R/W
#define REG_IO							0x0B
//16           Unused                                         NA
//17           Unused                                         NA
//18           Unused                                         NA
//19           Unused                                         NA
/*
Status Registers
*/
//0C           IRQ status                                     R
#define REG_IRQ							0x0C
//0D           Collision position and interrupt mask register R/W
#define REG_COLLISION_POS_IRQ_MASK		0x0D
//0E           Collision position                             R
#define REG_COLLISION_POS				0x0E
//0F           RSSI levels and oscillator status              R
#define REG_RSSI_OSC					0x0F
/*
FIFO Registers
*/
//1C           FIFO status                                    R
#define REG_FIFO_STAT					0x1C
/*
B7 RFU  Set to LOW          Reserved for future use (RFU)
B6 Fhil FIFO level HIGH     Indicates that 9 bytes are already in the FIFO (for RX)
B5 Flol FIFO level LOW      Indicates that only 3 bytes are in the FIFO (for TX)
B4 Fove FIFO overflow error Too much data was written to the FIFO
*/
/*
Bits B0:B3 indicate how many bytes that are loaded in FIFO were not read
out yet (displays N – 1 number of bytes). If 8 bytes are in the FIFO, this
number is 7.
*/
/*
B3 Fb3  FIFO bytes fb[3]    
B2 Fb2  FIFO bytes fb[2]
B1 Fb1  FIFO bytes fb[1]
B0 Fb0  FIFO bytes fb[0]
*/

//1D           TX length byte1                                R/W
#define REG_TX_LENGTH1					0x1D
//1E           TX length byte2                                R/W
#define REG_TX_LENGTH2					0x1E
//1F           FIFO I/O register                              R/W
#define REG_FIFO						0x1F
/*
Misc
*/
//RAM is 7 bytes long (0x10 - 0x16)
#define REG_RAM_BASE					0x10

#endif

