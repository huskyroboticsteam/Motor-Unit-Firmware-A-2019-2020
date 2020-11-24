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
#ifndef MAIN_HEADER
    #define MAIN_HEADER
    
    #include "../CANLib/CANLibrary.h"
    #include "cyapicallbacks.h"
    #include <stdint.h>
            
        #define LED_ON  0
        #define LED_OFF 1
        
        // Only 1 Rev Should be selected
        #ifdef MOTOR_REV1
        #define ERROR_LED
        #define CAN_LED
        #endif
        
        #ifdef MOTOR_REV2
        #define ERROR_LED
        #define CAN_LED
        #endif
        
        #ifdef MOTOR_REV3
        #define DEBUG_LED1
        #define DEBUG_LED2
        #define ERROR_LED
        #define CAN_LED
        #define RGB_LED_ARRAY
        #endif


        #define TX_DATA_SIZE            (100u)

        //void check_Pin(void);
            struct Error
            {
                uint8_t code, param, done;  
            };
            
            void Initialize(void);
            
        //debug tool for that prints packet to UART
        void PrintCanPacket(CANPacket receivedPacket);
        
        /*Returns the Packet ID or 0xFF if there is no Packet
        This pulls from the CAN lib's FIFO
        Also Triggers LED
        */
        uint16_t ReadCAN(CANPacket *receivedPacket);
        
        void DisplayErrorCode(uint8_t code);
        #define MOTOR_ERROR_INVALID_PACKET  0x0
        #define MOTOR_ERROR_WRONG_MODE      0x1

#endif
    
/* [] END OF FILE */
