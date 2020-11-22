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
#include "../CANLib/CANLibrary.h"
#include "main.h"
#include "Motor_Unit_CAN.h"
#include "Motor_Unit_FSM.h"
#include "MotorDrive.h"
#include "PositionPID.h"

#ifdef RGB_LED_ARRAY
#include "LED_Array.h"
extern const uint32 StripLights_CLUT[ ];
#endif



extern int16_t nextPWM;
extern int32_t millidegreeTarget;

//Reads from CAN FIFO and changes the state and mode accordingly
void NextStateFromCAN(CANPacket *receivedPacket) {
    uint8_t packageID = ReadCAN(receivedPacket);
    switch(packageID){
                    case(ID_MOTOR_UNIT_MODE_SEL):
                        if(GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PWM) {
                            //<init stuff for PWM>
                            #ifdef RGB_LED_ARRAY
                            StripLights_MemClear(StripLights_BLACK);
                            StripLights_Pixel(0, 0, get_color_packet(0,0,255));
                            StripLights_Trigger(1);
                            #endif
                            set_PWM(0,1,1);
                            SetModeTo(MOTOR_UNIT_MODE_PWM);
                            SetStateTo(CHECK_CAN);
                        }
                        else if (GetModeFromPacket(receivedPacket) == MOTOR_UNIT_MODE_PID) {
                            //<init stuff for PID>
                            #ifdef RGB_LED_ARRAY
                            StripLights_MemClear(StripLights_BLACK);
                            StripLights_Pixel(1, 0, get_color_packet(0,0,255));
                            StripLights_Trigger(1);
                            #endif
                            set_PWM(0,1,1);
                            SetModeTo(MOTOR_UNIT_MODE_PID);
                            SetStateTo(CHECK_CAN);
                        } else {
                            GotoUninitState();
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PWM_DIR_SET):
                        if(GetMode() == MOTOR_UNIT_MODE_PWM){
                            SetStateTo(SET_PWM);
                            nextPWM = GetPWMFromPacket(receivedPacket);
                        } else {
                            SetStateTo(QUEUE_ERROR);
                            DisplayErrorCode(1);
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PID_P_SET):
                        SetkPosition(GetPFromPacket(receivedPacket));
                        PositionConstIsSet();
                        SetStateTo(CHECK_CAN);
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_I_SET):
                        SetkIntegral(GetIFromPacket(receivedPacket));
                        IntegralConstIsSet();
                        SetStateTo(CHECK_CAN);
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_D_SET):
                        SetkDerivative(GetDFromPacket(receivedPacket));
                        DerivativeConstIsSet();
                        SetStateTo(CHECK_CAN);
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_POS_TGT_SET):
                        if(GetMode() == MOTOR_UNIT_MODE_PID && PIDconstsSet() ) {//&& PID values set
                            millidegreeTarget = GetPIDTargetFromPacket(receivedPacket);
                            SetStateTo(CALC_PID);
                        } else {
                            SetStateTo(QUEUE_ERROR);
                            DisplayErrorCode(1);
                        }
                        break;
                     
                    case(ID_MOTOR_UNIT_ENC_PPJR_SET):
                        SetkPPJR(GetEncoderPPJRFromPacket(receivedPacket));
                        PPJRConstIsSet();
                        SetStateTo(CHECK_CAN);
                        break;
                    /*
                    case(ID_MOTOR_UNIT_MAX_JNT_REV_SET):
                        break;
                    */
                    default://for 0xFF/no packets or Non recognized Packets
                        
                        if(GetState() == MOTOR_UNIT_MODE_PID){ //need to check if values set;
                            SetStateTo(CALC_PID);
                        } else if(GetState() == MOTOR_UNIT_MODE_PWM){ //skips PWM state to not reset saftey timer
                            SetStateTo(CHECK_CAN);
                        } else {
                            SetStateTo(CHECK_CAN);
                        }
                        
                        //recieved Packet with Non Valid ID
                        if(packageID != 0xFF) {
                            DisplayErrorCode(0);
                        }
                        break;
                }
}