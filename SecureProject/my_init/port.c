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
#include "port.h"

void PORT_init(void) {
	// configure one or more I/O pins as secured or non-secured.
	PORT_SEC->Group[0].NONSEC.reg = 0x00000000;
	
	// configure PA22 as clock output for GCLK2
	PORT_SEC->Group[0].DIRSET.reg = (1 << 22);
	PORT_SEC->Group[0].WRCONFIG.reg =
		  PORT_WRCONFIG_PMUX(MUX_PA22H_GCLK_IO2)
		| PORT_WRCONFIG_WRPMUX
		| PORT_WRCONFIG_PMUXEN
		| PORT_WRCONFIG_WRPINCFG
		| PORT_WRCONFIG_HWSEL
		| ((1 << 6) & 0xffff);	
	
	// configure PA25 as RX for SERCOM0
	PORT_SEC->Group[0].WRCONFIG.reg =
		  PORT_WRCONFIG_PMUX(MUX_PA25C_SERCOM0_PAD3)
		| PORT_WRCONFIG_WRPMUX
		| PORT_WRCONFIG_PMUXEN
		| PORT_WRCONFIG_WRPINCFG
		| PORT_WRCONFIG_HWSEL
		| ((1 << 9) & 0xffff);
		
	// configure PA24 as TX for SERCOM0
	PORT_SEC->Group[0].DIRSET.reg = (1 << 24);
	PORT_SEC->Group[0].WRCONFIG.reg =
		  PORT_WRCONFIG_PMUX(MUX_PA24C_SERCOM0_PAD2)
		| PORT_WRCONFIG_WRPMUX
		| PORT_WRCONFIG_PMUXEN
		| PORT_WRCONFIG_WRPINCFG
		| PORT_WRCONFIG_HWSEL
		| ((1 << 8) & 0xffff);
		
	// configure PA25 as WO1 for TC1
	PORT_SEC->Group[0].DIRSET.reg = (1 << 25);
	PORT_SEC->Group[0].WRCONFIG.reg =
		  PORT_WRCONFIG_PMUX(MUX_PA25E_TC1_WO1)
		| PORT_WRCONFIG_WRPMUX
		| PORT_WRCONFIG_PMUXEN
		| PORT_WRCONFIG_WRPINCFG
		| PORT_WRCONFIG_HWSEL
		| ((1 << 9) & 0xffff);
}