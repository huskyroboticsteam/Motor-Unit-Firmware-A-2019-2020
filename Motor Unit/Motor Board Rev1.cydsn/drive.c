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
#include "drive.h"

    // takes between -255 and 255
void set_PWM(int compare) {
    invalidate = 0;
    if (compare < -255 || compare > 255) { return; }
    uint8 status = Status_Reg_Switches_Read();
    if (compare < 0 ) {
        if(!(status & 0b01) || disable_limit){
            Pin_Direction_Write(0);
            PWM_Motor_WriteCompare(-compare);
        }
    } else if (compare > 0 ){
        if(!(status & 0b10) || disable_limit) {
            Pin_Direction_Write(1);
            PWM_Motor_WriteCompare(compare);
        }
    } else {
        PWM_Motor_WriteCompare(0);   
    }
}


int degrees_to_tick(int degrees){
    int ticks = (int)((double)degrees * ratio);
    if(uart_debug) {
        sprintf(txData, "degree: %d ticks: %d\r\n", degrees, ticks);
        UART_UartPutString(txData);
    }
    return(ticks);
}

int position_PID(int target){
    int16 current =  QuadDec_GetCounter() * flipEncoder;
    int p = target - current;
    if(!p) {
      //complete =  1;
      return(0);
    }
    i = i + p;
    if ( i > 500) {
        i = 500;   
    }
    if ( i < -500) {
        i = -500;
    }
    int d = p - lastp;
    lastp = p;
    if(uart_debug) {
        sprintf(txData, "p: %d, i: %d d %d current %d\r\n",p, i, d, current);
        UART_UartPutString(txData);
    }
    return (p*kp/10 + i*ki/10 + d*kd/10);
}