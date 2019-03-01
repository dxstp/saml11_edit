// DOM-IGNORE-BEGIN
/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */
// DOM-IGNORE-END

#include "sam.h"
#include "oscctrl.h"

void OSCCTRL_init(void) {
	// set GCLK3 to OSC16M (4 MHz by default), divide by 40
	// 100 kHz (DPLL ref)
	GCLK->GENCTRL[3].reg =
		  GCLK_GENCTRL_SRC_OSC16M
		| GCLK_GENCTRL_DIV(40)
		| GCLK_GENCTRL_GENEN;
	while(GCLK->SYNCBUSY.bit.GENCTRL3);
	
	// set the PLL reference clock to GCLK
	OSCCTRL->DPLLCTRLB.reg = OSCCTRL_DPLLCTRLB_REFCLK_GCLK;
	
	// set the DPLL reference clock to GCLK3
	GCLK->PCHCTRL[0].reg =
		  GCLK_PCHCTRL_GEN_GCLK3
		| GCLK_PCHCTRL_CHEN;
			
	// set the DPLL to multiply input by 960 to get 96 MHz	
	OSCCTRL->DPLLRATIO.reg = OSCCTRL_DPLLRATIO_LDR(959);
	while(OSCCTRL->DPLLSYNCBUSY.bit.DPLLRATIO);
	
	// enable DPLL
	// 96 MHz
	OSCCTRL->DPLLCTRLA.bit.ONDEMAND = 0;
	OSCCTRL->DPLLCTRLA.bit.ENABLE = 1;
	while(OSCCTRL->DPLLSYNCBUSY.bit.ENABLE);
	while(OSCCTRL->DPLLSTATUS.bit.CLKRDY != 1);
	while(OSCCTRL->DPLLSTATUS.bit.LOCK != 1);
	
	// change source of GCLK0 to FDPLL96M, divided by 3
	// 32 MHz (CPU)
	GCLK->GENCTRL[0].reg =
		  GCLK_GENCTRL_SRC_FDPLL96M
		| GCLK_GENCTRL_DIV(3)
		| GCLK_GENCTRL_GENEN;
	while(GCLK->SYNCBUSY.bit.GENCTRL0);
	
	// change source of GCLK1 to FDPLL96M, divided by 2
	// 48 MHz (Peripherals)
	GCLK->GENCTRL[1].reg = 
		  GCLK_GENCTRL_SRC_FDPLL96M
		| GCLK_GENCTRL_DIV(2)
		| GCLK_GENCTRL_GENEN;
		while(GCLK->SYNCBUSY.bit.GENCTRL1);
}

void clock_output_pa22(uint32_t source) {
	uint32_t divider;
	
	if(source == GCLK_GENCTRL_SRC_OSCULP32K || source == GCLK_GENCTRL_SRC_XOSC32K) {
		divider = 1;
	} else {
		divider = 250;
	}
	
	GCLK->GENCTRL[2].reg =
		  GCLK_GENCTRL_GENEN
		| source
		| GCLK_GENCTRL_DIV(divider)
		| GCLK_GENCTRL_OE;
	while(GCLK->SYNCBUSY.bit.GENCTRL2);
	
}