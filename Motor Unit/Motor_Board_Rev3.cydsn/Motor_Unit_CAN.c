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
#include "LED_Array.h"

extern uint8_t motorUnitMode;
extern uint8_t motorUnitState;
extern int currentPWM;
extern const uint32 StripLights_CLUT[ ];
extern int32_t kPosition;
extern int32_t kIntegral;
extern int32_t kDerivative;
extern uint32_t kPPJR;
extern int32_t millidegreeTarget;

//Reads from CAN FIFO and changes the state and mode accordingly
void NextStateFromCAN(CANPacket *receivedPacket) {
    switch(ReadCAN(receivedPacket)){
                    case(ID_MOTOR_UNIT_MODE_SEL):
                        if(GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PWM) {
                            //<init stuff for PWM>
                            #ifdef RGB_LED_ARRAY
                            StripLights_MemClear(StripLights_BLACK);
                            StripLights_Pixel(0, 0, get_color_packet(0,0,255));
                            StripLights_Trigger(1);
                            #endif
                            set_PWM(0,1,1);
                            motorUnitMode = MOTOR_UNIT_MODE_PWM;
                            motorUnitState = SEND_TELE;
                        }
                        else if (GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PID) {
                            //<init stuff for PID>
                            #ifdef RGB_LED_ARRAY
                            StripLights_MemClear(StripLights_BLACK);
                            StripLights_Pixel(1, 0, get_color_packet(0,0,255));
                            StripLights_Trigger(1);
                            #endif
                            set_PWM(0,1,1);
                            motorUnitMode = MOTOR_UNIT_MODE_PID;
                            motorUnitState = SEND_TELE;
                        } else {
                            GotoUninitState();
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PWM_DIR_SET):
                        if(motorUnitMode == MOTOR_UNIT_MODE_PWM){
                            motorUnitState = SET_PWM;
                            currentPWM = GetPWMFromPacket(receivedPacket);
                        } else {
                            motorUnitState = QUEUE_ERROR;
                            DisplayErrorCode(1);
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PID_P_SET):
                        kPosition = GetPFromPacket(receivedPacket);
                        PositionConstIsSet();
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_I_SET):
                        kIntegral = GetIFromPacket(receivedPacket);
                        IntegralConstIsSet();
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_D_SET):
                        kDerivative = GetDFromPacket(receivedPacket);
                        DerivativeConstIsSet();
                        motorUnitState = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_POS_TGT_SET):
                        if(motorUnitMode == MOTOR_UNIT_MODE_PID && PIDconstsSet() ) {//&& PID values set
                            millidegreeTarget = GetPIDTargetFromPacket(receivedPacket);
                            motorUnitState = CALC_PID;
                        } else {
                            motorUnitState = QUEUE_ERROR;
                            DisplayErrorCode(1);
                        }
                        break;
                     
                    case(ID_MOTOR_UNIT_ENC_PPJR_SET):
                        kPPJR = GetEncoderPPJRFromPacket(receivedPacket);
                        PPJRConstIsSet();
                        motorUnitState = SEND_TELE;
                        break;
                    /*
                    case(ID_MOTOR_UNIT_MAX_JNT_REV_SET):
                        break;
                    */
                    default://for 0xFF/no packets or Non recognized Packets
                        
                        if(motorUnitState == MOTOR_UNIT_MODE_PID){ //need to check if values set;
                            motorUnitState = CALC_PID;
                        } else if( motorUnitState == MOTOR_UNIT_MODE_PWM){ //skips PWM state to not reset saftey timer
                            motorUnitState = SEND_TELE;
                        } else {
                            motorUnitState = CHECK_CAN;
                        }
                        
                        //recieved Packet with Non Valid ID
                        if(receivedPacket->data[0] != 0xFF) {
                            DisplayErrorCode(0);
                        }
                        break;
                }
}