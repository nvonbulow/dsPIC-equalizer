
/**
  PTG Generated Driver API Source File 

  @Company
    Microchip Technology Inc.

  @File Name
    ptg.c

  @Summary
    This is the generated source file for the PTG driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This source file provides APIs for driver for PTG. 
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

#include "ptg.h"

/**
  Section: PTG Module APIs
*/

void PTG_Initialize (void)
{
    // PTGEN disabled; PTGSSEN disabled; PTGSWT disabled; PTGSIDL disabled; PTGTOGL disabled; PTGITM Continuous edge detect with Step delay executed on exit of command; PTGWTO disabled; PTGBUSY disabled; PTGIVIS disabled; PTGSTRT disabled; 
    PTGCST = (0x00 & 0x77FF);  // disabling PTGEN bit and PTGSTRT bit  
    // Clock Frequency = 80.0 MHz; PTGWDT disabled; PTGDIV 1; PTGCLK FOSC/2; PTGPWD 1; 
    PTGCON = 0x00;
    // PTGBTE13 disabled; PTGBTE14 disabled; PTGBTE11 disabled; PTGBTE12 disabled; PTGBTE15 disabled; PTGBTE1 disabled; PTGBTE0 disabled; PTGBTE3 disabled; PTGBTE2 disabled; PTGBTE5 disabled; PTGBTE4 disabled; PTGBTE10 disabled; PTGBTE7 disabled; PTGBTE6 disabled; PTGBTE9 disabled; PTGBTE8 disabled; 
    PTGBTE = 0x00;
    // PTGBTE19 disabled; PTGBTE24 disabled; PTGBTE25 disabled; PTGBTE22 disabled; PTGBTE23 disabled; PTGBTE17 disabled; PTGBTE28 disabled; PTGBTE18 disabled; PTGBTE29 disabled; PTGBTE26 disabled; PTGBTE16 disabled; PTGBTE27 disabled; PTGBTE20 disabled; PTGBTE31 disabled; PTGBTE21 disabled; PTGBTE30 disabled; 
    PTGBTEH = 0x00;
    // PTGHOLD 0; 
    PTGHOLD = 0x00;
    // Timer0 delay = 22.675 us; PTGT0LIM 1814; 
    PTGT0LIM = 0x716;    
    // Timer1 delay = 0.0 ns; PTGT1LIM 0; 
    PTGT1LIM = 0x00;    
    // Step delay = 0.0 ns; PTGSDLIM 0; 
    PTGSDLIM = 0x00;
    // PTGC0LIM 1024; 
    PTGC0LIM = 0x400;
    // PTGC1LIM 0; 
    PTGC1LIM = 0x00;
    // PTGADJ 0; 
    PTGADJ = 0x00;
    // PTGL0 0; 
    PTGL0 = 0x00;
    // PTGQPTR 0; 
    PTGQPTR = 0x00;

  /** 
   Step Commands 
  */

    
    PTG_STEP0 = PTGJMPC0 | 0x4;     // Jump to STEP4
    PTG_STEP1 = PTGIRQ | 0x0;     // Generate PTG IRQ 0
    PTG_STEP2 = PTGCTRL | 0xb;     // Wait for the software trigger (positive edge, PTGSWT = 0 to 1)
    PTG_STEP3 = PTGJMP | 0x0;     // Jump to STEP0
    PTG_STEP4 = PTGCTRL | 0x8;     // Wait for PTG Timer0 to match PTGT0LIM
    PTG_STEP5 = PTGTRIG | 0xc;     // Trigger for ADC Sample Trigger
    PTG_STEP6 = PTGWHI | 0xd;     // Trigger Input ADC Done Group Interrupt
    PTG_STEP7 = PTGJMP | 0x0;     // Jump to STEP0


    //Clear PTG0 interrupt flag  
    IFS5bits.PTG0IF = false;
    //Enable PTG0 interrupt
    IEC5bits.PTG0IE = true;

}

void PTG_Enable (void)
{
    PTGCSTbits.PTGEN = 1;
}

void PTG_StartStepSequence (void)
{
    PTGCSTbits.PTGSTRT = 1;
}

void PTG_SoftwareTriggerSet (void)
{
    PTGCSTbits.PTGSWT = 1;    
}

bool PTG_WatchdogTimeoutStatusGet (void)
{
    return( PTGCSTbits.PTGWTO);
}

void PTG_StopStepSequence (void)
{
    PTGCSTbits.PTGSTRT = 0;
}   

void PTG_Disable (void)
{
    PTGCSTbits.PTGEN = 0;
}


void __attribute__ ((weak)) PTG_Trigger0_CallBack(void)
{
    // Add your custom callback code here
}

void __attribute__ ( ( interrupt, no_auto_psv, context ) ) _ISR _PTG0Interrupt( void )
{
	// PTG callback function for Trigger0
	PTG_Trigger0_CallBack();
	
    /* TODO : Add interrupt handling code */
    IFS5bits.PTG0IF = false;
}

void __attribute__ ((weak)) PTG_Trigger1_CallBack(void)
{
    // Add your custom callback code here
}

void PTG_Trigger1_Tasks ( void )
{
	if(IFS5bits.PTG1IF)
	{
		// PTG Trigger1 callback function 
		PTG_Trigger1_CallBack();
		
		// clear the PTG Trigger1 interrupt flag
		IFS5bits.PTG1IF = 0;
	}
}

void __attribute__ ((weak)) PTG_Trigger2_CallBack(void)
{
    // Add your custom callback code here
}

void PTG_Trigger2_Tasks ( void )
{
	if(IFS5bits.PTG2IF)
	{
		// PTG Trigger2 callback function 
		PTG_Trigger2_CallBack();
		
		// clear the PTG Trigger2 interrupt flag
		IFS5bits.PTG2IF = 0;
	}
}

void __attribute__ ((weak)) PTG_Trigger3_CallBack(void)
{
    // Add your custom callback code here
}

void PTG_Trigger3_Tasks ( void )
{
	if(IFS5bits.PTG3IF)
	{
		// PTG Trigger3 callback function 
		PTG_Trigger3_CallBack();
		
		// clear the PTG Trigger3 interrupt flag
		IFS5bits.PTG3IF = 0;
	}
}

void __attribute__ ((weak)) PTG_WatchDogTimer_CallBack(void)
{
    // Add your custom callback code here
}

void PTG_WatchDogTimer_Tasks ( void )
{
	if(IFS5bits.PTGWDTIF)
	{
		// PTG WatchDogTimer callback function 
		PTG_WatchDogTimer_CallBack();
		
		// clear the PTG WatchDogTimer interrupt flag
		IFS5bits.PTGWDTIF = 0;
	}
}
