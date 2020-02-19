/**
  ADC1 Generated Driver File

  @Company
    Microchip Technology Inc.

  @File Name
    adc1.c

  @Summary
    This is the generated driver implementation file for the ADC1 driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for ADC1.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK256MP202      
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB 	          :  MPLAB X v5.30
*/

/*
    (c) 2019 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

/**
  Section: Included Files
*/

#include "adc1.h"

/**
 Section: File specific functions
*/

static void (*ADC1_CommonDefaultInterruptHandler)(void);
static void (*ADC1_LCD_YNDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_LCD_XMDefaultInterruptHandler)(uint16_t adcVal);
static void (*ADC1_Audio_ADCDefaultInterruptHandler)(uint16_t adcVal);

/**
  Section: Driver Interface
*/

void ADC1_Initialize (void)
{
    // ADSIDL disabled; ADON enabled; 
    ADCON1L = (0x8000 & 0x7FFF); //Disabling ADON bit
    // FORM Integer; SHRRES 12-bit resolution; 
    ADCON1H = 0x60;
    // PTGEN disabled; SHRADCS 2; REFCIE disabled; SHREISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; REFERCIE disabled; EIEN disabled; 
    ADCON2L = 0x00;
    // SHRSAMC 0; 
    ADCON2H = 0x00;
    // SWCTRG disabled; SHRSAMP disabled; SUSPEND disabled; SWLCTRG disabled; SUSPCIE disabled; CNVCHSEL AN0; REFSEL disabled; 
    ADCON3L = 0x00;
    // SHREN enabled; C1EN disabled; C0EN enabled; CLKDIV 1; CLKSEL FOSC/2; 
    ADCON3H = (0x81 & 0xFF00); //Disabling C0EN, C1EN, C2EN, C3EN and SHREN bits
    // SAMC0EN disabled; SAMC1EN disabled; 
    ADCON4L = 0x00;
    // C0CHS AN0; C1CHS AN1; 
    ADCON4H = 0x00;
    // SIGN0 disabled; SIGN4 disabled; SIGN3 disabled; SIGN2 disabled; SIGN1 disabled; SIGN7 disabled; SIGN6 disabled; DIFF0 disabled; SIGN5 disabled; DIFF1 disabled; DIFF2 disabled; DIFF3 disabled; DIFF4 disabled; DIFF5 disabled; DIFF6 disabled; DIFF7 disabled; 
    ADMOD0L = 0x00;
    // DIFF8 disabled; DIFF9 disabled; SIGN10 disabled; SIGN11 disabled; SIGN8 disabled; DIFF11 disabled; DIFF10 disabled; SIGN9 disabled; 
    ADMOD0H = 0x00;
    // DIFF25 disabled; SIGN25 disabled; 
    ADMOD1H = 0x00;
    // IE1 disabled; IE0 enabled; IE3 disabled; IE2 disabled; IE5 disabled; IE4 disabled; IE10 disabled; IE7 enabled; IE6 disabled; IE9 disabled; IE8 enabled; IE11 disabled; 
    ADIEL = 0x181;
    // IE24 disabled; IE25 disabled; 
    ADIEH = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP0ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP1ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP2ENL = 0x00;
    // CMPEN6 disabled; CMPEN10 disabled; CMPEN5 disabled; CMPEN11 disabled; CMPEN4 disabled; CMPEN3 disabled; CMPEN2 disabled; CMPEN1 disabled; CMPEN0 disabled; CMPEN9 disabled; CMPEN8 disabled; CMPEN7 disabled; 
    ADCMP3ENL = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP0ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP1ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP2ENH = 0x00;
    // CMPEN25 disabled; CMPEN24 disabled; 
    ADCMP3ENH = 0x00;
    // CMPLO 0; 
    ADCMP0LO = 0x00;
    // CMPLO 0; 
    ADCMP1LO = 0x00;
    // CMPLO 0; 
    ADCMP2LO = 0x00;
    // CMPLO 0; 
    ADCMP3LO = 0x00;
    // CMPHI 0; 
    ADCMP0HI = 0x00;
    // CMPHI 0; 
    ADCMP1HI = 0x00;
    // CMPHI 0; 
    ADCMP2HI = 0x00;
    // CMPHI 0; 
    ADCMP3HI = 0x00;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL0CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL1CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL2CON = 0x400;
    // OVRSAM 4x; MODE Oversampling Mode; FLCHSEL AN0; IE disabled; FLEN disabled; 
    ADFL3CON = 0x400;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP0CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP1CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP2CON = 0x00;
    // HIHI disabled; LOLO disabled; HILO disabled; BTWN disabled; LOHI disabled; CMPEN disabled; IE disabled; 
    ADCMP3CON = 0x00;
    // LVLEN9 disabled; LVLEN8 disabled; LVLEN11 disabled; LVLEN7 disabled; LVLEN10 disabled; LVLEN6 disabled; LVLEN5 disabled; LVLEN4 disabled; LVLEN3 disabled; LVLEN2 disabled; LVLEN1 disabled; LVLEN0 disabled; 
    ADLVLTRGL = 0x00;
    // LVLEN24 disabled; LVLEN25 disabled; 
    ADLVLTRGH = 0x00;
    // SAMC 0; 
    ADCORE0L = 0x00;
    // SAMC 0; 
    ADCORE1L = 0x00;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE0H = 0x300;
    // RES 12-bit resolution; EISEL Early interrupt is generated 1 TADCORE clock prior to data being ready; ADCS 2; 
    ADCORE1H = 0x300;
    // EIEN9 disabled; EIEN7 disabled; EIEN8 disabled; EIEN5 disabled; EIEN6 disabled; EIEN3 disabled; EIEN4 disabled; EIEN1 disabled; EIEN2 disabled; EIEN0 disabled; EIEN11 disabled; EIEN10 disabled; 
    ADEIEL = 0x00;
    // EIEN25 disabled; EIEN24 disabled; 
    ADEIEH = 0x00;
    // C0CIE disabled; C1CIE disabled; SHRCIE disabled; WARMTIME 32768 Source Clock Periods; 
    ADCON5H = (0xF00 & 0xF0FF); //Disabling WARMTIME bit
	
    //Assign Default Callbacks
    ADC1_SetCommonInterruptHandler(&ADC1_CallBack);
    ADC1_SetLCD_YNInterruptHandler(&ADC1_LCD_YN_CallBack);
    ADC1_SetLCD_XMInterruptHandler(&ADC1_LCD_XM_CallBack);
    ADC1_SetAudio_ADCInterruptHandler(&ADC1_Audio_ADC_CallBack);
    
    // Clearing ADC1 interrupt.
    IFS5bits.ADCIF = 0;
    // Enabling ADC1 interrupt.
    IEC5bits.ADCIE = 1;
    // Clearing Audio_ADC interrupt flag.
    IFS5bits.ADCAN0IF = 0;
    // Enabling Audio_ADC interrupt.
    IEC5bits.ADCAN0IE = 1;

    // Setting WARMTIME bit
    ADCON5Hbits.WARMTIME = 0xF;
    // Enabling ADC Module
    ADCON1Lbits.ADON = 0x1;
    // Enabling Power for the Shared Core
    ADC1_SharedCorePowerEnable();
    // Enabling Power for Core0
    ADC1_Core0PowerEnable();

    //TRGSRC0 PTG; TRGSRC1 None; 
    ADTRIG0L = 0x1E;
    //TRGSRC3 None; TRGSRC2 None; 
    ADTRIG0H = 0x00;
    //TRGSRC4 None; TRGSRC5 None; 
    ADTRIG1L = 0x00;
    //TRGSRC6 None; TRGSRC7 Common Software Trigger; 
    ADTRIG1H = 0x100;
    //TRGSRC8 Common Software Trigger; TRGSRC9 None; 
    ADTRIG2L = 0x01;
    //TRGSRC11 None; TRGSRC10 None; 
    ADTRIG2H = 0x00;
    //TRGSRC24 None; TRGSRC25 None; 
    ADTRIG6L = 0x00;
}

void ADC1_Core0PowerEnable ( ) 
{
    ADCON5Lbits.C0PWR = 1; 
    while(ADCON5Lbits.C0RDY == 0);
    ADCON3Hbits.C0EN = 1;     
}

void ADC1_Core1PowerEnable ( ) 
{
    ADCON5Lbits.C1PWR = 1; 
    while(ADCON5Lbits.C1RDY == 0);
    ADCON3Hbits.C1EN = 1;     
}

void ADC1_SharedCorePowerEnable ( ) 
{
    ADCON5Lbits.SHRPWR = 1;   
    while(ADCON5Lbits.SHRRDY == 0);
    ADCON3Hbits.SHREN = 1;   
}


void __attribute__ ((weak)) ADC1_CallBack ( void )
{ 

}

void ADC1_SetCommonInterruptHandler(void* handler)
{
    ADC1_CommonDefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCInterrupt ( void )
{
    if(ADC1_CommonDefaultInterruptHandler) 
    { 
        ADC1_CommonDefaultInterruptHandler(); 
    }

    // clear the ADC1 interrupt flag
    IFS5bits.ADCIF = 0;
}

void __attribute__ ((weak)) ADC1_LCD_YN_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetLCD_YNInterruptHandler(void* handler)
{
    ADC1_LCD_YNDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_LCD_YN_Tasks ( void )
{
    uint16_t valLCD_YN;

    if(IFS6bits.ADCAN7IF)
    {
        //Read the ADC value from the ADCBUF
        valLCD_YN = ADCBUF7;

        if(ADC1_LCD_YNDefaultInterruptHandler) 
        { 
            ADC1_LCD_YNDefaultInterruptHandler(valLCD_YN); 
        }

        //clear the LCD_YN interrupt flag
        IFS6bits.ADCAN7IF = 0;
    }
}

void __attribute__ ((weak)) ADC1_LCD_XM_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetLCD_XMInterruptHandler(void* handler)
{
    ADC1_LCD_XMDefaultInterruptHandler = handler;
}

void __attribute__ ((weak)) ADC1_LCD_XM_Tasks ( void )
{
    uint16_t valLCD_XM;

    if(IFS6bits.ADCAN8IF)
    {
        //Read the ADC value from the ADCBUF
        valLCD_XM = ADCBUF8;

        if(ADC1_LCD_XMDefaultInterruptHandler) 
        { 
            ADC1_LCD_XMDefaultInterruptHandler(valLCD_XM); 
        }

        //clear the LCD_XM interrupt flag
        IFS6bits.ADCAN8IF = 0;
    }
}


void __attribute__ ((weak)) ADC1_Audio_ADC_CallBack( uint16_t adcVal )
{ 

}

void ADC1_SetAudio_ADCInterruptHandler(void* handler)
{
    ADC1_Audio_ADCDefaultInterruptHandler = handler;
}

void __attribute__ ( ( __interrupt__ , auto_psv, weak ) ) _ADCAN0Interrupt ( void )
{
    uint16_t valAudio_ADC;
    //Read the ADC value from the ADCBUF
    valAudio_ADC = ADCBUF0;

    if(ADC1_Audio_ADCDefaultInterruptHandler) 
    { 
        ADC1_Audio_ADCDefaultInterruptHandler(valAudio_ADC); 
    }

    //clear the Audio_ADC interrupt flag
    IFS5bits.ADCAN0IF = 0;
}



/**
  End of File
*/
