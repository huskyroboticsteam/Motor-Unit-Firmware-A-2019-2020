/*******************************************************************************
* File Name: FAULT_MOTOR.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_FAULT_MOTOR_ALIASES_H) /* Pins FAULT_MOTOR_ALIASES_H */
#define CY_PINS_FAULT_MOTOR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FAULT_MOTOR_0			(FAULT_MOTOR__0__PC)
#define FAULT_MOTOR_0_PS		(FAULT_MOTOR__0__PS)
#define FAULT_MOTOR_0_PC		(FAULT_MOTOR__0__PC)
#define FAULT_MOTOR_0_DR		(FAULT_MOTOR__0__DR)
#define FAULT_MOTOR_0_SHIFT	(FAULT_MOTOR__0__SHIFT)
#define FAULT_MOTOR_0_INTR	((uint16)((uint16)0x0003u << (FAULT_MOTOR__0__SHIFT*2u)))

#define FAULT_MOTOR_INTR_ALL	 ((uint16)(FAULT_MOTOR_0_INTR))


#endif /* End Pins FAULT_MOTOR_ALIASES_H */


/* [] END OF FILE */
