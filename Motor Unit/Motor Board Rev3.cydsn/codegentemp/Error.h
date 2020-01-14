/*******************************************************************************
* File Name: Error.h  
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

#if !defined(CY_PINS_Error_H) /* Pins Error_H */
#define CY_PINS_Error_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Error_aliases.h"


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
} Error_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Error_Read(void);
void    Error_Write(uint8 value);
uint8   Error_ReadDataReg(void);
#if defined(Error__PC) || (CY_PSOC4_4200L) 
    void    Error_SetDriveMode(uint8 mode);
#endif
void    Error_SetInterruptMode(uint16 position, uint16 mode);
uint8   Error_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Error_Sleep(void); 
void Error_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Error__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Error_DRIVE_MODE_BITS        (3)
    #define Error_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Error_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Error_SetDriveMode() function.
         *  @{
         */
        #define Error_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Error_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Error_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Error_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Error_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Error_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Error_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Error_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Error_MASK               Error__MASK
#define Error_SHIFT              Error__SHIFT
#define Error_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Error_SetInterruptMode() function.
     *  @{
     */
        #define Error_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Error_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Error_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Error_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Error__SIO)
    #define Error_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Error__PC) && (CY_PSOC4_4200L)
    #define Error_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Error_USBIO_DISABLE              ((uint32)(~Error_USBIO_ENABLE))
    #define Error_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Error_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Error_USBIO_ENTER_SLEEP          ((uint32)((1u << Error_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Error_USBIO_SUSPEND_DEL_SHIFT)))
    #define Error_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Error_USBIO_SUSPEND_SHIFT)))
    #define Error_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Error_USBIO_SUSPEND_DEL_SHIFT)))
    #define Error_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Error__PC)
    /* Port Configuration */
    #define Error_PC                 (* (reg32 *) Error__PC)
#endif
/* Pin State */
#define Error_PS                     (* (reg32 *) Error__PS)
/* Data Register */
#define Error_DR                     (* (reg32 *) Error__DR)
/* Input Buffer Disable Override */
#define Error_INP_DIS                (* (reg32 *) Error__PC2)

/* Interrupt configuration Registers */
#define Error_INTCFG                 (* (reg32 *) Error__INTCFG)
#define Error_INTSTAT                (* (reg32 *) Error__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Error_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Error__SIO)
    #define Error_SIO_REG            (* (reg32 *) Error__SIO)
#endif /* (Error__SIO_CFG) */

/* USBIO registers */
#if !defined(Error__PC) && (CY_PSOC4_4200L)
    #define Error_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Error_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Error_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Error_DRIVE_MODE_SHIFT       (0x00u)
#define Error_DRIVE_MODE_MASK        (0x07u << Error_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Error_H */


/* [] END OF FILE */
