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
#ifndef CAN_MOTOR_TEST_MSG
#define CAN_MOTOR_TEST_MSG
    #include <stdio.h>
    #define UNINIT          0xFF
    #define CONSTRUCT_PWM   0x0
    #define CONSTRUCT_PID   0x1
    #define SEND_CAN        0x2
    #define READ_CAN        0x3
    #define MODE_SEL        0x4
    #define SEND_PACKET     0x5
    
    void InitializeMessage(void);
    uint8_t SelectModeMessage(void);
    uint8_t NeedToImplementMessage(void);
    uint8_t SetTargetSerial(void);
    int32_t SetMotorPWM(void);
    int32_t ReadNumberFromUART(void);
    void StoreUARTBufferToArray(char* buffer, uint8_t size);
    
#endif
/* [] END OF FILE */
