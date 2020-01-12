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
#ifndef global_var_H
#define global_var_H
    
        //CAN variables
    uint32 message_id = 0;
    #define MESSAGE_IDE             (0u)    /* Standard message */
    #define MESSAGE_IRQ             (0u)    /* No transmit IRQ */
    #define MESSAGE_RTR             (0u)    /* No RTR */
    uint16 CAN_RX_MAILBOX_1_SHIFT  = 0b1;
    uint32 CAN_RX_MAILBOX_0_SHIFT  = 0b10000000;
    uint16 CAN_RX_MAILBOX_1 = 0u;
    uint16 CAN_RX_MAILBOX_0 = 7u;
    int CAN_TIMEOUT;

    CY_ISR_PROTO(ISR_CAN);

    //Uart variables
    volatile uint8 uart_debug = 1;
    #define TX_DATA_SIZE            (100u)
    #define PWM_PERIOD = 255;
    char8 txData[TX_DATA_SIZE];


    //drive mode
    uint8 mode = 2;



    volatile uint8 drive = 0;

    
    
#endif

/* [] END OF FILE */
