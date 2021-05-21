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
#include <project.h>
void SetPosition(int32 miliDegrees) ;
int32_t MiliDegreesToTicks(int32_t miliDegrees);
int32_t Position_PID(int32 targetTick);
int32_t CurrentPositionMiliDegree();

void SetkPosition(int32_t kP);
void SetkIntegral(int32_t kI);
void SetkDerivative(int32_t kD);
void SetkPPJR(uint32_t kppjr);

//used for mode change 
void ClearPIDProgress();
void InitializePID();

void DisablePID();
void EnablePID();
uint8_t PIDIsEnabled();

int32_t GetEncoderValWithFlip();
void SetEncoderDirDefault();
void SetEncoderDirReverse();
void SetMaxPIDPWM(uint16_t setValue);
int32_t GetMaxPIDPWM();

int32_t GetkPosition();
int32_t GetkIntegral();
int32_t GetkDerivative();
uint32_t GetkPPJR();//pulses per joint revolution