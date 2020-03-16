/*******************************************************************************
* File Name: led_array.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "led_array.h"

static led_array_BACKUP_STRUCT  led_array_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: led_array_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet led_array_SUT.c usage_led_array_Sleep_Wakeup
*******************************************************************************/
void led_array_Sleep(void)
{
    #if defined(led_array__PC)
        led_array_backup.pcState = led_array_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            led_array_backup.usbState = led_array_CR1_REG;
            led_array_USB_POWER_REG |= led_array_USBIO_ENTER_SLEEP;
            led_array_CR1_REG &= led_array_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(led_array__SIO)
        led_array_backup.sioState = led_array_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        led_array_SIO_REG &= (uint32)(~led_array_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: led_array_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to led_array_Sleep() for an example usage.
*******************************************************************************/
void led_array_Wakeup(void)
{
    #if defined(led_array__PC)
        led_array_PC = led_array_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            led_array_USB_POWER_REG &= led_array_USBIO_EXIT_SLEEP_PH1;
            led_array_CR1_REG = led_array_backup.usbState;
            led_array_USB_POWER_REG &= led_array_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(led_array__SIO)
        led_array_SIO_REG = led_array_backup.sioState;
    #endif
}


/* [] END OF FILE */
