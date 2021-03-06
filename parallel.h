/*
trf7960evm port
Original code Copyright (C) 2006-2007 Texas Instruments, Inc.
Modifications copyright 2011 John McMaster <JohnDMcMaster@gmail.com>
See COPYING for details
*/

#ifndef PARALLEL_H
#define PARALLEL_H
//-----------------------------------------------------------
//-----------------------------------------------------------


//#ifndef SPI_BITBANG
//#define SPI_BITBANG

//can't be greater than 256+13 	
//me: what can't...?
#include <msp430x23x0.h>
#include <stdio.h>
#include "hardware.h"
#include "globals.h"
#include "host.h"

//NFC and tag emulation settings-----------------------------
#define	NFC106		0x21
#define NFC212		0x22
#define NFC424		0x23

#define TAG14443A	0x24
#define TAG14443B	0x25
#define TAG15693	0x26
#define TAGFelica	0x27

#define TAG106		0x00
#define TAG212		0x21
#define TAG424		0x42
#define TAG848		0x63



//function definitions--------------------------------------
void STARTconditionReader(void);
void STOPconditionReader(void);
void SPIStartCondition(void);
void SPIStopCondition(void);
void InitialSettings(void);
void ReInitialize15693Settings(void);
void ReaderSet(char mode);
void TRFset(unsigned char *pbuf);
void PARset(void);
void STOPcondition(void);
void STOPcont(void);
void STARTcondition(void);
void WriteSingle(unsigned char *pbuf, unsigned char length);
void WriteCont(unsigned char *pbuf, unsigned char length);
void ReadSingle(unsigned char *pbuf, unsigned char length);
void ReadCont(unsigned char *pbuf, unsigned char length);
void DirectCommand(unsigned char *pbuf);
void RAWwrite(unsigned char *pbuf, unsigned char length);
void DirectMode(void);
void Response(unsigned char *pbuf, unsigned char length);
void InterruptHandlerReader(unsigned char *Register);
void InterruptHandlerNFC(unsigned char Register);
void InterruptHandlerNFCtarget(unsigned char Register);

interrupt (PORT2_VECTOR) Port_B(void);





//#endif      // SPI_BITBANG
#endif

