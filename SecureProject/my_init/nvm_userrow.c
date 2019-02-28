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

/* NVM User Row definitions
 * All values are factory settings, except AS, ANSC, DS, RS
 */

/* WORD0: BOD, Watchdog and Misc settings */
#define NVM_USER_WORD_0                                                        \
  (NVMCTRL_FUSES_SULCK(0x07) |                                                 \
   NVMCTRL_FUSES_NSULCK(0x07) |                                                \
   FUSES_BOD33USERLEVEL(0x06) |                                                \
   (0x00 << FUSES_BOD33_DIS_Pos) |                                             \
   FUSES_BOD33_ACTION(0x01) |                                                  \
   (0x00 << WDT_FUSES_ENABLE_Pos) |                                            \
   (0x00 << WDT_FUSES_ALWAYSON_Pos) |                                          \
   ((uint32_t)(0x0B) << WDT_FUSES_PER_Pos))

/* WORD1: Watchdog and Misc settings */
#define NVM_USER_WORD_1                                                        \
  (WDT_FUSES_WINDOW(0x0B) |										               \
   WDT_FUSES_EWOFFSET(0x0B) |                                                  \
   (0x00 << WDT_FUSES_ENABLE_Pos) |                                            \
   (0x00 << FUSES_BOD33_HYST_Pos) |                                            \
   (0x01 << FUSES_BOOTROM_RXN_Pos) |                                           \
   (0x01 << FUSES_BOOTROM_DXN_Pos))

/* WORD2: Memories Security Attribution: AS, ANSC, RS */
#define NVM_USER_WORD_2                                                        \
  ((0x80 << (64 % 32)) | (0x20 << (72 % 32)) |                                 \
   (0x08 << (80 % 32)) | (0x40 << (88 % 32)))
#pragma message "AS, ANSC, DS and RS must match the values in the secure linker file."

/* WORD3: User Row Write Enable */
#define NVM_USER_WORD_3 (0x01 << NVMCTRL_FUSES_URWEN_Pos)

/* WORD4: Peripherals Security Attribution Bridge A (NONSECA) */
#define NVM_USER_WORD_4                                                        \
  ((0x0 << PAC_NONSECA_PAC_Pos) |                                              \
   (0x0 << PAC_NONSECA_PM_Pos) |                                               \
   (0x0 << PAC_NONSECA_MCLK_Pos) |                                             \
   (0x0 << PAC_NONSECA_RSTC_Pos) |                                             \
   (0x0 << PAC_NONSECA_OSCCTRL_Pos) |                                          \
   (0x0 << PAC_NONSECA_OSC32KCTRL_Pos) |                                       \
   (0x0 << PAC_NONSECA_SUPC_Pos) |                                             \
   (0x0 << PAC_NONSECA_GCLK_Pos) |                                             \
   (0x0 << PAC_NONSECA_WDT_Pos) |                                              \
   (0x0 << PAC_NONSECA_RTC_Pos) |                                              \
   (0x0 << PAC_NONSECA_EIC_Pos) |                                              \
   (0x0 << PAC_NONSECA_FREQM_Pos) |                                            \
   (0x0 << PAC_NONSECA_PORT_Pos) |                                             \
   (0x0 << PAC_NONSECA_AC_Pos))

/* WORD5: Peripherals Security Attribution Bridge B (NONSECB) */
#define NVM_USER_WORD_5                                                        \
  ((0x0 << PAC_NONSECB_IDAU_Pos) |                                             \
   (0x0 << PAC_NONSECB_DSU_Pos) |                                              \
   (0x0 << PAC_NONSECB_NVMCTRL_Pos) |                                          \
   (0x0 << PAC_NONSECB_DMAC_Pos))

/* WORD6: Peripherals Security Attribution Bridge C (NONSECC) */
#define NVM_USER_WORD_6                                                        \
  ((0x0 << PAC_NONSECC_EVSYS_Pos) |                                            \
   (0x0 << PAC_NONSECC_SERCOM0_Pos) |                                          \
   (0x0 << PAC_NONSECC_SERCOM1_Pos) |                                          \
   (0x0 << PAC_NONSECC_SERCOM2_Pos) |                                          \
   (0x0 << PAC_NONSECC_TC0_Pos) |                                              \
   (0x0 << PAC_NONSECC_TC1_Pos) |                                              \
   (0x0 << PAC_NONSECC_TC2_Pos) |                                              \
   (0x0 << PAC_NONSECC_ADC_Pos) |                                              \
   (0x0 << PAC_NONSECC_DAC_Pos) |                                              \
   (0x0 << PAC_NONSECC_PTC_Pos) |                                              \
   (0x0 << PAC_NONSECC_TRNG_Pos) |                                             \
   (0x0 << PAC_NONSECC_CCL_Pos) |                                              \
   (0x0 << PAC_NONSECC_OPAMP_Pos) |                                            \
   (0x0 << PAC_NONSECC_TRAM_Pos))


#if defined(__GNUC__) /* GCC */
/* "userrowsec" section should be correctly defined in your linker file */
__attribute__((section(".userrowsec"))) const uint32_t nvm_user_row[] =
#elif defined(__ICCARM__) /* IAR EWARM */
/* "nvm_user_page" section should be correctly defined in your linker file */
__root const uint32_t nvm_user_row[] @ ".nvm_user_page" =
#else
#warning "This IDE can't support USER Row fuse programming."
#endif
    {NVM_USER_WORD_0, NVM_USER_WORD_1, NVM_USER_WORD_2, NVM_USER_WORD_3,
     NVM_USER_WORD_4, NVM_USER_WORD_5, NVM_USER_WORD_6};

