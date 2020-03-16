/*******************************************************************************
* File Name: CAN_isr.h
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
#if !defined(CY_ISR_CAN_isr_H)
#define CY_ISR_CAN_isr_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void CAN_isr_Start(void);
void CAN_isr_StartEx(cyisraddress address);
void CAN_isr_Stop(void);

CY_ISR_PROTO(CAN_isr_Interrupt);

void CAN_isr_SetVector(cyisraddress address);
cyisraddress CAN_isr_GetVector(void);

void CAN_isr_SetPriority(uint8 priority);
uint8 CAN_isr_GetPriority(void);

void CAN_isr_Enable(void);
uint8 CAN_isr_GetState(void);
void CAN_isr_Disable(void);

void CAN_isr_SetPending(void);
void CAN_isr_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the CAN_isr ISR. */
#define CAN_isr_INTC_VECTOR            ((reg32 *) CAN_isr__INTC_VECT)

/* Address of the CAN_isr ISR priority. */
#define CAN_isr_INTC_PRIOR             ((reg32 *) CAN_isr__INTC_PRIOR_REG)

/* Priority of the CAN_isr interrupt. */
#define CAN_isr_INTC_PRIOR_NUMBER      CAN_isr__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable CAN_isr interrupt. */
#define CAN_isr_INTC_SET_EN            ((reg32 *) CAN_isr__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the CAN_isr interrupt. */
#define CAN_isr_INTC_CLR_EN            ((reg32 *) CAN_isr__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the CAN_isr interrupt state to pending. */
#define CAN_isr_INTC_SET_PD            ((reg32 *) CAN_isr__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the CAN_isr interrupt. */
#define CAN_isr_INTC_CLR_PD            ((reg32 *) CAN_isr__INTC_CLR_PD_REG)



#endif /* CY_ISR_CAN_isr_H */


/* [] END OF FILE */
