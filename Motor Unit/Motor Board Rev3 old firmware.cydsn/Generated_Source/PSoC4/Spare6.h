/*******************************************************************************
* File Name: Spare6.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_Spare6_H) /* Pins Spare6_H */
#define CY_PINS_Spare6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Spare6_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} Spare6_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Spare6_Read(void);
void    Spare6_Write(uint8 value);
uint8   Spare6_ReadDataReg(void);
#if defined(Spare6__PC) || (CY_PSOC4_4200L) 
    void    Spare6_SetDriveMode(uint8 mode);
#endif
void    Spare6_SetInterruptMode(uint16 position, uint16 mode);
uint8   Spare6_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Spare6_Sleep(void); 
void Spare6_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Spare6__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Spare6_DRIVE_MODE_BITS        (3)
    #define Spare6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Spare6_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Spare6_SetDriveMode() function.
         *  @{
         */
        #define Spare6_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Spare6_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Spare6_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Spare6_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Spare6_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Spare6_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Spare6_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Spare6_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Spare6_MASK               Spare6__MASK
#define Spare6_SHIFT              Spare6__SHIFT
#define Spare6_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Spare6_SetInterruptMode() function.
     *  @{
     */
        #define Spare6_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Spare6_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Spare6_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Spare6_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Spare6__SIO)
    #define Spare6_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Spare6__PC) && (CY_PSOC4_4200L)
    #define Spare6_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Spare6_USBIO_DISABLE              ((uint32)(~Spare6_USBIO_ENABLE))
    #define Spare6_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Spare6_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Spare6_USBIO_ENTER_SLEEP          ((uint32)((1u << Spare6_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Spare6_USBIO_SUSPEND_DEL_SHIFT)))
    #define Spare6_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Spare6_USBIO_SUSPEND_SHIFT)))
    #define Spare6_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Spare6_USBIO_SUSPEND_DEL_SHIFT)))
    #define Spare6_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Spare6__PC)
    /* Port Configuration */
    #define Spare6_PC                 (* (reg32 *) Spare6__PC)
#endif
/* Pin State */
#define Spare6_PS                     (* (reg32 *) Spare6__PS)
/* Data Register */
#define Spare6_DR                     (* (reg32 *) Spare6__DR)
/* Input Buffer Disable Override */
#define Spare6_INP_DIS                (* (reg32 *) Spare6__PC2)

/* Interrupt configuration Registers */
#define Spare6_INTCFG                 (* (reg32 *) Spare6__INTCFG)
#define Spare6_INTSTAT                (* (reg32 *) Spare6__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Spare6_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Spare6__SIO)
    #define Spare6_SIO_REG            (* (reg32 *) Spare6__SIO)
#endif /* (Spare6__SIO_CFG) */

/* USBIO registers */
#if !defined(Spare6__PC) && (CY_PSOC4_4200L)
    #define Spare6_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Spare6_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Spare6_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Spare6_DRIVE_MODE_SHIFT       (0x00u)
#define Spare6_DRIVE_MODE_MASK        (0x07u << Spare6_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Spare6_H */


/* [] END OF FILE */
