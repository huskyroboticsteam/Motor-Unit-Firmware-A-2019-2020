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
#include <project.h>
#include "PositionPID.h"
#include "MotorDrive.h"

extern int32_t kPosition;
extern int32_t kIntegral;
extern int32_t kDerivative;
extern uint32_t kPPJR;
extern int32_t currentPWM;
extern uint8_t ignoreLimSw;


int8 flipEncoder = 1;

int16 final_angle = 0;//needs to be reset upon mode change
int integral = 0;     //needs to be reset upon mode change
int lastPosition = 0; //needs to be reset upon mode change
int integralClamp = 500;

double ratio;
uint8 complete = 0;
uint16 maxV = 0xFFFF;

void SetPosition(int32 miliDegrees) {

        currentPWM = position_PID(MiliDegreesToTicks(miliDegrees));
        
        //Max Power clamp
        if(currentPWM > maxV){
            set_PWM(maxV, ignoreLimSw, Status_Reg_Switches_Read());   
        } else if(currentPWM < -maxV) {
            set_PWM(-maxV, ignoreLimSw, Status_Reg_Switches_Read());
        } else {
            set_PWM(currentPWM, ignoreLimSw, Status_Reg_Switches_Read());   
        }
}

int MiliDegreesToTicks(int32_t miliDegrees){
    int ticks = (int)((float)miliDegrees * (float)kPPJR/(float)(360*1000));// make float

    return(ticks);
}

int position_PID(int target){
    int16 current =  QuadDec_GetCounter();
    int position = target - current;
    
    //if within tolerance exit
    if(position <= 5 && position >= -5) {
      return(0);
    }
    
    integral = integral + position;
    
    //integral clamp
    if (integral > integralClamp) {
        integral = integralClamp;   
    }
    if (integral < -integralClamp) {
        integral = -integralClamp;
    }
    
    int derivative = position - lastPosition;
    
    lastPosition = position;
    
    return (position*kPosition + integral*kIntegral + derivative*kDerivative);
}

/* [] END OF FILE */
