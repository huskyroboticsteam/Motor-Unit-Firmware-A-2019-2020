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
#ifndef CYAPICALLBACKS_H
#define CYAPICALLBACKS_H

#include "project.h"

#define TX_DATA_SIZE            (100u)


//void check_Pin(void);
    struct Error
    {
        uint8 code, param, done;  
    };
    
void initialize(void);

    
#endif /* CYAPICALLBACKS_H */   
/* [] */
