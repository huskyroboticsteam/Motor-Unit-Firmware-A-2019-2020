/*******************************************************************************
* File Name: StripLights_cisr.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_StripLights_cisr_H)
#define CY_ISR_StripLights_cisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StripLights_cisr_Start(void);
void StripLights_cisr_StartEx(cyisraddress address);
void StripLights_cisr_Stop(void);

CY_ISR_PROTO(StripLights_cisr_Interrupt);

void StripLights_cisr_SetVector(cyisraddress address);
cyisraddress StripLights_cisr_GetVector(void);

void StripLights_cisr_SetPriority(uint8 priority);
uint8 StripLights_cisr_GetPriority(void);

void StripLights_cisr_Enable(void);
uint8 StripLights_cisr_GetState(void);
void StripLights_cisr_Disable(void);

void StripLights_cisr_SetPending(void);
void StripLights_cisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StripLights_cisr ISR. */
#define StripLights_cisr_INTC_VECTOR            ((reg32 *) StripLights_cisr__INTC_VECT)

/* Address of the StripLights_cisr ISR priority. */
#define StripLights_cisr_INTC_PRIOR             ((reg32 *) StripLights_cisr__INTC_PRIOR_REG)

/* Priority of the StripLights_cisr interrupt. */
#define StripLights_cisr_INTC_PRIOR_NUMBER      StripLights_cisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StripLights_cisr interrupt. */
#define StripLights_cisr_INTC_SET_EN            ((reg32 *) StripLights_cisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StripLights_cisr interrupt. */
#define StripLights_cisr_INTC_CLR_EN            ((reg32 *) StripLights_cisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StripLights_cisr interrupt state to pending. */
#define StripLights_cisr_INTC_SET_PD            ((reg32 *) StripLights_cisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StripLights_cisr interrupt. */
#define StripLights_cisr_INTC_CLR_PD            ((reg32 *) StripLights_cisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_StripLights_cisr_H */


/* [] END OF FILE */
