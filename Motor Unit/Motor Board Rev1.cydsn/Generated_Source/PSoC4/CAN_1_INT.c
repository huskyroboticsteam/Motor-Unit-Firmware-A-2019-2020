/*******************************************************************************
* File Name: CAN_1_INT.c
* Version 3.0
*
* Description:
*  This file contains Interrupt Service Routine (ISR) for CAN Component.
*  The Interrupt handlers functions are generated accordingly to the PSoC
*  Creator Customizer inputs.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "CAN_1.h"
#include "cyapicallbacks.h"

/* `#START CAN_INT_C_CODE_DEFINITION` */

/* `#END` */

#if (CAN_1_ARB_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_ArbLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Arbitration Lost Interrupt. Clears
    *  Arbitration Lost interrupt flag. Only generated if Arbitration Lost
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_ArbLostIsr(void) 
    {
        /* Clear Arbitration Lost flag */
        CAN_1_INT_SR_REG = CAN_1_ARBITRATION_LOST_MASK;

        /* `#START ARBITRATION_LOST_ISR` */

        /* `#END` */

        #ifdef CAN_1_ARB_LOST_ISR_CALLBACK
            CAN_1_ArbLostIsr_Callback();
        #endif /* CAN_1_ARB_LOST_ISR_CALLBACK */
    }
#endif /* CAN_1_ARB_LOST */


#if (CAN_1_OVERLOAD)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_OvrLdErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Overload Error Interrupt. Clears Overload
    *  Error interrupt flag. Only generated if Overload Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_OvrLdErrorIsr(void) 
    {
        /* Clear Overload Error flag */
        CAN_1_INT_SR_REG = CAN_1_OVERLOAD_ERROR_MASK;

        /* `#START OVER_LOAD_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_OVR_LD_ERROR_ISR_CALLBACK
            CAN_1_OvrLdErrorIsr_Callback();
        #endif /* CAN_1_OVR_LD_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_OVERLOAD */


#if (CAN_1_BIT_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_BitErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Error Interrupt. Clears Bit Error
    *  interrupt flag. Only generated if Bit Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_BitErrorIsr(void) 
    {
        /* Clear Bit Error flag */
        CAN_1_INT_SR_REG = CAN_1_BIT_ERROR_MASK;

        /* `#START BIT_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_BIT_ERROR_ISR_CALLBACK
            CAN_1_BitErrorIsr_Callback();
        #endif /* CAN_1_BIT_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_BIT_ERR */


#if (CAN_1_STUFF_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_BitStuffErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bit Stuff Error Interrupt. Clears Bit Stuff
    *  Error interrupt flag. Only generated if Bit Stuff Error Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_BitStuffErrorIsr(void) 
    {
        /* Clear Stuff Error flag */
        CAN_1_INT_SR_REG = CAN_1_STUFF_ERROR_MASK;

        /* `#START BIT_STUFF_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_BIT_STUFF_ERROR_ISR_CALLBACK
            CAN_1_BitStuffErrorIsr_Callback();
        #endif /* CAN_1_BIT_STUFF_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_STUFF_ERR */


#if (CAN_1_ACK_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_AckErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Acknowledge Error Interrupt. Clears
    *  Acknowledge Error interrupt flag. Only generated if Acknowledge Error
    *  Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_AckErrorIsr(void) 
    {
        /* Clear Acknoledge Error flag */
        CAN_1_INT_SR_REG = CAN_1_ACK_ERROR_MASK;

        /* `#START ACKNOWLEDGE_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_ACK_ERROR_ISR_CALLBACK
            CAN_1_AckErrorIsr_Callback();
        #endif /* CAN_1_ACK_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_ACK_ERR */


#if (CAN_1_FORM_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_MsgErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Form Error Interrupt. Clears Form Error
    *  interrupt flag. Only generated if Form Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_MsgErrorIsr(void) 
    {
        /* Clear Form Error flag */
        CAN_1_INT_SR_REG = CAN_1_FORM_ERROR_MASK;

        /* `#START MESSAGE_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_MSG_ERROR_ISR_CALLBACK
            CAN_1_MsgErrorIsr_Callback();
        #endif /* CAN_1_MSG_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_FORM_ERR */


#if (CAN_1_CRC_ERR)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_CrcErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to CRC Error Interrupt. Clears CRC Error
    *  interrupt flag. Only generated if CRC Error Interrupt enable in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_CrcErrorIsr(void) 
    {
        /* Clear CRC Error flag */
        CAN_1_INT_SR_REG = CAN_1_CRC_ERROR_MASK;

        /* `#START CRC_ERROR_ISR` */

        /* `#END` */

        #ifdef CAN_1_CRC_ERROR_ISR_CALLBACK
            CAN_1_CrcErrorIsr_Callback();
        #endif /* CAN_1_CRC_ERROR_ISR_CALLBACK */
    }
#endif /* CAN_1_CRC_ERR */


#if (CAN_1_BUS_OFF)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_BusOffIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Bus Off Interrupt. Places CAN Component
    *  to Stop mode. Only generated if Bus Off Interrupt enable in Customizer.
    *  Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void CAN_1_BusOffIsr(void) 
    {
        /* Clear Bus Off flag */
        CAN_1_INT_SR_REG = CAN_1_BUS_OFF_MASK;

        /* `#START BUS_OFF_ISR` */

        /* `#END` */

        #ifdef CAN_1_BUS_OFF_ISR_CALLBACK
            CAN_1_BusOffIsr_Callback();
        #endif /* CAN_1_BUS_OFF_ISR_CALLBACK */

        (void) CAN_1_Stop();
    }
#endif /* CAN_1_BUS_OFF */


#if (CAN_1_RX_MSG_LOST)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_MsgLostIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Message Lost Interrupt. Clears Message Lost
    *  interrupt flag. Only generated if Message Lost Interrupt enable in Customizer
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_MsgLostIsr(void) 
    {
        /* Clear Receive Message Lost flag */
        CAN_1_INT_SR_REG = CAN_1_RX_MSG_LOST_MASK;

        /* `#START MESSAGE_LOST_ISR` */

        /* `#END` */

        #ifdef CAN_1_MSG_LOST_ISR_CALLBACK
            CAN_1_MsgLostIsr_Callback();
        #endif /* CAN_1_MSG_LOST_ISR_CALLBACK */
    }
#endif /* CAN_1_RX_MSG_LOST */


#if (CAN_1_TX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_MsgTXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Transmit Message Interrupt. Clears Transmit
    *  Message interrupt flag. Only generated if Transmit Message Interrupt enable
    *  in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Reentrant:
    *  Depends on Customer code.
    *
    *******************************************************************************/
    void CAN_1_MsgTXIsr(void) 
    {
        /* Clear Transmit Message flag */
        CAN_1_INT_SR_REG = CAN_1_TX_MESSAGE_MASK;

        /* `#START MESSAGE_TRANSMITTED_ISR` */

        /* `#END` */

        #ifdef CAN_1_MSG_TX_ISR_CALLBACK
            CAN_1_MsgTXIsr_Callback();
        #endif /* CAN_1_MSG_TX_ISR_CALLBACK */
    }
#endif /* CAN_1_TX_MESSAGE */


#if (CAN_1_RX_MESSAGE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_MsgRXIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to Receive Message Interrupt. Clears Receive
    *  Message interrupt flag and call appropriate handlers for Basic and Full
    *  interrupt based mailboxes. Only generated if Receive Message Interrupt
    *  enable in Customizer. Recommended setting to enable this interrupt.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CAN_1_MsgRXIsr(void) 
    {
        uint8 mailboxNumber;
        uint16 shift = 0x01u;

        /* Clear Receive Message flag */
        CAN_1_INT_SR_REG = CAN_1_RX_MESSAGE_MASK;

        /* `#START MESSAGE_RECEIVE_ISR` */

        /* `#END` */

        #ifdef CAN_1_MSG_RX_ISR_CALLBACK
            CAN_1_MsgRXIsr_Callback();
        #endif /* CAN_1_MSG_RX_ISR_CALLBACK */

        for (mailboxNumber = 0u; mailboxNumber < CAN_1_NUMBER_OF_RX_MAILBOXES; mailboxNumber++)
        {

            if ((CAN_1_BUF_SR_REG & shift) != 0u)
            {
                if ((CAN_1_RX_CMD_REG(mailboxNumber) & CAN_1_RX_INT_ENABLE_MASK) != 0u)
                {
                    if ((CAN_1_RX_MAILBOX_TYPE & shift) != 0u)
                    {
                        /* RX Full mailboxes handler */
                    }
                    else
                    {
                        /* RX Basic mailbox handler */
                        CAN_1_ReceiveMsg(mailboxNumber);
                    }
                }
            }
            shift <<= 1u;
        }
    }
#endif /* CAN_1_RX_MESSAGE */


#if (CAN_1_RTR_AUTO_MSG_SENT)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_RtrAutoMsgSentIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is entry point to the RTR automatic message sent Interrupt.
    *  It is only generated if RTR message sent Interrupt is enabled in Customizer.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void CAN_1_RtrAutoMsgSentIsr(void)
    {
        /* Clear RTR auto-reply message sent flag */
        CAN_1_INT_SR_REG = CAN_1_RTR_MSG_MASK;

        /* `#START RTR_AUTO_MSG_SENT_ISR` */

        /* `#END` */

        #ifdef CAN_1_RTR_AUTO_MSG_SENT_ISR_CALLBACK
            CAN_1_RtrAutoMsgSentIsr_Callback();
        #endif /* CAN_1_RTR_AUTO_MSG_SENT_ISR_CALLBACK */
    }
#endif /* CAN_1_RTR_AUTO_MSG_SENT */


#if (CAN_1_STUCK_AT_ZERO)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_StuckAtZeroIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to the stuck at dominant bit Interrupt.
    *  It is only generated if stuck at zero Interrupt is enabled in Customizer.
    *  Enabling this interrupt is recommended.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Stops CAN component operation.
    *
    *******************************************************************************/
    void CAN_1_StuckAtZeroIsr(void)
    {
        /* Clear Stuck at dominant error flag */
        CAN_1_INT_SR_REG = CAN_1_STUCK_AT_ZERO_MASK;

        /* `#START STUCK_AT_ZERO_ISR` */

        /* `#END` */

        #ifdef CAN_1_STUCK_AT_ZERO_ISR_CALLBACK
            CAN_1_StuckAtZeroIsr_Callback();
        #endif /* CAN_1_STUCK_AT_ZERO_ISR_CALLBACK */

        (void) CAN_1_Stop();
    }
#endif /* CAN_1_STUCK_AT_ZERO */


#if (CAN_1_SST_FAILURE)
    /*******************************************************************************
    * FUNCTION NAME:   CAN_1_SSTErrorIsr
    ********************************************************************************
    *
    * Summary:
    *  This function is the entry point to the single shot transmission error
    *  Interrupt. It is only generated if the single shot transmission Interrupt
    *  is enabled in Customizer. Generated when the mailbox set for single shot
    *  transmission experienced an arbitration loss or a bus error during
    *  transmission.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Removes message that failed SST transmission from the Tx mailbox.
    *
    *******************************************************************************/
    void CAN_1_SSTErrorIsr(void)
    {
        uint8 i;

        /* Clear Single shot transmission failure flag */
        CAN_1_INT_SR_REG = CAN_1_SST_FAILURE_MASK;

        /* `#START SST_FAILURE_ISR_PRE` */

        /* `#END` */

        #ifdef CAN_1_SST_ERROR_ISR_PRE_CALLBACK
            CAN_1_SSTErrorIsr_Pre_Callback();
        #endif /* CAN_1_SST_ERROR_ISR_PRE_CALLBACK */

        /* Removes message that failed SST transmission from the Tx mailbox */
        for (i = 0u; i < CAN_1_NUMBER_OF_TX_MAILBOXES; i++)
        {
            if ((CAN_1_TX_CMD_REG(i) & CAN_1_TX_ABORT_MASK) != 0u)
            {
                CAN_1_TX_CMD_REG(i) = (CAN_1_TX_CMD_REG(i) & (uint32) (~(uint32) CAN_1_TX_TRANSMIT_REQUEST)) |
                                    CAN_1_TX_ABORT_MASK;
            }
        }

        /* `#START SST_FAILURE_ISR_POST` */

        /* `#END` */

        #ifdef CAN_1_SST_ERROR_ISR_POST_CALLBACK
            CAN_1_SSTErrorIsr_Post_Callback();
        #endif /* CAN_1_SST_ERROR_ISR_POST_CALLBACK */
    }
#endif /* CAN_1_SST_FAILURE */


/*******************************************************************************
* Function Name: CAN_1_ISR
********************************************************************************
*
* Summary:
*  This ISR is executed when CAN Core generates and interrupt on one of events:
*  Arb_lost, Overload, Bit_err, Stuff_err, Ack_err, Form_err, Crc_err,
*  Buss_off, Rx_msg_lost, Tx_msg or Rx_msg. The interrupt sources depends
*  on the Customizer inputs.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
CY_ISR(CAN_1_ISR)
{
    #ifdef CAN_1_ISR_INTERRUPT_CALLBACK
        CAN_1_ISR_InterruptCallback();
    #endif /* CAN_1_ISR_INTERRUPT_CALLBACK */
    
    /* Place your Interrupt code here. */
    /* `#START CAN_ISR` */

    /* `#END` */
    
    /* Arbitration */
    #if (CAN_1_ARB_LOST && (CAN_1_ARB_LOST_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_ARBITRATION_LOST_MASK) != 0u)
        {
            CAN_1_ArbLostIsr();
        }
    #endif /* CAN_1_ARB_LOST && CAN_1_ARB_LOST_USE_HELPER */

    /* Overload Error */
    #if (CAN_1_OVERLOAD && (CAN_1_OVERLOAD_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_OVERLOAD_ERROR_MASK) != 0u)
        {
            CAN_1_OvrLdErrorIsr();
        }
    #endif /* CAN_1_OVERLOAD && CAN_1_OVERLOAD_USE_HELPER */

    /* Bit Error */
    #if (CAN_1_BIT_ERR && (CAN_1_BIT_ERR_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_BIT_ERROR_MASK) != 0u)
        {
            CAN_1_BitErrorIsr();
        }
    #endif /* CAN_1_BIT_ERR && CAN_1_BIT_ERR_USE_HELPER */

    /* Bit Staff Error */
    #if (CAN_1_STUFF_ERR && (CAN_1_STUFF_ERR_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_STUFF_ERROR_MASK) != 0u)
        {
            CAN_1_BitStuffErrorIsr();
        }
    #endif /* CAN_1_STUFF_ERR && CAN_1_STUFF_ERR_USE_HELPER */

    /* ACK Error */
    #if (CAN_1_ACK_ERR && (CAN_1_ACK_ERR_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_ACK_ERROR_MASK) != 0u)
        {
            CAN_1_AckErrorIsr();
        }
    #endif /* CAN_1_ACK_ERR && CAN_1_ACK_ERR_USE_HELPER */

    /* Form(msg) Error */
    #if (CAN_1_FORM_ERR && (CAN_1_FORM_ERR_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_FORM_ERROR_MASK) != 0u)
        {
            CAN_1_MsgErrorIsr();
        }
    #endif /* CAN_1_FORM_ERR && CAN_1_FORM_ERR_USE_HELPER */

    /* CRC Error */
    #if (CAN_1_CRC_ERR && (CAN_1_CRC_ERR_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_CRC_ERROR_MASK) != 0u)
        {
            CAN_1_CrcErrorIsr();
        }
    #endif /* CAN_1_CRC_ERR && CAN_1_CRC_ERR_USE_HELPER */

    /* Bus Off state */
    #if (CAN_1_BUS_OFF && (CAN_1_BUS_OFF_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_BUS_OFF_MASK) != 0u)
        {
            CAN_1_BusOffIsr();
        }
    #endif /* CAN_1_BUS_OFF && CAN_1_BUS_OFF_USE_HELPER */

    /* Message Lost */
    #if (CAN_1_RX_MSG_LOST && (CAN_1_RX_MSG_LOST_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_RX_MSG_LOST_MASK) != 0u)
        {
            CAN_1_MsgLostIsr();
        }
    #endif /* CAN_1_RX_MSG_LOST && CAN_1_RX_MSG_LOST_USE_HELPER */

    /* TX Message Send */
    #if (CAN_1_TX_MESSAGE && (CAN_1_TX_MESSAGE_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_TX_MESSAGE_MASK) != 0u)
        {
            CAN_1_MsgTXIsr();
        }
    #endif /* CAN_1_TX_MESSAGE && CAN_1_TX_MESSAGE_USE_HELPER */

    /* RX Message Available */
    #if (CAN_1_RX_MESSAGE && (CAN_1_RX_MESSAGE_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_RX_MESSAGE_MASK) != 0u)
        {
            CAN_1_MsgRXIsr();
        }
    #endif /* CAN_1_RX_MESSAGE && CAN_1_RX_MESSAGE_USE_HELPER */

    /* RTR Auto-reply Message Sent */
    #if (CAN_1_RTR_AUTO_MSG_SENT && (CAN_1_RTR_MESSAGE_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_RTR_MSG_MASK) != 0u)
        {
            CAN_1_RtrAutoMsgSentIsr();
        }
    #endif /* CAN_1_RTR_AUTO_MSG_SENT && CAN_1_RTR_MESSAGE_USE_HELPER */

    /* Stuck at dominant error */
    #if (CAN_1_STUCK_AT_ZERO && (CAN_1_STUCK_AT_ZERO_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_STUCK_AT_ZERO_MASK) != 0u)
        {
            CAN_1_StuckAtZeroIsr();
        }
    #endif /* CAN_1_STUCK_AT_ZERO && CAN_1_STUCK_AT_ZERO_USE_HELPER */

    /* Single shot transmission failure */
    #if (CAN_1_SST_FAILURE && (CAN_1_SST_FAILURE_USE_HELPER || \
        (!CAN_1_ADVANCED_INTERRUPT_CFG)))
        if ((CAN_1_INT_SR_REG & CAN_1_SST_FAILURE_MASK) != 0u)
        {
            CAN_1_SSTErrorIsr();
        }
    #endif /* CAN_1_SST_FAILURE && CAN_1_SST_FAILURE_USE_HELPER */
}


/* [] END OF FILE */
