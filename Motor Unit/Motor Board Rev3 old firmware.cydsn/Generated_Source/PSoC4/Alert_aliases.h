/*******************************************************************************
* File Name: Alert.h  
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

#if !defined(CY_PINS_Alert_ALIASES_H) /* Pins Alert_ALIASES_H */
#define CY_PINS_Alert_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Alert_0			(Alert__0__PC)
#define Alert_0_PS		(Alert__0__PS)
#define Alert_0_PC		(Alert__0__PC)
#define Alert_0_DR		(Alert__0__DR)
#define Alert_0_SHIFT	(Alert__0__SHIFT)
#define Alert_0_INTR	((uint16)((uint16)0x0003u << (Alert__0__SHIFT*2u)))

#define Alert_INTR_ALL	 ((uint16)(Alert_0_INTR))


#endif /* End Pins Alert_ALIASES_H */


/* [] END OF FILE */
