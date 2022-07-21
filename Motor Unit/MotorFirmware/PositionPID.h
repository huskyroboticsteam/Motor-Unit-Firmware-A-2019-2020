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

#define MDEG_PER_REV 360000

void SetPosition(int32 miliDegrees);
int32_t MiliDegreesToTicks(int32_t miliDegrees);
int32_t Position_PID(int32 targetTick);
int32_t TicksToMiliDegrees(int32_t ticks);

void SetkPosition(int32_t kP);
void SetkIntegral(int32_t kI);
void SetkDerivative(int32_t kD);
void SetkPPJR(uint32_t kppjr);
uint32_t updatekPPJR();

int32_t getmDegMin();
int32_t getmDegMax();
int32_t getTickMin();
int32_t getTickMax();

//used for mode change 
void ClearPIDProgress();
void InitializePID();

void useEnc();
void usePot();
void setmDegMin(int32_t val);
void setmDegMax(int32_t val);
void setTickMin(int32_t val);
void setTickMax(int32_t val);
void DisablePID();
void EnablePID();
void SetEncoderDirDefault();
void SetEncoderDirReverse();
void SetMaxPIDPWM(uint16_t setValue);

uint8_t UsingPot();
uint8_t PIDIsEnabled();
int32_t GetkPosition();
int32_t GetkIntegral();
int32_t GetkDerivative();
uint32_t GetkPPJR();//pulses per joint revolution
int32_t GetMaxPIDPWM();

int32_t GetEncoderValWithFlip();
int32_t GetPosition();
int32_t GetPotVal();
int32_t GetTicks();