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
/*
#include <project.h>

extern int32_t kPosition;
extern int32_t kIntegral;
extern int32_t kDerivative;
extern uint32_t kPPJR;
int8 flipEncoder = 1;
int16 final_angle = 0;
int i = 0;
int lastp = 0;

exter 
double ratio;
uint8 complete = 0;
uint8 maxV = 0;

void set_Position(int16 degrees) {


        int PWM = position_PID(degrees_to_tick(degrees));
        if(PWM > maxV){
            set_PWM(maxV);   
        } else if(PWM < -maxV) {
            set_PWM(-maxV);
        } else {
            set_PWM(PWM);   
        }
}

int degrees_to_tick(int16 degrees){
    int ticks = (int)((double)degrees * kPPJR/360);
    return(ticks);
}

int position_PID(int target){
    int16 current =  QuadDec_GetCounter() * flipEncoder;
    int p = target - current;
    if(p <= 5 && p >= -5) {
      return(0);
    }
    i = i + p;
    
    //integral clamp
    if ( i > 500) {
        i = 500;   
    }
    if ( i < -500) {
        i = -500;
    }
    
    int d = p - lastp;
    
    lastp = p;
    
    return (p*kPosition/10 + i*kIntegral/10 + d*kDerivative/10);
}
*/
/* [] END OF FILE */
