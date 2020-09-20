/*******************************************************************************
* File Name: FAULT.h  
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

#if !defined(CY_PINS_FAULT_ALIASES_H) /* Pins FAULT_ALIASES_H */
#define CY_PINS_FAULT_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define FAULT_0			(FAULT__0__PC)
#define FAULT_0_PS		(FAULT__0__PS)
#define FAULT_0_PC		(FAULT__0__PC)
#define FAULT_0_DR		(FAULT__0__DR)
#define FAULT_0_SHIFT	(FAULT__0__SHIFT)
#define FAULT_0_INTR	((uint16)((uint16)0x0003u << (FAULT__0__SHIFT*2u)))

#define FAULT_INTR_ALL	 ((uint16)(FAULT_0_INTR))


#endif /* End Pins FAULT_ALIASES_H */


/* [] END OF FILE */
