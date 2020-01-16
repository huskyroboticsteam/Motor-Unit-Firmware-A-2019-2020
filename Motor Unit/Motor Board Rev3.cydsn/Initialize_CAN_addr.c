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
#include "Initialize_CAN_addr.h"
//Recieve:
//1 00010 10000 0x450 BBB to base rotation
//1 00010 10001 0x451 
//1 00010 10010 0x452
//1 00010 10011 0x453
//1 00010 10100 0x454
//1 00010 10101 0x455
//1 00010 10110 0x456
//Send:
//1 10000 00010 0x602 base rotation to BBB 
//1 10001 00010 0x622 shoulder to BBB
//1 10010 00010 0x642 elbow ""
//1 10011 00010 0x662 forearm rotation ""
//1 10100 00010 0x682 diff wrist 1 ""
//1 10101 00010 0x6A2 diff wrist 2 ""
//1 10110 00010 0x6C2 hand ""

void initialize_can_addr(void) {
    uint8 setting = Can_addr_Read();
    uint8 shift = 0;
    switch(Can_addr_Read()) {
        case 0b000: //Base rotation
            message_id = 0b10000;
            shift = 0;
            break;
        case 0b001: // shoulder
            message_id = 0b10001;
            shift = 1;
            break;
        case 0b010: // elbow
            message_id = 0b10010;
            shift = 2;
            break;
        case 0b011: // forearm rotation
            message_id = 0b10011;
            shift = 3;
            break;
        case 0b100: // diff wrist 1
            message_id = 0b10100;
            shift = 4;
            break;
        case 0b101: // diff wrist 2
            message_id = 0b10101;
            shift = 5;
            break;
        case 0b110: // hand
            message_id = 0b10110;
            shift = 6;
            break;
    }
    
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %ld\r\n",setting, message_id);
        UART_UartPutString(txData); 
        sprintf(txData, "Can shift: %d   P0Mailbox: %d P1Mailbox %d\r\n",shift, CAN_RX_MAILBOX_0, CAN_RX_MAILBOX_1);
        UART_UartPutString(txData); 
        sprintf(txData, "disable_limit: %d\r\n",disable_limit);
        UART_UartPutString(txData); 
    }
}
/* [] END OF FILE */
