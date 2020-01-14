/*******************************************************************************
* File Name: Servo.h  
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

#if !defined(CY_PINS_Servo_ALIASES_H) /* Pins Servo_ALIASES_H */
#define CY_PINS_Servo_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Servo_0			(Servo__0__PC)
#define Servo_0_PS		(Servo__0__PS)
#define Servo_0_PC		(Servo__0__PC)
#define Servo_0_DR		(Servo__0__DR)
#define Servo_0_SHIFT	(Servo__0__SHIFT)
#define Servo_0_INTR	((uint16)((uint16)0x0003u << (Servo__0__SHIFT*2u)))

#define Servo_INTR_ALL	 ((uint16)(Servo_0_INTR))


#endif /* End Pins Servo_ALIASES_H */


/* [] END OF FILE */
