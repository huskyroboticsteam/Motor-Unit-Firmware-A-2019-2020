/*******************************************************************************
* File Name: StripLights_StringSel_PM.c
* Version 1.80
*
* Description:
*  This file contains the setup, control, and status commands to support 
*  the component operation in the low power mode. 
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "StripLights_StringSel.h"

/* Check for removal by optimization */
#if !defined(StripLights_StringSel_Sync_ctrl_reg__REMOVED)

static StripLights_StringSel_BACKUP_STRUCT  StripLights_StringSel_backup = {0u};

    
/*******************************************************************************
* Function Name: StripLights_StringSel_SaveConfig
********************************************************************************
*
* Summary:
*  Saves the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void StripLights_StringSel_SaveConfig(void) 
{
    StripLights_StringSel_backup.controlState = StripLights_StringSel_Control;
}


/*******************************************************************************
* Function Name: StripLights_StringSel_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the control register value.
*
* Parameters:
*  None
*
* Return:
*  None
*
*
*******************************************************************************/
void StripLights_StringSel_RestoreConfig(void) 
{
     StripLights_StringSel_Control = StripLights_StringSel_backup.controlState;
}


/*******************************************************************************
* Function Name: StripLights_StringSel_Sleep
********************************************************************************
*
* Summary:
*  Prepares the component for entering the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void StripLights_StringSel_Sleep(void) 
{
    StripLights_StringSel_SaveConfig();
}


/*******************************************************************************
* Function Name: StripLights_StringSel_Wakeup
********************************************************************************
*
* Summary:
*  Restores the component after waking up from the low power mode.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void StripLights_StringSel_Wakeup(void)  
{
    StripLights_StringSel_RestoreConfig();
}

#endif /* End check for removal by optimization */


/* [] END OF FILE */
