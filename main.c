/*
trf7960evm port
Original code Copyright (C) 2006-2007 Texas Instruments, Inc.
Modifications copyright 2011 John McMaster <JohnDMcMaster@gmail.com>
See COPYING for details
*/

//--------------------------------------
//Program with hardware USART and
//paralel communication interface
//with TIR reader chip.
//

//PORT 4.0-4.7 - (IO0-IO7) for parallel interface with reader chip
//PORT3.4 - PORT3.5 - USCI_A0 ---> USB/UART control signals
//PORT2.1 - IRQ
//PORT3.3 - DATA_CLK
//PORT1.7 - PORT1.3 - signaling LEDs
//--------------------------------------

#define DBG		0

//Processor specific definitions
#include <msp430x23x0.h>
#include <stdlib.h>		
#include <stdio.h>
#include "hardware.h"
#include "parallel.h"
#include "anticollision.h"
#include "globals.h"
#include "tiris.h"
#include "14443.h"
#include "host.h"
#include "epc.h"
#include "automatic.h"

// =======================================================================

char rxdata;			//RS232 RX data byte
unsigned char buf[BUF_LENGTH];
signed char RXTXstate;	//used for transmit recieve byte count
unsigned char flags;	//stores the mask value (used in anticollision)
unsigned char RXErrorFlag;
unsigned char RXflag;		//indicates that data is in buffer
unsigned char i_reg;	//interrupt register
unsigned char counter;
unsigned char CollPoss;

// =========================================================================
// Main function with init and an endless loop
//
//
int main(void) {
	// initialize peripherals
	WDTCTL = WDTPW + WDTHOLD;             // Stop WDT

	UARTset();


	EnableSet;
	TRFDisable;
	delay_ms(1);
	TRFEnable;
	delay_ms(1);

	//Add logic for SPI/parallel selection.
	if (SPIMODE)
	{ 
		//Set Port Functions for Serial Mode
		EnableSet;
		irqPINset;
		irqEDGEset;			/* rising edge interrupt */

		LEDallOFF;
		LEDportSET;
	}
	else
		PARset();     //Set Port Functions for Parallel Mode


	/* Use the DCO to program the SPI first*/
	if (SPIMODE)
	{
#ifndef SPI_BITBANG
		USARTset();       //Set the USART */
#else
		SlaveSelectPortSet  // P3.0 - Slave Select
		SlaveSelectHIGH     // Slave Select - inactive ( high)
		SIMOSet
		clkPOUTset;
#endif
	}


	//test code
	TRFDisable;
	TRFEnable;
	delay_ms(1);
	//end test code

	InitialSettings();                  // Set MCU Clock Frequency to 13.56 MHz and OOK Modulation


	/*Now switch from DCO to external 13.56 MHz clock*/

	OSCsel(0x00);       //set the oscilator
	delay_ms(10);

	/*Re-configure the USART with this external clock*/

	if (SPIMODE)
	{
#ifndef SPI_BITBANG
		USARTEXTCLKset();       //Set the USART */
#endif
	}

	EnableInterrupts;                    // General enable interrupts


	delay_ms(10);
	LEDpowerON;


	OOKdirIN;			//set OOK port tristate
	ENABLE = 1;

	POLLING = 1;
	FindTags(0x00);
	return 0;
}


// === end of main =====================================================

