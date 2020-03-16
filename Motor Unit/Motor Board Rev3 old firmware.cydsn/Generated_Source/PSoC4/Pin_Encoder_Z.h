/*******************************************************************************
* File Name: Pin_Encoder_Z.h  
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

#if !defined(CY_PINS_Pin_Encoder_Z_H) /* Pins Pin_Encoder_Z_H */
#define CY_PINS_Pin_Encoder_Z_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Pin_Encoder_Z_aliases.h"


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
} Pin_Encoder_Z_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   Pin_Encoder_Z_Read(void);
void    Pin_Encoder_Z_Write(uint8 value);
uint8   Pin_Encoder_Z_ReadDataReg(void);
#if defined(Pin_Encoder_Z__PC) || (CY_PSOC4_4200L) 
    void    Pin_Encoder_Z_SetDriveMode(uint8 mode);
#endif
void    Pin_Encoder_Z_SetInterruptMode(uint16 position, uint16 mode);
uint8   Pin_Encoder_Z_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void Pin_Encoder_Z_Sleep(void); 
void Pin_Encoder_Z_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(Pin_Encoder_Z__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define Pin_Encoder_Z_DRIVE_MODE_BITS        (3)
    #define Pin_Encoder_Z_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Pin_Encoder_Z_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the Pin_Encoder_Z_SetDriveMode() function.
         *  @{
         */
        #define Pin_Encoder_Z_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define Pin_Encoder_Z_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define Pin_Encoder_Z_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define Pin_Encoder_Z_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define Pin_Encoder_Z_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define Pin_Encoder_Z_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define Pin_Encoder_Z_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define Pin_Encoder_Z_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define Pin_Encoder_Z_MASK               Pin_Encoder_Z__MASK
#define Pin_Encoder_Z_SHIFT              Pin_Encoder_Z__SHIFT
#define Pin_Encoder_Z_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in Pin_Encoder_Z_SetInterruptMode() function.
     *  @{
     */
        #define Pin_Encoder_Z_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define Pin_Encoder_Z_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define Pin_Encoder_Z_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define Pin_Encoder_Z_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(Pin_Encoder_Z__SIO)
    #define Pin_Encoder_Z_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(Pin_Encoder_Z__PC) && (CY_PSOC4_4200L)
    #define Pin_Encoder_Z_USBIO_ENABLE               ((uint32)0x80000000u)
    #define Pin_Encoder_Z_USBIO_DISABLE              ((uint32)(~Pin_Encoder_Z_USBIO_ENABLE))
    #define Pin_Encoder_Z_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define Pin_Encoder_Z_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define Pin_Encoder_Z_USBIO_ENTER_SLEEP          ((uint32)((1u << Pin_Encoder_Z_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << Pin_Encoder_Z_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pin_Encoder_Z_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << Pin_Encoder_Z_USBIO_SUSPEND_SHIFT)))
    #define Pin_Encoder_Z_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << Pin_Encoder_Z_USBIO_SUSPEND_DEL_SHIFT)))
    #define Pin_Encoder_Z_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(Pin_Encoder_Z__PC)
    /* Port Configuration */
    #define Pin_Encoder_Z_PC                 (* (reg32 *) Pin_Encoder_Z__PC)
#endif
/* Pin State */
#define Pin_Encoder_Z_PS                     (* (reg32 *) Pin_Encoder_Z__PS)
/* Data Register */
#define Pin_Encoder_Z_DR                     (* (reg32 *) Pin_Encoder_Z__DR)
/* Input Buffer Disable Override */
#define Pin_Encoder_Z_INP_DIS                (* (reg32 *) Pin_Encoder_Z__PC2)

/* Interrupt configuration Registers */
#define Pin_Encoder_Z_INTCFG                 (* (reg32 *) Pin_Encoder_Z__INTCFG)
#define Pin_Encoder_Z_INTSTAT                (* (reg32 *) Pin_Encoder_Z__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define Pin_Encoder_Z_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(Pin_Encoder_Z__SIO)
    #define Pin_Encoder_Z_SIO_REG            (* (reg32 *) Pin_Encoder_Z__SIO)
#endif /* (Pin_Encoder_Z__SIO_CFG) */

/* USBIO registers */
#if !defined(Pin_Encoder_Z__PC) && (CY_PSOC4_4200L)
    #define Pin_Encoder_Z_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define Pin_Encoder_Z_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define Pin_Encoder_Z_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define Pin_Encoder_Z_DRIVE_MODE_SHIFT       (0x00u)
#define Pin_Encoder_Z_DRIVE_MODE_MASK        (0x07u << Pin_Encoder_Z_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins Pin_Encoder_Z_H */


/* [] END OF FILE */
