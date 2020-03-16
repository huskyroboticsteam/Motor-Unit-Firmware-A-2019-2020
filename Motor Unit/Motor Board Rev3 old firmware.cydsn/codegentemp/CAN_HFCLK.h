/*******************************************************************************
* File Name: CAN_HFCLK.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_CAN_HFCLK_H)
#define CY_CLOCK_CAN_HFCLK_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void CAN_HFCLK_StartEx(uint32 alignClkDiv);
#define CAN_HFCLK_Start() \
    CAN_HFCLK_StartEx(CAN_HFCLK__PA_DIV_ID)

#else

void CAN_HFCLK_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void CAN_HFCLK_Stop(void);

void CAN_HFCLK_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 CAN_HFCLK_GetDividerRegister(void);
uint8  CAN_HFCLK_GetFractionalDividerRegister(void);

#define CAN_HFCLK_Enable()                         CAN_HFCLK_Start()
#define CAN_HFCLK_Disable()                        CAN_HFCLK_Stop()
#define CAN_HFCLK_SetDividerRegister(clkDivider, reset)  \
    CAN_HFCLK_SetFractionalDividerRegister((clkDivider), 0u)
#define CAN_HFCLK_SetDivider(clkDivider)           CAN_HFCLK_SetDividerRegister((clkDivider), 1u)
#define CAN_HFCLK_SetDividerValue(clkDivider)      CAN_HFCLK_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define CAN_HFCLK_DIV_ID     CAN_HFCLK__DIV_ID

#define CAN_HFCLK_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define CAN_HFCLK_CTRL_REG   (*(reg32 *)CAN_HFCLK__CTRL_REGISTER)
#define CAN_HFCLK_DIV_REG    (*(reg32 *)CAN_HFCLK__DIV_REGISTER)

#define CAN_HFCLK_CMD_DIV_SHIFT          (0u)
#define CAN_HFCLK_CMD_PA_DIV_SHIFT       (8u)
#define CAN_HFCLK_CMD_DISABLE_SHIFT      (30u)
#define CAN_HFCLK_CMD_ENABLE_SHIFT       (31u)

#define CAN_HFCLK_CMD_DISABLE_MASK       ((uint32)((uint32)1u << CAN_HFCLK_CMD_DISABLE_SHIFT))
#define CAN_HFCLK_CMD_ENABLE_MASK        ((uint32)((uint32)1u << CAN_HFCLK_CMD_ENABLE_SHIFT))

#define CAN_HFCLK_DIV_FRAC_MASK  (0x000000F8u)
#define CAN_HFCLK_DIV_FRAC_SHIFT (3u)
#define CAN_HFCLK_DIV_INT_MASK   (0xFFFFFF00u)
#define CAN_HFCLK_DIV_INT_SHIFT  (8u)

#else 

#define CAN_HFCLK_DIV_REG        (*(reg32 *)CAN_HFCLK__REGISTER)
#define CAN_HFCLK_ENABLE_REG     CAN_HFCLK_DIV_REG
#define CAN_HFCLK_DIV_FRAC_MASK  CAN_HFCLK__FRAC_MASK
#define CAN_HFCLK_DIV_FRAC_SHIFT (16u)
#define CAN_HFCLK_DIV_INT_MASK   CAN_HFCLK__DIVIDER_MASK
#define CAN_HFCLK_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_CAN_HFCLK_H) */

/* [] END OF FILE */
