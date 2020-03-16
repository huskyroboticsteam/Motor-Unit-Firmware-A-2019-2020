/*******************************************************************************
* File Name: Array_LED.h  
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

#if !defined(CY_PINS_Array_LED_H) /* Pins Array_LED_H */
#define CY_PINS_Array_LED_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Array_LED_aliases.h"


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
} Array_LED_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Array_LED_Read(void);
void    Array_LED_Write(uint8 value);
uint8   Array_LED_ReadDataReg(void);
#if defined(Array_LED__PC) || (CY_PSOC4_4200L) 
    void    Array_LED_SetDriveMode(uint8 mode);
#endif
void    Array_LED_SetInterruptMode(uint16 position, uint16 mode);
uint8   Array_LED_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Array_LED_Sleep(void); 
void Array_LED_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Array_LED__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Array_LED_DRIVE_MODE_BITS        (3)
    #define Array_LED_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Array_LED_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Array_LED_SetDriveMode() function.
         *  @{
         */
        #define Array_LED_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Array_LED_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Array_LED_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Array_LED_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Array_LED_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Array_LED_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Array_LED_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Array_LED_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Array_LED_MASK               Array_LED__MASK
#define Array_LED_SHIFT              Array_LED__SHIFT
#define Array_LED_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Array_LED_SetInterruptMode() function.
     *  @{
     */
        #define Array_LED_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Array_LED_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Array_LED_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Array_LED_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Array_LED__SIO)
    #define Array_LED_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Array_LED__PC) && (CY_PSOC4_4200L)
    #define Array_LED_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Array_LED_USBIO_DISABLE              ((uint32)(~Array_LED_USBIO_ENABLE))
    #define Array_LED_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Array_LED_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Array_LED_USBIO_ENTER_SLEEP          ((uint32)((1u << Array_LED_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Array_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Array_LED_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Array_LED_USBIO_SUSPEND_SHIFT)))
    #define Array_LED_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Array_LED_USBIO_SUSPEND_DEL_SHIFT)))
    #define Array_LED_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Array_LED__PC)
    /* Port Configuration */
    #define Array_LED_PC                 (* (reg32 *) Array_LED__PC)
#endif
/* Pin State */
#define Array_LED_PS                     (* (reg32 *) Array_LED__PS)
/* Data Register */
#define Array_LED_DR                     (* (reg32 *) Array_LED__DR)
/* Input Buffer Disable Override */
#define Array_LED_INP_DIS                (* (reg32 *) Array_LED__PC2)

/* Interrupt configuration Registers */
#define Array_LED_INTCFG                 (* (reg32 *) Array_LED__INTCFG)
#define Array_LED_INTSTAT                (* (reg32 *) Array_LED__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Array_LED_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Array_LED__SIO)
    #define Array_LED_SIO_REG            (* (reg32 *) Array_LED__SIO)
#endif /* (Array_LED__SIO_CFG) */

/* USBIO registers */
#if !defined(Array_LED__PC) && (CY_PSOC4_4200L)
    #define Array_LED_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Array_LED_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Array_LED_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Array_LED_DRIVE_MODE_SHIFT       (0x00u)
#define Array_LED_DRIVE_MODE_MASK        (0x07u << Array_LED_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Array_LED_H */


/* [] END OF FILE */
