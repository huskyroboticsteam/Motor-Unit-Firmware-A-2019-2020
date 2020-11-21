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
#ifndef MOTOR_UNIT_FSM_H
    #define MOTOR_UNIT_FSM_H
    #include <project.h>
    
    void GotoUninitState();
    
    void PositionConstIsSet();
    void IntegralConstIsSet();
    void DerivativeConstIsSet();
    void PPJRConstIsSet();
    void MaxJointRevIsSet();
    uint8_t PIDconstsSet();
    void ClearPIDconst();
    
#endif