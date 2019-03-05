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
#include "trustzone_veneer.h"
#include "sercom.h"

#define WRITE_BUFFER_LENGTH 80

int32_t __attribute__((cmse_nonsecure_entry)) nsc_SERCOM0_write(const char *const buf, const uint32_t length) {
	char writeBuf[WRITE_BUFFER_LENGTH] = "NONSEC: ";
	int writeIndex = 8;
		
	for (int readIndex = 0; readIndex < WRITE_BUFFER_LENGTH - 2 && readIndex < (int) length; readIndex++) {
		if(buf[readIndex] >= 0x00 && buf[readIndex] <= 0x1f) {
			continue;
		} else {
			writeBuf[writeIndex++] = buf[readIndex];
		}
	}
	
	writeBuf[writeIndex++] = '\r';
	writeBuf[writeIndex++] = '\n';
	writeBuf[writeIndex] = '\0';
	
	
	return SERCOM0_write(writeBuf, writeIndex);
}

int32_t __attribute__((cmse_nonsecure_entry)) nsc_SERCOM0_read(char *const buf, const uint32_t length) {
	return SERCOM0_read(buf, length);
}

int32_t __attribute__((cmse_nonsecure_entry)) nsc_SERCOM0_IsDataAvailable(void) {
	return SERCOM0_IsDataAvailable();
}
