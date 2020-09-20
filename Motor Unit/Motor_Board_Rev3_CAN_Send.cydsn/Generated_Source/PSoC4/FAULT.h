/*******************************************************************************
* File Name: FAULT.h  
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

#if !defined(CY_PINS_FAULT_H) /* Pins FAULT_H */
#define CY_PINS_FAULT_H

#include "cytypes.h"
#include "cyfitter.h"
#include "FAULT_aliases.h"


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
} FAULT_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   FAULT_Read(void);
void    FAULT_Write(uint8 value);
uint8   FAULT_ReadDataReg(void);
#if defined(FAULT__PC) || (CY_PSOC4_4200L) 
    void    FAULT_SetDriveMode(uint8 mode);
#endif
void    FAULT_SetInterruptMode(uint16 position, uint16 mode);
uint8   FAULT_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void FAULT_Sleep(void); 
void FAULT_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(FAULT__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define FAULT_DRIVE_MODE_BITS        (3)
    #define FAULT_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - FAULT_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the FAULT_SetDriveMode() function.
         *  @{
         */
        #define FAULT_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define FAULT_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define FAULT_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define FAULT_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define FAULT_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define FAULT_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define FAULT_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define FAULT_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define FAULT_MASK               FAULT__MASK
#define FAULT_SHIFT              FAULT__SHIFT
#define FAULT_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in FAULT_SetInterruptMode() function.
     *  @{
     */
        #define FAULT_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define FAULT_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define FAULT_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define FAULT_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(FAULT__SIO)
    #define FAULT_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(FAULT__PC) && (CY_PSOC4_4200L)
    #define FAULT_USBIO_ENABLE               ((uint32)0x80000000u)
    #define FAULT_USBIO_DISABLE              ((uint32)(~FAULT_USBIO_ENABLE))
    #define FAULT_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define FAULT_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define FAULT_USBIO_ENTER_SLEEP          ((uint32)((1u << FAULT_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << FAULT_USBIO_SUSPEND_DEL_SHIFT)))
    #define FAULT_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << FAULT_USBIO_SUSPEND_SHIFT)))
    #define FAULT_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << FAULT_USBIO_SUSPEND_DEL_SHIFT)))
    #define FAULT_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(FAULT__PC)
    /* Port Configuration */
    #define FAULT_PC                 (* (reg32 *) FAULT__PC)
#endif
/* Pin State */
#define FAULT_PS                     (* (reg32 *) FAULT__PS)
/* Data Register */
#define FAULT_DR                     (* (reg32 *) FAULT__DR)
/* Input Buffer Disable Override */
#define FAULT_INP_DIS                (* (reg32 *) FAULT__PC2)

/* Interrupt configuration Registers */
#define FAULT_INTCFG                 (* (reg32 *) FAULT__INTCFG)
#define FAULT_INTSTAT                (* (reg32 *) FAULT__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define FAULT_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(FAULT__SIO)
    #define FAULT_SIO_REG            (* (reg32 *) FAULT__SIO)
#endif /* (FAULT__SIO_CFG) */

/* USBIO registers */
#if !defined(FAULT__PC) && (CY_PSOC4_4200L)
    #define FAULT_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define FAULT_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define FAULT_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define FAULT_DRIVE_MODE_SHIFT       (0x00u)
#define FAULT_DRIVE_MODE_MASK        (0x07u << FAULT_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins FAULT_H */


/* [] END OF FILE */
