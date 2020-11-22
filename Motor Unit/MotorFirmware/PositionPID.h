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
int MiliDegreesToTicks(int32_t miliDegrees);
int Position_PID(int target);

void SetkPosition(int32_t kP);
void SetkIntegral(int32_t kI);
void SetkDerivative(int32_t kD);
void SetkPPJR(uint32_t kppjr);

int32_t GetkPosition();
int32_t GetkIntegral();
int32_t GetkDerivative();
uint32_t GetkPPJR();//pulses per joint revolution