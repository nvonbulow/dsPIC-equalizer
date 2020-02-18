/*
  PTG Generated Driver API Header File

  @Company
    Microchip Technology Inc.

  @File Name
    ptg.h

  @Summary
    This is the generated header file for the PTG driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description
    This header file provides APIs for driver for PTG.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.166.0
        Device            :  dsPIC33CK256MP202
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.41
        MPLAB             :  MPLAB X v5.30
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

#ifndef _PTG_H
#define _PTG_H

/**
  Section: Included Files
*/

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

/**
  Section: Helper Macros
*/ 


 /* PTGQUE0 */
#define PTG_STEP0 PTGQUE0bits.STEP0
#define PTG_STEP1 PTGQUE0bits.STEP1
 /* PTGQUE1 */
#define PTG_STEP2 PTGQUE1bits.STEP2
#define PTG_STEP3 PTGQUE1bits.STEP3
 /* PTGQUE2 */
#define PTG_STEP4 PTGQUE2bits.STEP4
#define PTG_STEP5 PTGQUE2bits.STEP5
 /* PTGQUE3 */
#define PTG_STEP6 PTGQUE3bits.STEP6
#define PTG_STEP7 PTGQUE3bits.STEP7
 /* PTGQUE4 */
#define PTG_STEP8 PTGQUE4bits.STEP8
#define PTG_STEP9 PTGQUE4bits.STEP9
 /* PTGQUE5 */
#define PTG_STEP10 PTGQUE5bits.STEP10
#define PTG_STEP11 PTGQUE5bits.STEP11
 /* PTGQUE6 */
#define PTG_STEP12 PTGQUE6bits.STEP12
#define PTG_STEP13 PTGQUE6bits.STEP13
 /* PTGQUE7 */
#define PTG_STEP14 PTGQUE7bits.STEP14
#define PTG_STEP15 PTGQUE7bits.STEP15
 /* PTGQUE8 */
#define PTG_STEP16 PTGQUE8bits.STEP16
#define PTG_STEP17 PTGQUE8bits.STEP17
 /* PTGQUE9 */
#define PTG_STEP18 PTGQUE9bits.STEP18
#define PTG_STEP19 PTGQUE9bits.STEP19
 /* PTGQUE10 */
#define PTG_STEP20 PTGQUE10bits.STEP20
#define PTG_STEP21 PTGQUE10bits.STEP21
 /* PTGQUE11 */
#define PTG_STEP22 PTGQUE11bits.STEP22
#define PTG_STEP23 PTGQUE11bits.STEP23
 /* PTGQUE12 */
#define PTG_STEP24 PTGQUE12bits.STEP24
#define PTG_STEP25 PTGQUE12bits.STEP25
 /* PTGQUE13 */
#define PTG_STEP26 PTGQUE13bits.STEP26
#define PTG_STEP27 PTGQUE13bits.STEP27
 /* PTGQUE14 */
#define PTG_STEP28 PTGQUE14bits.STEP28
#define PTG_STEP29 PTGQUE14bits.STEP29
 /* PTGQUE15 */
#define PTG_STEP30 PTGQUE15bits.STEP30
#define PTG_STEP31 PTGQUE15bits.STEP31



#define PTGCTRL  (0x0 << 4 )    //PTGCTRL command
#define PTGCOPY  (0x1 << 4 )    //PTGCOPY command
#define PTGADD  (0x1 << 4 )    //PTGADD command
#define PTGSTRB  (0x2 << 4 )    //PTGSTRB command
#define PTGWHI  (0x4 << 4 )    //PTGWHI command
#define PTGWLO  (0x5 << 4 )    //PTGWLO command
#define PTGIRQ  (0x7 << 4 )    //PTGIRQ command
#define PTGTRIG  (0x8 << 4 )    //PTGTRIG command
#define PTGJMP  (0xa << 4 )    //PTGJMP command
#define PTGJMPC0  (0xc << 4 )    //PTGJMPC0 command
#define PTGJMPC1  (0xe << 4 )    //PTGJMPC1 command


#ifdef __cplusplus  // Provide C++ Compatibility

    extern "C" {

#endif

/**
  Section: PTG Module APIs
*/

/**
  @Summary
    Initializes the PTG

  @Description
    This routine initializes the PTG.
    This routine must be called before any other PTG routine is called.
    This routine should only be called once during system initialization.
    This routine does not enable PTG module and start the step sequence. 
    Functions PTG_Enable() and PTG_StartStepSequence() need to be called for
    enabling PTG module and for starting step sequence execution, respectively.
    
  @Preconditions
    None

  @Param
    None

  @Returns
    None

  @Example
    <code>
    void main(void)
    {
    // initialize the device
    
    SYSTEM_Initialize();

    PTG_Enable();
    PTG_StartStepSequence();

      while (1)
      {      
          PTG_SoftwareTriggerSet();  
          bool wdtBit = PTG_WatchdogTimeoutStatusGet();
              if(wdtBit){          
                 PTG_StopStepSequence();
                 PTG_Disable();
                }
      }
    }
    </code> 
*/
void PTG_Initialize(void);

/**
  @Summary
    Enables the PTG module.

  @Description
    This routine enables the PTG module.
  
  @Preconditions
    PTG_Initializer function should have been called 
    before calling this function.
  
  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

void PTG_Enable (void);

/**
  @Summary
    Start the step sequence execution.

  @Description
    This routine starts the step sequence execution.

  
  @Preconditions
    PTG_Initializer and PTG_Enable functions should have been called 
    before calling this function.

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

void PTG_StartStepSequence (void);

/**
  @Summary
    Software trigger for PTG module

  @Description
    This routine provides a software trigger for PTG module
  
  @Preconditions
    None. 

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

void PTG_SoftwareTriggerSet (void);

/**
  @Summary
    Status of PTG watchdog time out bit.

  @Description
    This routine returns the status of PTG watchdog time out bit.
    
  @Preconditions
    None.

  @Param
    None.

  @Returns
    Returns the status of PTG watchdog time out bit.
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

bool PTG_WatchdogTimeoutStatusGet (void);

/**
  @Summary
    Stops the step sequence execution.

  @Description
    This routine stops the step sequence execution.

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

void PTG_StopStepSequence (void);

/**
  @Summary
   Disable the PTG module. 

  @Description
   This routine disables the PTG module. 

  @Preconditions
    None.

  @Param
    None.

  @Returns
    None
 
  @Example 
    Refer to the example of PTG_Initialize();
*/

void PTG_Disable (void);

/**
  @Summary
    Callback for PTG Trigger0.

  @Description
    This routine is callback for PTG Trigger0

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to PTG_Initialize(); for an example
*/
void PTG_Trigger0_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PTG_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to PTG_Initialize(); for an example
    
*/
void PTG_Trigger0_Tasks(void);
/**
  @Summary
    Callback for PTG Trigger1.

  @Description
    This routine is callback for PTG Trigger1

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to PTG_Initialize(); for an example
*/
void PTG_Trigger1_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PTG_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to PTG_Initialize(); for an example
    
*/
void PTG_Trigger1_Tasks(void);
/**
  @Summary
    Callback for PTG Trigger2.

  @Description
    This routine is callback for PTG Trigger2

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to PTG_Initialize(); for an example
*/
void PTG_Trigger2_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PTG_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to PTG_Initialize(); for an example
    
*/
void PTG_Trigger2_Tasks(void);
/**
  @Summary
    Callback for PTG Trigger3.

  @Description
    This routine is callback for PTG Trigger3

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to PTG_Initialize(); for an example
*/
void PTG_Trigger3_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PTG_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to PTG_Initialize(); for an example
    
*/
void PTG_Trigger3_Tasks(void);
/**
  @Summary
    Callback for PTG WatchDogTimer.

  @Description
    This routine is callback for PTG WatchDogTimer

  @Param
    None.

  @Returns
    None
 
  @Example 
	Refer to PTG_Initialize(); for an example
*/
void PTG_WatchDogTimer_CallBack(void);

/**
  @Summary
    Polled implementation

  @Description
    This routine is used to implement the tasks for polled implementations.
  
  @Preconditions
    PTG_Initialize() function should have been 
    called before calling this function.
 
  @Returns 
    None
 
  @Param
    None
 
  @Example
    Refer to PTG_Initialize(); for an example
    
*/
void PTG_WatchDogTimer_Tasks(void);

#ifdef __cplusplus  // Provide C++ Compatibility

    }

#endif

#endif //_PTG_H
    
/**
 End of File
*/
