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
#include "Motor_Unit_CAN.h"
#include "Motor_Unit_FSM.h"
#include "MotorDrive.h"

extern uint8_t motorUnitMode;
extern uint8_t motorUnitState;
extern int currentPWM;
extern const uint32 StripLights_CLUT[ ];

//Reads from CAN FIFO and changes the state and mode accordingly
void NextStateFromCAN(CANPacket *receivedPacket) {
    switch(ReadCAN(receivedPacket)){
                    case(ID_MOTOR_UNIT_MODE_SEL):
                        if(GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PWM) {
                            //<init stuff for PWM>
                            set_PWM(0,1,1);
                            motorUnitMode = MOTOR_UNIT_MODE_PWM;
                            motorUnitState = SET_PWM;
                        }
                        else if (GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PID) {
                            //<init stuff for PID>
                            set_PWM(0,1,1);
                            motorUnitMode = MOTOR_UNIT_MODE_PID;
                            motorUnitState = CALC_PID;
                        } else {
                            gotoUninitState();
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PWM_DIR_SET):
                        if(motorUnitMode == MOTOR_UNIT_MODE_PWM){
                            motorUnitState = SET_PWM;
                          /*  int32_t decodeData = 0;
                            for (int i = 0; i < 4; i++) 
                                {
                                    decodedData |= data[1 + i] << (8 * (3-i));
                                }*/
                            currentPWM = GetPWMFromPacket(receivedPacket);
                        } else {
                            motorUnitState = QUEUE_ERROR;
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PID_P_SET):
                        //Set Global P constant
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_I_SET):
                        //Set Global I constant
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_D_SET):
                        //Set Global D constant
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_POS_TGT_SET):
                        if(motorUnitMode == MOTOR_UNIT_MODE_PID ) {//&& PID values set
                            
                        } else {
                            motorUnitState = QUEUE_ERROR;
                        }
                        break;
                    /* 
                    case(ID_MOTOR_UNIT_ENC_PPJR_SET):
                        break;
                    
                    case(ID_MOTOR_UNIT_MAX_JNT_REV_SET):
                        break;
                    */
                    default://for 0xFF or any weird bugs
                        if(motorUnitState == MOTOR_UNIT_MODE_PID){ //need to check if values set;
                            motorUnitState = CALC_PID;
                        } else if( motorUnitState == MOTOR_UNIT_MODE_PWM){
                            motorUnitState = SEND_TELE;
                        } else {
                            motorUnitState = CHECK_CAN;
                        }
                        break;
                }
}