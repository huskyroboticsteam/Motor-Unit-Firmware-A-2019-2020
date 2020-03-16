/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
/*
#include "Initialize_CAN_addr.h"

void initialize_can_addr(void) {
    CAN_RX_CFG canConfig;
    canConfig.rxamr |= 0b1 << 14 | 0xFFFF << 15;
    canConfig.rxacr |= Can_addr_Read() << 3 | 0x4 <<10;
    canConfig.rxcmd = 
    canConfig.rxmailbox = 0;
    
    uint8 Can_accept = CAN_RxBufConfig(&canConfig);
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %ld\r\n",setting, message_id);
        UART_UartPutString(txData); 
        sprintf(txData, "Can shift: %d   P0Mailbox: %d P1Mailbox %d\r\n",shift, CAN_RX_MAILBOX_0, CAN_RX_MAILBOX_1);
        UART_UartPutString(txData); 
        sprintf(txData, "disable_limit: %d\r\n",disable_limit);
        UART_UartPutString(txData); 
    }
}
    */
/* [] END OF FILE */
