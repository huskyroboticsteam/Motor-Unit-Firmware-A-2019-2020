/*******************************************************************************
* File Name: vout.h  
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

#if !defined(CY_PINS_vout_H) /* Pins vout_H */
#define CY_PINS_vout_H

#include "cytypes.h"
#include "cyfitter.h"
#include "vout_aliases.h"


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
} vout_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   vout_Read(void);
void    vout_Write(uint8 value);
uint8   vout_ReadDataReg(void);
#if defined(vout__PC) || (CY_PSOC4_4200L) 
    void    vout_SetDriveMode(uint8 mode);
#endif
void    vout_SetInterruptMode(uint16 position, uint16 mode);
uint8   vout_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void vout_Sleep(void); 
void vout_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(vout__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define vout_DRIVE_MODE_BITS        (3)
    #define vout_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - vout_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the vout_SetDriveMode() function.
         *  @{
         */
        #define vout_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define vout_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define vout_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define vout_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define vout_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define vout_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define vout_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define vout_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define vout_MASK               vout__MASK
#define vout_SHIFT              vout__SHIFT
#define vout_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in vout_SetInterruptMode() function.
     *  @{
     */
        #define vout_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define vout_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define vout_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define vout_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(vout__SIO)
    #define vout_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(vout__PC) && (CY_PSOC4_4200L)
    #define vout_USBIO_ENABLE               ((uint32)0x80000000u)
    #define vout_USBIO_DISABLE              ((uint32)(~vout_USBIO_ENABLE))
    #define vout_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define vout_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define vout_USBIO_ENTER_SLEEP          ((uint32)((1u << vout_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << vout_USBIO_SUSPEND_DEL_SHIFT)))
    #define vout_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << vout_USBIO_SUSPEND_SHIFT)))
    #define vout_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << vout_USBIO_SUSPEND_DEL_SHIFT)))
    #define vout_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(vout__PC)
    /* Port Configuration */
    #define vout_PC                 (* (reg32 *) vout__PC)
#endif
/* Pin State */
#define vout_PS                     (* (reg32 *) vout__PS)
/* Data Register */
#define vout_DR                     (* (reg32 *) vout__DR)
/* Input Buffer Disable Override */
#define vout_INP_DIS                (* (reg32 *) vout__PC2)

/* Interrupt configuration Registers */
#define vout_INTCFG                 (* (reg32 *) vout__INTCFG)
#define vout_INTSTAT                (* (reg32 *) vout__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define vout_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(vout__SIO)
    #define vout_SIO_REG            (* (reg32 *) vout__SIO)
#endif /* (vout__SIO_CFG) */

/* USBIO registers */
#if !defined(vout__PC) && (CY_PSOC4_4200L)
    #define vout_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define vout_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define vout_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define vout_DRIVE_MODE_SHIFT       (0x00u)
#define vout_DRIVE_MODE_MASK        (0x07u << vout_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins vout_H */


/* [] END OF FILE */
