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
#ifndef PID_H
#define PID_H
    #include <project.h>
    
    int8 flipEncoder;
    static int integral;
    int lastp;
    int kp;
    int ki;
    int kd;
    double ratio;
    uint8 complete;
    uint8 maxV;
    uint8 lastFinalPos;
    
    void initPID();
    
   
    
#endif //PID_H

/* [] END OF FILE */
