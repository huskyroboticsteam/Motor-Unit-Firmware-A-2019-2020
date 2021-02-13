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
#define MODE_UNINIT 0xFF
#define MODE_PWM 0x0
#define MODE_PID 0x1


#include "project.h"
#include "../CANLib/CANLibrary.h"

#define TX_DATA_SIZE            (100u)

#define CHIP_TYPE CHIP_TYPE_PSOC_CY8C4248AZI_L485
//void check_Pin(void);
    struct Error
    {
        uint8 code, param, done;  
    };
    
void Initialize(void);

void PrintCanPacket(CANPacket receivedPacket);
void ReadCan(CANPacket *receivedPacket);

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
