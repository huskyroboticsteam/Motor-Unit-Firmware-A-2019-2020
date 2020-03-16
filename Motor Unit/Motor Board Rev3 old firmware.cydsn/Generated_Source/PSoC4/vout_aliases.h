/*******************************************************************************
* File Name: vout.h  
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

#if !defined(CY_PINS_vout_ALIASES_H) /* Pins vout_ALIASES_H */
#define CY_PINS_vout_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define vout_0			(vout__0__PC)
#define vout_0_PS		(vout__0__PS)
#define vout_0_PC		(vout__0__PC)
#define vout_0_DR		(vout__0__DR)
#define vout_0_SHIFT	(vout__0__SHIFT)
#define vout_0_INTR	((uint16)((uint16)0x0003u << (vout__0__SHIFT*2u)))

#define vout_INTR_ALL	 ((uint16)(vout_0_INTR))


#endif /* End Pins vout_ALIASES_H */


/* [] END OF FILE */
