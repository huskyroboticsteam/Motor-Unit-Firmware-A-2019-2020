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
#ifndef drive_H
#define drive_H
    
#include <project.h>
#include "global_var.h"
    
    //drive varaible
    int GEAR_RATIO;
    int pwm_compare;
    uint8 invalidate = 0;

    //PID varaibles
    int8 flipEncoder = 1;
    int i = 0;
    int lastp = 0;
    int kp = 50;
    int ki = 3;
    int kd = 10;
    double ratio;
    uint8 complete = 0;
    uint8 maxV = 0;
    uint8 lastFinalPos;
    
    void set_PWM(int period);
    int degrees_to_tick(int degrees);
    int position_PID(int target);
    void set_Position(int degrees);
    void set_Speed(int current_spd, int speed);
    
#endif

/* [] END OF FILE */
