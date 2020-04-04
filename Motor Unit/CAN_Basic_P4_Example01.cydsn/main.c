/*******************************************************************************
* File Name: main.c
*
* Version: 1.0
*
* Description:
*  In this project, the CAN component is configured to transmit two messages
*  over the CAN bus:
*   Message 1 - Status of Switch 1. Sent whenever there is a change in the
*               status.
*   Message 2 - ADC data. Sent every 100ms.
*
*  The component is also configured to receive data which is used to set the
*  pulse width of the PWM used in the project.
*  Both transmitted and received data are send out over UART, so that it can be
*  received on a PC using a USB-UART bridge (PSoC 5LP) on CY8CKIT-044
*  Development Kit and the terminal software.
*
*  This is only one part of the CAN example project. Use this example along
*  with CAN_Full_P4_Example for complete demonstration.
*
* Hardware Dependency:
*  CY8CKIT-044
*  CY8CKIT-017
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation. All rights reserved.
* This software is owned by Cypress Semiconductor Corporation and is protected
* by and subject to worldwide patent and copyright laws and treaties.
* Therefore, you may use this software ony as provided in the license agreement
* accompanying the software package from which you obtained this software.
* CYPRESS AND ITS SUPPLIERS MAKE NO WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
* WITH REGARD TO THIS SOFTWARE, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT,
* IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
*******************************************************************************/
#include <project.h>
#include <stdio.h>

/* Switch debounce delay in milliseconds */
#define SWITCH_DEBOUNCE_UNIT   (1u)

/* Number of debounce units to count delay, before consider that switch is pressed */
#define SWITCH_DEBOUNCE_PERIOD (10u)

/* Switch state defines */
#define SWITCH_RELEASED        (0u)
#define SWITCH_PRESSED         (1u)

#define TX_DATA_SIZE           (25u)
#define ADC_CHANNEL_NUMBER_0   (0u)

/* Function prototypes */
static uint32 ReadSwSwitch(void);
CY_ISR_PROTO(ISR_CAN);

/* Global variable used to store switch state */
uint8 switchState = SWITCH_RELEASED;

/* Global variable used to store ISR flag */
volatile uint8 isrFlag = 0u;


/*******************************************************************************
* Function Name: main
********************************************************************************
*
* Summary:
*  main() performs the following functions:
*  1: Starts the ADC, UART, PWM, CAN, ISR components.
*  2: Starts ADC conversion.
*  3: Gets the converted result, sends message over a CAN and sends the 
*     converted result over UART.
*  4: Polls the status of Switch 1 and sends a message over CAN if it changes.
*  5: Sets a PWM pulse width and sends it over UART.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
int main()
{
    int16 output;
    uint16 resMilliVolts;
    char8 txData[TX_DATA_SIZE];

    UART_Start();
    ADC_Start();
    PWM_Start();

    /* Start ADC conversion */
    ADC_StartConvert();

    CAN_Start();

    /* Set CAN interrupt handler to local routine */
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);

    CyGlobalIntEnable;

    for(;;)
    {
        if (ADC_IsEndConversion(ADC_RETURN_STATUS))
        {
            /* Gets ADC conversion result */
            output = ADC_GetResult16(ADC_CHANNEL_NUMBER_0);

            /* Saturates ADC result to positive numbers */
            if (output < 0)
            {
                output = 0;
            }
            
            /* Converts ADC result to milli volts */
            resMilliVolts = (uint16) ADC_CountsTo_mVolts(ADC_CHANNEL_NUMBER_0, output);
            
            /* Sends value of ADC output via CAN */
            CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_ADCdata, HI8(resMilliVolts));
            CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_ADCdata, LO8(resMilliVolts));
            CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_TX_DATA_BYTE6(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_TX_DATA_BYTE7(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_TX_DATA_BYTE8(CAN_TX_MAILBOX_ADCdata, 0u);
            CAN_SendMsgADCdata();

            /* Display value of ADC output on LCD */
            sprintf(txData, "ADC out: %u.%.3u \r\n", (resMilliVolts / 1000u), (resMilliVolts % 1000u));
            UART_UartPutString(txData);
        }

        /* Change configuration at switch press or release event */
        if (switchState != ReadSwSwitch())    /* Switch state changed status */
        {
            /* Store the current switch state */
            switchState = ReadSwSwitch();

            /* Fill CAN data depending on switch state */
            if (Switch1_Read() == 0u)
            {
                CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_switchStatus, SWITCH_PRESSED);
                UART_UartPutString("switch1 pressed.\r\n");
            }
            else
            {
                CAN_TX_DATA_BYTE1(CAN_TX_MAILBOX_switchStatus, SWITCH_RELEASED);
                UART_UartPutString("switch1 released.\r\n");
            }
            CAN_TX_DATA_BYTE2(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE3(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE4(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE5(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE6(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE7(CAN_TX_MAILBOX_switchStatus, 0u);
            CAN_TX_DATA_BYTE8(CAN_TX_MAILBOX_switchStatus, 0u);

            /* Send CAN message with switch state */
            CAN_SendMsgswitchStatus();
        }

        if (isrFlag != 0u)
        {
            /* Set PWM pulse width */
            PWM_WriteCompare(CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_0));

            /* Puts out over UART value of PWM pulse width */
            sprintf(txData, "PWM pulse width: %X \r\n", CAN_RX_DATA_BYTE1(CAN_RX_MAILBOX_0));
            UART_UartPutString(txData);
            
            /* Clear the isrFlag */
            isrFlag = 0u;
        }

        CyDelay(100u);
    }
}


/*******************************************************************************
* Function Name: ISR_CAN
********************************************************************************
*
* Summary:
*  This ISR is executed at a Receive Message event and set the isrFlag.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;

    /* Set the isrFlag */
    isrFlag = 1u;

    /* Acknowledges receipt of new message */
    CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_0);
}


/*******************************************************************************
* Function Name: ReadSwSwitch
********************************************************************************
* Summary:
*  Reads and returns the current status of the switch.
*
* Parameters:
*  None
*
* Return:
*  Returns a non-zero value, if switch is pressed, and a zero value otherwise.
*
*******************************************************************************/
static uint32 ReadSwSwitch(void)
{
    uint32 heldDown;
    uint32 swStatus;

    swStatus = 0u;  /* Switch is not active */
    heldDown = 0u;  /* Reset debounce counter */

    /* Wait for debounce period before determining whether the switch is pressed */
    while (Switch1_Read() == SWITCH_PRESSED)
    {
        /* Count debounce period */
        CyDelay(SWITCH_DEBOUNCE_UNIT);
        ++heldDown;

        if (heldDown > SWITCH_DEBOUNCE_PERIOD)
        {
            swStatus = 1u; /* Switch is pressed */
            break;
        }
    }

    return (swStatus);
}

/* [] END OF FILE */
