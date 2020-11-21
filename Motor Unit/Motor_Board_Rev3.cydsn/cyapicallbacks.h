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
    #include "project.h"
    #include "../CANLib/CANLibrary.h"
    
    //States in FSM
    #define UNINIT          0xFF
    #define SET_PWM         0x0
    #define CALC_PID        0x1
    #define SEND_TELE       0x2
    #define CHECK_CAN       0x3
    #define QUEUE_ERROR     0x4
        
        
    #define LED_ON  0
    #define LED_OFF 1
    
    //#defines for Revs
    #define MOTOR_REV1
    
    #ifdef MOTOR_REV1
    #endif
    
    #ifdef MOTOR_REV2
    #endif
    
    #ifdef MOTOR_REV3
        #define DEBUG_LEDS
        #define RGB_LED_ARRAY
    #endif
    



    #define TX_DATA_SIZE            (100u)

    #define CHIP_TYPE CHIP_TYPE_PSOC_CY8C4248AZI_L485
    //void check_Pin(void);
        struct Error
        {
            uint8 code, param, done;  
        };
        
        void Initialize(void);
    void PrintCanPacket(CANPacket receivedPacket);
    uint8_t ReadCAN(CANPacket *receivedPacket);
    void DisplayErrorCode(uint8_t code);

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
