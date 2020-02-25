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

//PID varaibles
int8 flipEncoder = 1;
int16 final_angle = 0;
int i = 0;
int lastp = 0;
int kp;
int ki;
int kd;
double ratio;
uint8 complete = 0;
uint8 maxV = 0;

void set_Position(int16 degrees) {
    if(uart_debug) {
        sprintf(txData, "complete: %d\r\n",complete);
        UART_UartPutString(txData);
    }
    //while(!complete) {
        int PWM = position_PID(degrees_to_tick(degrees));
        if(uart_debug) {
            sprintf(txData, "PWM: %d\r\n",PWM);
            UART_UartPutString(txData);
        }
        if(PWM > maxV){
            set_PWM(maxV);   
        } else if(PWM < -maxV) {
            set_PWM(-maxV);
        } else {
            set_PWM(PWM);   
        }
   // }
}

int degrees_to_tick(int16 degrees){
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
    if(p <= 5 && p >= -5) {
        if(uart_debug) {
            sprintf(txData, "p: %d\r\n",p);
            UART_UartPutString(txData);
        }
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
/* [] END OF FILE */
