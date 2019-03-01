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
#include "trustzone/nonsecure_call.h"
#include "my_init/nvmctrl.h"
#include "my_init/nvic.h"
#include "my_init/pm.h"
#include "my_init/port.h"
#include "my_init/oscctrl.h"
#include "my_init/sercom.h"
#include "utils/print.h"


int main(void) {

	PM_init();
	NVMCTRL_init();
	OSCCTRL_init();
	
	clock_output_pa22(GCLK_GENCTRL_SRC_FDPLL96M);
	//clock_output_pa22(GCLK_GENCTRL_SRC_OSC16M);
	//clock_output_pa22(GCLK_GENCTRL_SRC_OSCULP32K);
	
	NVIC_init();
	PORT_init();
	SERCOM0_init();
	print_init();
	
	secure_printf("Hello Metal World!\r\n");
	
	NonSecureCall();

    while (1) {
    }
}

void HardFault_Handler(void) {
	while(1);
}

