/*******************************************************************************
* File Name: Spare5.h  
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

#if !defined(CY_PINS_Spare5_ALIASES_H) /* Pins Spare5_ALIASES_H */
#define CY_PINS_Spare5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Spare5_0			(Spare5__0__PC)
#define Spare5_0_PS		(Spare5__0__PS)
#define Spare5_0_PC		(Spare5__0__PC)
#define Spare5_0_DR		(Spare5__0__DR)
#define Spare5_0_SHIFT	(Spare5__0__SHIFT)
#define Spare5_0_INTR	((uint16)((uint16)0x0003u << (Spare5__0__SHIFT*2u)))

#define Spare5_INTR_ALL	 ((uint16)(Spare5_0_INTR))


#endif /* End Pins Spare5_ALIASES_H */


/* [] END OF FILE */
