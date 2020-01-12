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


    
//void check_Pin(void);
    struct Can_data 
    {
        uint8 b0,b1,b2,b3,b4,done;
    };
    struct Error
    {
        uint8 code,param,done;  
    };
void initialize_can_addr(void);
void set_CAN_ID(uint32 priority);
void set_data(uint16 addr);
void CAN_Send_Encoder(void);
void CAN_Send_Telemetry(void);
void CAN_Send_Model(void);
void CAN_Send_Error(uint8 code, uint8 param);
void initialize(void);
int encoder(void);
void emergency_Stop(void);
void initialize(void);
uint32 pot_Read(void);
void set_PWM(int period);
int degrees_to_tick(int16 degrees);
int position_PID(int target);
void set_Position(int16 degrees);
void set_Speed(int current_spd, int speed);


    /*Define your macro callbacks here */
    /*For more information, refer to the Writing Code topic in the PSoC Creator Help.*/

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
