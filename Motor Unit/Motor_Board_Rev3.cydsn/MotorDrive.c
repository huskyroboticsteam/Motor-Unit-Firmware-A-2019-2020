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
#include <project.h>
#include "cyapicallbacks.h"
#include <stdio.h>
#include "MotorDrive.h"

extern uint8 invalidate;
extern char8 txData[TX_DATA_SIZE];


//uint8 limitSW = Status_Reg_Switches_Read();


void set_PWM(int32_t compare, uint8_t disable_limit, uint8 limitSW) {

    sprintf(txData, "PWM:%d disable_limit: %d\r\n",compare,disable_limit);
   // UART_UartPutString(txData); 

    invalidate = 0;
    
    //16bit clamp
    if (compare < -65535 || compare > 65535) { return; }
    if (compare < 0 && (!(limitSW & 0b01) || disable_limit) ) {
        Pin_Direction_Write(0);
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && (!(limitSW & 0b10) || disable_limit) ){
        Pin_Direction_Write(1);
        PWM_Motor_WriteCompare(compare);
    } else {
        PWM_Motor_WriteCompare(0);
    }
}
/* [] END OF FILE */