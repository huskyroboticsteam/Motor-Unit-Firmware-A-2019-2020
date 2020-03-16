/*******************************************************************************
* File Name: Alert.h  
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

#if !defined(CY_PINS_Alert_H) /* Pins Alert_H */
#define CY_PINS_Alert_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Alert_aliases.h"


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
} Alert_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Alert_Read(void);
void    Alert_Write(uint8 value);
uint8   Alert_ReadDataReg(void);
#if defined(Alert__PC) || (CY_PSOC4_4200L) 
    void    Alert_SetDriveMode(uint8 mode);
#endif
void    Alert_SetInterruptMode(uint16 position, uint16 mode);
uint8   Alert_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Alert_Sleep(void); 
void Alert_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Alert__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Alert_DRIVE_MODE_BITS        (3)
    #define Alert_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Alert_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Alert_SetDriveMode() function.
         *  @{
         */
        #define Alert_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Alert_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Alert_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Alert_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Alert_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Alert_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Alert_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Alert_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Alert_MASK               Alert__MASK
#define Alert_SHIFT              Alert__SHIFT
#define Alert_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Alert_SetInterruptMode() function.
     *  @{
     */
        #define Alert_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Alert_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Alert_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Alert_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Alert__SIO)
    #define Alert_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Alert__PC) && (CY_PSOC4_4200L)
    #define Alert_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Alert_USBIO_DISABLE              ((uint32)(~Alert_USBIO_ENABLE))
    #define Alert_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Alert_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Alert_USBIO_ENTER_SLEEP          ((uint32)((1u << Alert_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Alert_USBIO_SUSPEND_DEL_SHIFT)))
    #define Alert_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Alert_USBIO_SUSPEND_SHIFT)))
    #define Alert_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Alert_USBIO_SUSPEND_DEL_SHIFT)))
    #define Alert_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Alert__PC)
    /* Port Configuration */
    #define Alert_PC                 (* (reg32 *) Alert__PC)
#endif
/* Pin State */
#define Alert_PS                     (* (reg32 *) Alert__PS)
/* Data Register */
#define Alert_DR                     (* (reg32 *) Alert__DR)
/* Input Buffer Disable Override */
#define Alert_INP_DIS                (* (reg32 *) Alert__PC2)

/* Interrupt configuration Registers */
#define Alert_INTCFG                 (* (reg32 *) Alert__INTCFG)
#define Alert_INTSTAT                (* (reg32 *) Alert__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Alert_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Alert__SIO)
    #define Alert_SIO_REG            (* (reg32 *) Alert__SIO)
#endif /* (Alert__SIO_CFG) */

/* USBIO registers */
#if !defined(Alert__PC) && (CY_PSOC4_4200L)
    #define Alert_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Alert_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Alert_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Alert_DRIVE_MODE_SHIFT       (0x00u)
#define Alert_DRIVE_MODE_MASK        (0x07u << Alert_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Alert_H */


/* [] END OF FILE */
