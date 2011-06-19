/*
trf7960evm
Original code Copyright (C) 2006-2007 Texas Instruments, Inc.
Modifications copyright 2011 John McMaster <JohnDMcMaster@gmail.com>
See COPYING for details
*/

//Global variables-------------------------------
//
//
//Can be used in all header and C files

#define BUF_LENGTH 300		//Number of characters in a frame
#define EnableInterrupts _EINT()

//From mifare code
#define __low_power_mode_off_on_exit() __bic_SR_register_on_exit(CPUOFF | SCG0 | SCG1 | OSCOFF)

extern char rxdata;			//RS232 RX data byte
extern unsigned char buf[BUF_LENGTH];
extern signed char RXTXstate;	//used for transmit recieve byte count
extern unsigned char flags;	//stores the mask value (used in anticollision)
extern unsigned char RXErrorFlag;
extern unsigned char RXflag;		//indicates that data is in buffer

extern unsigned char i_reg;	//interrupt register

extern unsigned char CollPoss;


extern unsigned char RXdone;
extern unsigned char ENABLE;
extern unsigned char POLLING;


//-----------------------------------------------
