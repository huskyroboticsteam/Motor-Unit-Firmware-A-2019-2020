/*******************************************************************************
* File Name: FAULT_MOTOR.h  
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

#if !defined(CY_PINS_FAULT_MOTOR_H) /* Pins FAULT_MOTOR_H */
#define CY_PINS_FAULT_MOTOR_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FAULT_MOTOR_aliases.h"


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
} FAULT_MOTOR_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FAULT_MOTOR_Read(void);
void    FAULT_MOTOR_Write(uint8 value);
uint8   FAULT_MOTOR_ReadDataReg(void);
#if defined(FAULT_MOTOR__PC) || (CY_PSOC4_4200L) 
    void    FAULT_MOTOR_SetDriveMode(uint8 mode);
#endif
void    FAULT_MOTOR_SetInterruptMode(uint16 position, uint16 mode);
uint8   FAULT_MOTOR_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FAULT_MOTOR_Sleep(void); 
void FAULT_MOTOR_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FAULT_MOTOR__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FAULT_MOTOR_DRIVE_MODE_BITS        (3)
    #define FAULT_MOTOR_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FAULT_MOTOR_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FAULT_MOTOR_SetDriveMode() function.
         *  @{
         */
        #define FAULT_MOTOR_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FAULT_MOTOR_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FAULT_MOTOR_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FAULT_MOTOR_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FAULT_MOTOR_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FAULT_MOTOR_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FAULT_MOTOR_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FAULT_MOTOR_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FAULT_MOTOR_MASK               FAULT_MOTOR__MASK
#define FAULT_MOTOR_SHIFT              FAULT_MOTOR__SHIFT
#define FAULT_MOTOR_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FAULT_MOTOR_SetInterruptMode() function.
     *  @{
     */
        #define FAULT_MOTOR_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FAULT_MOTOR_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FAULT_MOTOR_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FAULT_MOTOR_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FAULT_MOTOR__SIO)
    #define FAULT_MOTOR_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FAULT_MOTOR__PC) && (CY_PSOC4_4200L)
    #define FAULT_MOTOR_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FAULT_MOTOR_USBIO_DISABLE              ((uint32)(~FAULT_MOTOR_USBIO_ENABLE))
    #define FAULT_MOTOR_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FAULT_MOTOR_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FAULT_MOTOR_USBIO_ENTER_SLEEP          ((uint32)((1u << FAULT_MOTOR_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FAULT_MOTOR_USBIO_SUSPEND_DEL_SHIFT)))
    #define FAULT_MOTOR_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FAULT_MOTOR_USBIO_SUSPEND_SHIFT)))
    #define FAULT_MOTOR_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FAULT_MOTOR_USBIO_SUSPEND_DEL_SHIFT)))
    #define FAULT_MOTOR_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FAULT_MOTOR__PC)
    /* Port Configuration */
    #define FAULT_MOTOR_PC                 (* (reg32 *) FAULT_MOTOR__PC)
#endif
/* Pin State */
#define FAULT_MOTOR_PS                     (* (reg32 *) FAULT_MOTOR__PS)
/* Data Register */
#define FAULT_MOTOR_DR                     (* (reg32 *) FAULT_MOTOR__DR)
/* Input Buffer Disable Override */
#define FAULT_MOTOR_INP_DIS                (* (reg32 *) FAULT_MOTOR__PC2)

/* Interrupt configuration Registers */
#define FAULT_MOTOR_INTCFG                 (* (reg32 *) FAULT_MOTOR__INTCFG)
#define FAULT_MOTOR_INTSTAT                (* (reg32 *) FAULT_MOTOR__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FAULT_MOTOR_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FAULT_MOTOR__SIO)
    #define FAULT_MOTOR_SIO_REG            (* (reg32 *) FAULT_MOTOR__SIO)
#endif /* (FAULT_MOTOR__SIO_CFG) */

/* USBIO registers */
#if !defined(FAULT_MOTOR__PC) && (CY_PSOC4_4200L)
    #define FAULT_MOTOR_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FAULT_MOTOR_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FAULT_MOTOR_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FAULT_MOTOR_DRIVE_MODE_SHIFT       (0x00u)
#define FAULT_MOTOR_DRIVE_MODE_MASK        (0x07u << FAULT_MOTOR_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FAULT_MOTOR_H */


/* [] END OF FILE */
