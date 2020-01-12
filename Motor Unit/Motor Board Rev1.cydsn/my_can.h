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
#ifndef MY_CAN_H
#define MY_CAN_H
    
    #include <project.h>
    
    //flags
    uint8 send_data = 1;
    uint8 model_req = 0;
    uint8 disable_limit = 0;
        
        //Status and Data Structs
    struct Can_data Can_rx_pwm, Can_rx_angle;
    struct Error stall;
    struct Error command_failed;
    struct Error invalid_arg;

    int mailbox = 0x000;
    uint8 emergency = 0;
    /* Global variables used to store configuration and data for BASIC CAN mailbox */
    CAN_DATA_BYTES_MSG data;
    CAN_TX_MSG message;
    
    
    
    
    void set_data(uint16 addr);
    void initialize_can_addr(void);
    void set_CAN_ID(uint32 priority);
    void CAN_Send_Encoder(void);
    void CAN_Send_Telemetry(void);
    void CAN_Send_Model(void);
    void CAN_Send_Error(uint8 code, uint8 param);
    
#endif

/* [] END OF FILE */
