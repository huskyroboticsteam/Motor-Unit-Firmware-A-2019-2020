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

/*drive mode
0xFF = un-init
0x0 = pwm
0x1 = PID*/
uint8_t motorUnitMode   = 0xFF;
uint8_t motorUnitState  = UNINIT;

extern const uint32 StripLights_CLUT[ ];

void gotoUninitState() {
    //halt motor
    StripLights_DisplayClear(StripLights_BLACK);
    motorUnitMode = 0xFF;
    motorUnitState = UNINIT;
}