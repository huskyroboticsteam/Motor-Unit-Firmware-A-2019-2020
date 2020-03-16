/*******************************************************************************
* File Name: Laser.h  
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

#if !defined(CY_PINS_Laser_ALIASES_H) /* Pins Laser_ALIASES_H */
#define CY_PINS_Laser_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define Laser_0			(Laser__0__PC)
#define Laser_0_PS		(Laser__0__PS)
#define Laser_0_PC		(Laser__0__PC)
#define Laser_0_DR		(Laser__0__DR)
#define Laser_0_SHIFT	(Laser__0__SHIFT)
#define Laser_0_INTR	((uint16)((uint16)0x0003u << (Laser__0__SHIFT*2u)))

#define Laser_INTR_ALL	 ((uint16)(Laser_0_INTR))


#endif /* End Pins Laser_ALIASES_H */


/* [] END OF FILE */
