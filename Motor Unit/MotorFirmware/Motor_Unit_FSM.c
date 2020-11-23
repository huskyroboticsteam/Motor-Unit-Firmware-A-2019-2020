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
#include "Motor_Unit_FSM.h"
#include "MotorDrive.h"
#include "project.h"
#include "PositionPID.h"

/*drive mode
0xFF = un-init
0x0 = pwm
0x1 = PID*/
uint8_t motorUnitMode   = 0xFF;
uint8_t motorUnitState  = UNINIT;
uint8_t PIDConstSetReg      = 0;

extern const uint32 StripLights_CLUT[ ];

void GotoUninitState() {
    //halt motor
    #ifdef RGB_LED_ARRAY
    StripLights_DisplayClear(StripLights_BLACK);
    #endif
    ClearPIDProgress();
    motorUnitMode = 0xFF;
    motorUnitState = UNINIT;
}
void SetStateTo(uint8_t state) {
    motorUnitState = state;
}
void SetModeTo(uint8_t mode) {
    motorUnitMode = mode;
}
uint8_t GetState(){
    return motorUnitState;
}
uint8_t GetMode(){
    return motorUnitMode;
}
void PositionConstIsSet() {
    PIDConstSetReg |= 0b100;
}

void IntegralConstIsSet(){
    PIDConstSetReg |= 0b10;
}

void DerivativeConstIsSet(){
    PIDConstSetReg |= 0b1;
}

void PPJRConstIsSet() {
    PIDConstSetReg |= 0b1000;
}

void MaxJointRevIsSet(){
}

//return 1 if all PID const are set. Return 0 if not
uint8_t PIDconstsSet(){
    return PIDConstSetReg == 0b1111; 
}

void ClearPIDconst() {
    PIDConstSetReg = 0;
}