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
#ifndef CYAPICALLBACKS_H
    #define CYAPICALLBACKS_H
    #define CHIP_TYPE CHIP_TYPE_PSOC_CY8C4248AZI_L485
    
    //Specifies Revision
    #define MOTOR_REV3
    
    //Telemetry
    #define CAN_TELEM_SEND
    
    //Debug Setting
    #define ENABLE_DEBUG_UART
    
    //comment out things you don't want to see
    #ifdef ENABLE_DEBUG_UART
    //#define PRINT_CAN_PACKET
    //#define PRINT_LIMIT_SW_TRIGGER
    //#define PRINT_MOTOR_ERROR
    //#define PRINT_FSM_STATE_MODE
    //#define PRINT_SET_PID_CONST
    #define PRINT_PWM_COMMAND
    #endif
    
    #define DEV_TEST

#endif /* CYAPICALLBACKS_H */   
/* [] */
