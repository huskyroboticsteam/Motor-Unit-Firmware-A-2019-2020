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

int32_t kPosition = 0;
int32_t kIntegral = 0;
int32_t kDerivative = 0;
uint32_t kPPJR = 0;
extern int16_t nextPWM;
extern uint8_t ignoreLimSw;


int8 flipEncoder = 1;

int16 final_angle = 0;//needs to be reset upon mode change
int integral = 0;     //needs to be reset upon mode change
int lastPosition = 0; //needs to be reset upon mode change
int integralClamp = 500;

double ratio;
uint8 complete = 0;
uint16 maxV = 0xFFFF;

void SetkPosition(int32_t kP){
    kPosition = kP;
}
void SetkIntegral(int32_t kI){
    kIntegral = kI;
}
void SetkDerivative(int32_t kD){
    kDerivative = kD;
}
void SetkPPJR(uint32_t kppjr){
    kPPJR = kppjr;
}

int32_t GetkPosition(){
    return kPosition;
}
int32_t GetkIntegral(){
    return kIntegral;
}
int32_t GetkDerivative(){
    return kDerivative;
}
uint32_t GetkPPJR(){
    return kPPJR;
}

void SetPosition(int32 miliDegrees) {

        nextPWM = Position_PID(MiliDegreesToTicks(miliDegrees));
        
        //Max Power clamp
        if(nextPWM > maxV){
            set_PWM(maxV, ignoreLimSw, Status_Reg_Switches_Read());   
        } else if(nextPWM < -maxV) {
            set_PWM(-maxV, ignoreLimSw, Status_Reg_Switches_Read());
        } else {
            set_PWM(nextPWM, ignoreLimSw, Status_Reg_Switches_Read());   
        }
}

int MiliDegreesToTicks(int32_t miliDegrees){
    int ticks = (int)((float)miliDegrees * (float)kPPJR/(float)(360*1000));// make float

    return(ticks);
}

int Position_PID(int target){
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
