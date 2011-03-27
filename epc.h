#ifndef EPC_H
#define EPC_H
//------------------------------------------------------//
//This file contains functions for testing the		//
//EPC RFID protocol for TRF796x reader chip.		//
//							//
//------------------------------------------------------//

#include <msp430x23x0.h>     	//can't be greater than 256+13 	
#include "parallel.h"
#include "SPI.h"
#include <stdio.h>
#include "anticollision.h"
#include "globals.h"


void BeginRound(unsigned char MaskLenght, unsigned char *Mask, unsigned char slotNo);
unsigned char RequestEPC(unsigned char *pbuf, unsigned char lenght);
void CSScommand(void);
#endif

