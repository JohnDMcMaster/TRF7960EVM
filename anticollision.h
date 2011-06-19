#ifndef ANTICOLLISION_H
#define ANTICOLLISION_H
//---------------------------------
//Functions for anticollision------
//---------------------------------

#include <msp430x23x0.h>     	//can't be greater than 256+13 	
#include <stdio.h>
#include "parallel.h"
#include "SPI.h"
#include "globals.h"


void EnableSlotCounter(void);
void DisableSlotCounter(void);
void InventoryRequest(unsigned char *mask, unsigned char length);
unsigned char RequestCommand(unsigned char *pbuf, unsigned char length, unsigned char brokenBits, char noCRC);

#endif

