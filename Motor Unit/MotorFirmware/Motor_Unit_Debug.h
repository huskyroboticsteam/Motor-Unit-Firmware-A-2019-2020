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

/* [] END OF FILE */
#ifndef MOTOR_UNIT_DEBUG
    #define MOTOR_UNIT_DEBUG
        
    //Telemetry
    #define CAN_TELEM_SEND
    
    //Debug Setting
    #define ENABLE_DEBUG_UART
    
    //comment out things you don't want to see
    #ifdef ENABLE_DEBUG_UART
    /*#define PRINT_CAN_PACKET
    #define PRINT_LIMIT_SW_TRIGGER
    #define PRINT_MOTOR_ERROR
    #define PRINT_FSM_STATE_MODE
    #define PRINT_SET_PID_CONST
    #define PRINT_ENCODER_VALUE
    #define PRINT_PID_DEBUG
        */
    #define PRINT_MOTOR_ERROR
    #define PRINT_PWM_COMMAND
    
    #endif
    
    #define DEV_TEST
#endif