/*******************************************************************************
* File Name: Error.h  
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

#if !defined(CY_PINS_Error_ALIASES_H) /* Pins Error_ALIASES_H */
#define CY_PINS_Error_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Error_0			(Error__0__PC)
#define Error_0_PS		(Error__0__PS)
#define Error_0_PC		(Error__0__PC)
#define Error_0_DR		(Error__0__DR)
#define Error_0_SHIFT	(Error__0__SHIFT)
#define Error_0_INTR	((uint16)((uint16)0x0003u << (Error__0__SHIFT*2u)))

#define Error_INTR_ALL	 ((uint16)(Error_0_INTR))


#endif /* End Pins Error_ALIASES_H */


/* [] END OF FILE */
