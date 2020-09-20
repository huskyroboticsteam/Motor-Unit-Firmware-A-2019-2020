/*******************************************************************************
* File Name: isr_period.h
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
#if !defined(CY_ISR_isr_period_H)
#define CY_ISR_isr_period_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void isr_period_Start(void);
void isr_period_StartEx(cyisraddress address);
void isr_period_Stop(void);

CY_ISR_PROTO(isr_period_Interrupt);

void isr_period_SetVector(cyisraddress address);
cyisraddress isr_period_GetVector(void);

void isr_period_SetPriority(uint8 priority);
uint8 isr_period_GetPriority(void);

void isr_period_Enable(void);
uint8 isr_period_GetState(void);
void isr_period_Disable(void);

void isr_period_SetPending(void);
void isr_period_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the isr_period ISR. */
#define isr_period_INTC_VECTOR            ((reg32 *) isr_period__INTC_VECT)

/* Address of the isr_period ISR priority. */
#define isr_period_INTC_PRIOR             ((reg32 *) isr_period__INTC_PRIOR_REG)

/* Priority of the isr_period interrupt. */
#define isr_period_INTC_PRIOR_NUMBER      isr_period__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable isr_period interrupt. */
#define isr_period_INTC_SET_EN            ((reg32 *) isr_period__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the isr_period interrupt. */
#define isr_period_INTC_CLR_EN            ((reg32 *) isr_period__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the isr_period interrupt state to pending. */
#define isr_period_INTC_SET_PD            ((reg32 *) isr_period__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the isr_period interrupt. */
#define isr_period_INTC_CLR_PD            ((reg32 *) isr_period__INTC_CLR_PD_REG)



#endif /* CY_ISR_isr_period_H */


/* [] END OF FILE */
