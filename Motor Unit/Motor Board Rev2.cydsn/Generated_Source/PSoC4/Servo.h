/*******************************************************************************
* File Name: Servo.h  
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

#if !defined(CY_PINS_Servo_H) /* Pins Servo_H */
#define CY_PINS_Servo_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Servo_aliases.h"


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
} Servo_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Servo_Read(void);
void    Servo_Write(uint8 value);
uint8   Servo_ReadDataReg(void);
#if defined(Servo__PC) || (CY_PSOC4_4200L) 
    void    Servo_SetDriveMode(uint8 mode);
#endif
void    Servo_SetInterruptMode(uint16 position, uint16 mode);
uint8   Servo_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Servo_Sleep(void); 
void Servo_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Servo__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Servo_DRIVE_MODE_BITS        (3)
    #define Servo_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Servo_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Servo_SetDriveMode() function.
         *  @{
         */
        #define Servo_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Servo_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Servo_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Servo_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Servo_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Servo_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Servo_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Servo_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Servo_MASK               Servo__MASK
#define Servo_SHIFT              Servo__SHIFT
#define Servo_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Servo_SetInterruptMode() function.
     *  @{
     */
        #define Servo_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Servo_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Servo_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Servo_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Servo__SIO)
    #define Servo_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Servo__PC) && (CY_PSOC4_4200L)
    #define Servo_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Servo_USBIO_DISABLE              ((uint32)(~Servo_USBIO_ENABLE))
    #define Servo_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Servo_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Servo_USBIO_ENTER_SLEEP          ((uint32)((1u << Servo_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Servo_USBIO_SUSPEND_DEL_SHIFT)))
    #define Servo_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Servo_USBIO_SUSPEND_SHIFT)))
    #define Servo_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Servo_USBIO_SUSPEND_DEL_SHIFT)))
    #define Servo_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Servo__PC)
    /* Port Configuration */
    #define Servo_PC                 (* (reg32 *) Servo__PC)
#endif
/* Pin State */
#define Servo_PS                     (* (reg32 *) Servo__PS)
/* Data Register */
#define Servo_DR                     (* (reg32 *) Servo__DR)
/* Input Buffer Disable Override */
#define Servo_INP_DIS                (* (reg32 *) Servo__PC2)

/* Interrupt configuration Registers */
#define Servo_INTCFG                 (* (reg32 *) Servo__INTCFG)
#define Servo_INTSTAT                (* (reg32 *) Servo__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Servo_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Servo__SIO)
    #define Servo_SIO_REG            (* (reg32 *) Servo__SIO)
#endif /* (Servo__SIO_CFG) */

/* USBIO registers */
#if !defined(Servo__PC) && (CY_PSOC4_4200L)
    #define Servo_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Servo_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Servo_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Servo_DRIVE_MODE_SHIFT       (0x00u)
#define Servo_DRIVE_MODE_MASK        (0x07u << Servo_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Servo_H */


/* [] END OF FILE */
