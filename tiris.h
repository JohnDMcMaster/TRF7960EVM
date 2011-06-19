#ifndef TIRIS_H
#define TIRIS_H
//------------------------------------------------------//
//This file contains the funcions needed for the	//
//Texas Instruments Tag-IT protocol.			//
//The functions in the HOST protocol are numbered	//
//from 0x20 upwards.					//
			//
//------------------------------------------------------//

#include <msp430x23x0.h>     	//can't be greater than 256+13 	
#include "parallel.h"
#include "SPI.h"
#include <stdio.h>
#include "anticollision.h"
#include "globals.h"


void TIInventoryRequest(unsigned char *mask, unsigned char length);
#endif

