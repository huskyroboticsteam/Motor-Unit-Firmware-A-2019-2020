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
//#include "cyapicallbacks.h"
#include <project.h>
#include <stdio.h>
#include "main.h"
#include <stdint.h>
#include "MotorDrive.h"

uint8_t invalidate = 0;
extern char txData[TX_DATA_SIZE];

int32_t currentPWM = 0;


void set_PWM(int16_t compare, uint8_t disable_limit, uint8 limitSW) {
    #ifdef PRINT_PWM_COMMAND
    sprintf(txData, "PWM:%d disable_limit: %d\r\n",compare,disable_limit);
    UART_UartPutString(txData); 
    #endif
    
    invalidate = 0;
    if (compare < 0 && (!(limitSW & 0b01) || disable_limit) ) {
        Pin_Direction_Write(0);
        currentPWM = compare;
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && (!(limitSW & 0b10) || disable_limit) ){
        Pin_Direction_Write(1);
        currentPWM = compare;
        PWM_Motor_WriteCompare(compare);
    } else {
        currentPWM = 0;
        PWM_Motor_WriteCompare(0);
    }
}

int16_t GetCurrentPWM() {
    return currentPWM;
}
/* [] END OF FILE */
