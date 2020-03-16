/*******************************************************************************
* File Name: StripLights_1_fisr.h
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
#if !defined(CY_ISR_StripLights_1_fisr_H)
#define CY_ISR_StripLights_1_fisr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void StripLights_1_fisr_Start(void);
void StripLights_1_fisr_StartEx(cyisraddress address);
void StripLights_1_fisr_Stop(void);

CY_ISR_PROTO(StripLights_1_fisr_Interrupt);

void StripLights_1_fisr_SetVector(cyisraddress address);
cyisraddress StripLights_1_fisr_GetVector(void);

void StripLights_1_fisr_SetPriority(uint8 priority);
uint8 StripLights_1_fisr_GetPriority(void);

void StripLights_1_fisr_Enable(void);
uint8 StripLights_1_fisr_GetState(void);
void StripLights_1_fisr_Disable(void);

void StripLights_1_fisr_SetPending(void);
void StripLights_1_fisr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the StripLights_1_fisr ISR. */
#define StripLights_1_fisr_INTC_VECTOR            ((reg32 *) StripLights_1_fisr__INTC_VECT)

/* Address of the StripLights_1_fisr ISR priority. */
#define StripLights_1_fisr_INTC_PRIOR             ((reg32 *) StripLights_1_fisr__INTC_PRIOR_REG)

/* Priority of the StripLights_1_fisr interrupt. */
#define StripLights_1_fisr_INTC_PRIOR_NUMBER      StripLights_1_fisr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable StripLights_1_fisr interrupt. */
#define StripLights_1_fisr_INTC_SET_EN            ((reg32 *) StripLights_1_fisr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the StripLights_1_fisr interrupt. */
#define StripLights_1_fisr_INTC_CLR_EN            ((reg32 *) StripLights_1_fisr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the StripLights_1_fisr interrupt state to pending. */
#define StripLights_1_fisr_INTC_SET_PD            ((reg32 *) StripLights_1_fisr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the StripLights_1_fisr interrupt. */
#define StripLights_1_fisr_INTC_CLR_PD            ((reg32 *) StripLights_1_fisr__INTC_CLR_PD_REG)



#endif /* CY_ISR_StripLights_1_fisr_H */


/* [] END OF FILE */
