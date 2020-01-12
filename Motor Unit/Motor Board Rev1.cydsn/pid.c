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
#include "pid.h"



void initPID()
{
    flipEncoder = 1;
    i    = 0;//change to integral
    int lastp = 0;
    int kp = 50;
    int ki = 3;
    int kd = 10;
    double ratio;
    complete = 0;
    maxV = 0;
    lastFinalPos;
}



/* [] END OF FILE */
