/*******************************************************************************
* File Name: Dip_3.h  
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

#if !defined(CY_PINS_Dip_3_ALIASES_H) /* Pins Dip_3_ALIASES_H */
#define CY_PINS_Dip_3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Dip_3_0			(Dip_3__0__PC)
#define Dip_3_0_PS		(Dip_3__0__PS)
#define Dip_3_0_PC		(Dip_3__0__PC)
#define Dip_3_0_DR		(Dip_3__0__DR)
#define Dip_3_0_SHIFT	(Dip_3__0__SHIFT)
#define Dip_3_0_INTR	((uint16)((uint16)0x0003u << (Dip_3__0__SHIFT*2u)))

#define Dip_3_INTR_ALL	 ((uint16)(Dip_3_0_INTR))


#endif /* End Pins Dip_3_ALIASES_H */


/* [] END OF FILE */
