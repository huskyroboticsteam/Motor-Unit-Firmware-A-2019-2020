/*******************************************************************************
* File Name: SLP.h  
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

#if !defined(CY_PINS_SLP_ALIASES_H) /* Pins SLP_ALIASES_H */
#define CY_PINS_SLP_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define SLP_0			(SLP__0__PC)
#define SLP_0_PS		(SLP__0__PS)
#define SLP_0_PC		(SLP__0__PC)
#define SLP_0_DR		(SLP__0__DR)
#define SLP_0_SHIFT	(SLP__0__SHIFT)
#define SLP_0_INTR	((uint16)((uint16)0x0003u << (SLP__0__SHIFT*2u)))

#define SLP_INTR_ALL	 ((uint16)(SLP_0_INTR))


#endif /* End Pins SLP_ALIASES_H */


/* [] END OF FILE */
