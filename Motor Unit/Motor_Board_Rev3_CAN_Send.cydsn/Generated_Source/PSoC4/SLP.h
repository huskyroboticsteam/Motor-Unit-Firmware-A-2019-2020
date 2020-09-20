/*******************************************************************************
* File Name: SLP.h  
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

#if !defined(CY_PINS_SLP_H) /* Pins SLP_H */
#define CY_PINS_SLP_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SLP_aliases.h"


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
} SLP_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   SLP_Read(void);
void    SLP_Write(uint8 value);
uint8   SLP_ReadDataReg(void);
#if defined(SLP__PC) || (CY_PSOC4_4200L) 
    void    SLP_SetDriveMode(uint8 mode);
#endif
void    SLP_SetInterruptMode(uint16 position, uint16 mode);
uint8   SLP_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void SLP_Sleep(void); 
void SLP_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(SLP__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define SLP_DRIVE_MODE_BITS        (3)
    #define SLP_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SLP_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the SLP_SetDriveMode() function.
         *  @{
         */
        #define SLP_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define SLP_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define SLP_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define SLP_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define SLP_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define SLP_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define SLP_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define SLP_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define SLP_MASK               SLP__MASK
#define SLP_SHIFT              SLP__SHIFT
#define SLP_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in SLP_SetInterruptMode() function.
     *  @{
     */
        #define SLP_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define SLP_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define SLP_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define SLP_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(SLP__SIO)
    #define SLP_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(SLP__PC) && (CY_PSOC4_4200L)
    #define SLP_USBIO_ENABLE               ((uint32)0x80000000u)
    #define SLP_USBIO_DISABLE              ((uint32)(~SLP_USBIO_ENABLE))
    #define SLP_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define SLP_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define SLP_USBIO_ENTER_SLEEP          ((uint32)((1u << SLP_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << SLP_USBIO_SUSPEND_DEL_SHIFT)))
    #define SLP_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << SLP_USBIO_SUSPEND_SHIFT)))
    #define SLP_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << SLP_USBIO_SUSPEND_DEL_SHIFT)))
    #define SLP_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(SLP__PC)
    /* Port Configuration */
    #define SLP_PC                 (* (reg32 *) SLP__PC)
#endif
/* Pin State */
#define SLP_PS                     (* (reg32 *) SLP__PS)
/* Data Register */
#define SLP_DR                     (* (reg32 *) SLP__DR)
/* Input Buffer Disable Override */
#define SLP_INP_DIS                (* (reg32 *) SLP__PC2)

/* Interrupt configuration Registers */
#define SLP_INTCFG                 (* (reg32 *) SLP__INTCFG)
#define SLP_INTSTAT                (* (reg32 *) SLP__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define SLP_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(SLP__SIO)
    #define SLP_SIO_REG            (* (reg32 *) SLP__SIO)
#endif /* (SLP__SIO_CFG) */

/* USBIO registers */
#if !defined(SLP__PC) && (CY_PSOC4_4200L)
    #define SLP_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define SLP_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define SLP_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define SLP_DRIVE_MODE_SHIFT       (0x00u)
#define SLP_DRIVE_MODE_MASK        (0x07u << SLP_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins SLP_H */


/* [] END OF FILE */
