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
#include "main.h"

int32_t kPosition = 0;
int32_t kIntegral = 0;
int32_t kDerivative = 0;
int32_t kPPJR = 0;
int32_t PWM = 0;
int32_t mDegMin = 0;
int32_t mDegMax = MDEG_PER_REV;
int32_t tickMin = 0;
int32_t tickMax = 0;

extern uint8_t ignoreLimSw;

extern char txData[TX_DATA_SIZE];
int8 flipEncoder = 1;
uint8_t usingPot = 0;

int integral = 0;     //needs to be reset upon mode change
int lastPosition = 0; //needs to be reset upon mode change
int integralClamp = 500;

double ratio;
uint8 complete = 0;
int32 maxPWM = 32767;

uint8_t enabledPID = 0;

void ClearPIDProgress() {
    integral = 0;
    lastPosition = 0;
}
void DisablePID() {
    enabledPID = 0;
}
void EnablePID() {
    enabledPID = 1;
}
uint8_t PIDIsEnabled() {
    return(enabledPID);
}
void InitializePID() {
    set_PWM(0, 0, 0);
    ClearPIDProgress();
    DisablePID();
    lastPosition = GetTicks();
}

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
uint32_t updatekPPJR() {
    if (mDegMin == mDegMax) return 0;
    kPPJR = MDEG_PER_REV*(tickMax-tickMin)/(mDegMax-mDegMin);
    return kPPJR
}

void SetMaxPIDPWM(uint16_t setValue){
    maxPWM = setValue;
}
int32_t GetMaxPIDPWM(){
    return maxPWM;
}

int32_t GetPotentiometerVal() {
    ADC_Pot_StartConvert();
    ADC_Pot_IsEndConversion(ADC_Pot_WAIT_FOR_RESULT);
    return ADC_Pot_GetResult16(0);
}
int32_t GetEncoderValWithFlip() {
    return flipEncoder * QuadDec_GetCounter();
}
void SetEncoderDirDefault(){
    flipEncoder = 1;
}
void SetEncoderDirReverse(){
    flipEncoder = -1;
}
int32_t GetTicks() {
    if (usingPot)
        return GetPotentiometerVal();
  
    return GetEncoderValWithFlip();
}
void SetPosition(int32 miliDegrees) {
        PWM = Position_PID(MiliDegreesToTicks(miliDegrees));
        
        //Max Power clamp
        if(PWM > GetMaxPIDPWM()){
            set_PWM(GetMaxPIDPWM(), ignoreLimSw, Status_Reg_Switches_Read());   
        } else if(PWM < -GetMaxPIDPWM()) {
            set_PWM(-GetMaxPIDPWM(), ignoreLimSw, Status_Reg_Switches_Read());
        } else {
            set_PWM(PWM, ignoreLimSw, Status_Reg_Switches_Read());   
        }
}
int32_t TicksToMiliDegrees(int32_t ticks){
    if(kPPJR == 0) return 0;
    
    return mDegMin + (ticks-tickMin) * MDEG_PER_REV / kPPJR;
}
int32_t MiliDegreesToTicks(int32_t miliDegrees){
    int32_t ticks = tickMin + (miliDegrees-mDegMin) * kPPJR / MDEG_PER_REV;// make float
    return ticks;
}

int32_t Position_PID(int32 targetTick){
    if(!PIDIsEnabled()){
        return(0);
    }
    //TODO: Make Potenitometer Compatible
    volatile int32 current =  GetTicks();
    int32 position = targetTick - current;
    
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
    int PWMOut = position*kPosition/10 + integral*kIntegral/10 + derivative*kDerivative/10;
    lastPosition = position;
    
    #ifdef PRINT_PID_DEBUG
        sprintf(txData,"c:%d, P:%d, I%d, D:%d, Out:%d", current, position, integral, derivative, PWMOut);
        UART_UartPutString(txData);   
    #endif
 
    return (PWMOut);
}

/* [] END OF FILE */
