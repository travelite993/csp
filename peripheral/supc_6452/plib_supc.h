/*******************************************************************************
  Supply Controller (SUPC) Peripheral Library (PLIB) Interface Header File

  Company
    Microchip Technology Inc.

  File Name
    plib_supc.h

  Summary
    SUPC peripheral library interface.

  Description
    This file defines the interface to the SUPC peripheral library.  This 
    library provides access to and control of the associated Reset Controller.

  Remarks:
    This header is for documentation only. The actual SUPC headers will be
    generated as required by the MCC.

*******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2017 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third-party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
*******************************************************************************/
// DOM-IGNORE-END

#ifndef PLIB_SUPCx_H    // Guards against multiple inclusion
#define PLIB_SUPCx_H

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

/* This section lists the other files that are included in this file.
*/

#include <stdbool.h>

// DOM-IGNORE-BEGIN
#ifdef __cplusplus // Provide C++ Compatibility

    extern "C" {

#endif
// DOM-IGNORE-END

// *****************************************************************************
// *****************************************************************************
// Section: Data Types
// *****************************************************************************
// *****************************************************************************

typedef void (*SUPC_CALLBACK) (uintptr_t context);

// *****************************************************************************
// *****************************************************************************
// Section: Interface Routines
// *****************************************************************************
// *****************************************************************************

/* Function:
    void SUPCx_Initialize (void);

  Summary:
    Initializes SUPC module with the user configuration.

  Description:
    This function initializes SUPC module with the values configured in MCC GUI.

  Precondition:
    MCC GUI should be configured with the right values.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
        SUPC0_Initialize();
    </code>

  Remarks:
    This function must be called before any other SUUPC function is called.                                           

*/

void SUPCx_Initialize (void);


// *****************************************************************************
/* Function:
	void SUPCx_EnterSleepMode( void );

  Summary:
	Puts the device in Sleep mode 
   
  Description:
    This functions is used to put the device in sleep mode to optimize power consumption. 
    In this mode, only the core clock is stopped and peripheral clock remains enabled.	
    
	Processor wake-up is triggered by an interrupt.
	
  Precondition:
    None

  Parameters:
    None

  Returns:
   None.

  Example:
  	<code>
     
    SUPC0_EnterSleepMode();
	
    </code>

  Remarks:
    None.

*/

void SUPCx_EnterSleepMode( void );


// *****************************************************************************
/* Function:
	void SUPCx_EnterWaitMode(WAITMODE_FLASH_STATE flash_lpm, WAITMODE_WKUP_SOURCE source);

  Summary:
	Puts the device in Wait mode 
   
  Description:
    The purpose of Wait mode is to achieve very low power consumption while maintaining the whole device in a
    powered state for a startup time of less than 10 μs.
    
	In Wait mode, the clocks of the core, peripherals and memories are stopped. However, the core, peripherals and
    memories power supplies are still powered. The Flah

	When entering Wait mode, the embedded Flash can be placed in one of the low-power modes (Deep-power-down
	or Standby mode). 
	
	Exit from Backup mode occurs as a result of one of the following enabled wake-up events:
	 WKUP0–13 pins 
	 RTC alarm
	 RTT alarm
	 USB
	 GMAC	
	
	A fast startup is enabled upon the detection of a programmed level on one of the 14 wake-up inputs (WKUP) or
	upon an active alarm from the RTC, RTT and USB Controller. The polarity of the 14 wake-up inputs is
	programmable by writing the PMC Fast Startup Polarity register (PMC_FSPR)
	
  Precondition:
    The peripherals (RTT, RTC etc) must be configured to generate wake-up event.

  Parameters:
    None

  Returns:
   None.

  Example:
  	<code>
     
    SUPC0_EnterWaitMode(PMC_FSMR_FLPM_FLASH_DEEP_POWERDOWN, WAITMODE_WKUP_RTC);
	
    </code>

  Remarks:
    None.

*/

void SUPCx_EnterWaitMode(WAITMODE_FLASH_STATE flash_lpm, WAITMODE_WKUP_SOURCE source);

// *****************************************************************************
/* Function:
	void SUPCx_EnterBackupMode(void);

  Summary:
	Puts the device in Backup mode 
   
  Description:
	The purpose of Backup mode is to achieve the lowest power consumption possible in a system which is
	performing periodic wake-ups to perform tasks but not requiring fast startup time..
    
	The Supply Controller, zero-power power-on reset, RTT, RTC, backup SRAM, backup registers and 32 kHz
	oscillator (RC or crystal oscillator selected by software in the Supply Controller) are running. The regulator and the
	core supply are off.

	Exit from Backup mode occurs as a result of one of the following enabled wake-up events and it causes device reset:
	 WKUP0–13 pins (level transition, configurable debouncing)
	 Supply Monitor alarm
	 RTC alarm
	 RTT alarm

  Precondition:
    The peripherals (Supply Monitor, RTT, RTC etc) must be configured to generate wake-up event.

  Parameters:
    None

  Returns:
   None.

  Example:
  	<code>
     
    SUPC0_EnterBackupMode();
	
    </code>

  Remarks:
    None.

*/

void SUPCx_EnterBackupMode(void);

// *****************************************************************************
/* Function:
    void SUPCx_CallbackRegister (SUPC_CALLBACK callback, uintptr_t context)

  Summary:
    Allows a client to identify a callback function.

  Description:
    None
    
  Precondition:
    Function SUPCx_Initialize should have been called before calling this
    function.

  Parameters:
    callback - Pointer to the callback function.
    context  - The value of parameter will be passed back to the client
               unchanged, when the callback function is called.  It can be used 
               to identify any client specific data object that identifies the
               instance of the client module (for example, it may be a pointer
               to the client module's state structure).   

  Returns:
   None.

  Example:
    <code>
    MY_APP_OBJ myAppObj;
    void APP_SUPC_CallbackFunction (uintptr_t context)
    {  
        // The context was set to an application specific object.
        // It is now retrievable easily in the event handler.
           MY_APP_OBJ myAppObj = (MY_APP_OBJ *) context;
        //Application related tasks
    }
                  
    SUPC0_CallbackRegister (APP_SUPC_CallbackFunction, (uintptr_t)&myAppObj);
    </code>

  Remarks:
    None.

*/

void SUPCx_CallbackRegister (SUPC_CALLBACK callback, uintptr_t context);



// DOM-IGNORE-BEGIN
#ifdef __cplusplus  // Provide C++ Compatibility
    }
#endif
// DOM-IGNORE-END

#endif //PLIB_SUPCx_H

/**
 End of File
*/

