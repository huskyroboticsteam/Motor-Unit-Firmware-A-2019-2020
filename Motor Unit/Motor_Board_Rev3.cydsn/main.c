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
#include <project.h>
#include "cyapicallbacks.h"
#include <stdio.h>
#include <stdint.h>
//#include "../CANLib/CANLibrary.h"
#include "MotorDrive.h"
#include "LED_Array.h"

extern const uint32 StripLights_CLUT[ ];
//LED
uint8 CAN_time_LED = 0;

//Uart variables
char8 txData[TX_DATA_SIZE];

//drive varaible
uint8 invalidate = 0;

/*drive mode
0xFF = un-init
0x0 = pwm
0x1 = PID*/
volatile uint8 mode = 0xFF;
volatile uint8 address = 0;

//Status and Data Structs
volatile uint8 drive = 0;
uint8_t state = 0;//used for FSM
uint8_t CAN_check_delay = 0;


CY_ISR(Period_Reset_Handler) {
    int timer = Timer_1_ReadStatusRegister();
    invalidate++;
    CAN_time_LED++;
    CAN_check_delay ++;
    if(invalidate >= 20){
        set_PWM(0, 0, 0);   
    }
    if(CAN_time_LED >= 5){
        CAN_LED_Write(LED_OFF);
    }
}
  
CY_ISR(Pin_Limit_Handler){
   /* if(uart_debug) {
        sprintf(txData,"Limit interupt triggerd\r\n");
        UART_UartPutString(txData);
    }*/
    set_PWM(0, 0, 0);
    QuadDec_SetCounter(0);
}

int main(void)
{ 
    Initialize();
    StripLights_DisplayClear(StripLights_BLACK);
   // CyDelay(2000);
    CANPacket can_recieve;
    CANPacket can_send;
    volatile int error = 0;
    can_send.id = 0x5 << 6 | 0xf;
    can_send.dlc = 0x8;
    uint8_t test = 0;
    for(int i = 0; i < 8; i++) {
        can_send.data[i] = i;
    }
    can_send.data[0] = 1;
    for(;;)
    {
        switch(state) {
            case(UNINIT):
                //idle animation
                state = CHECK_CAN;
                break;
            case(SET_PWM):
                ReadCAN(&can_recieve);
                StripLights_MemClear(StripLights_BLACK);
                StripLights_Pixel(0, 0, get_color_packet(0,0,255));
                StripLights_Trigger(1);
                state = SEND_TELE;
                break;
            case(CALC_PID):
                ReadCAN(&can_recieve);
                StripLights_MemClear(StripLights_BLACK);
                StripLights_Pixel(1, 0, get_color_packet(0,0,255));
                StripLights_Trigger(1);
                state = SEND_TELE;
                break;
            case(SEND_TELE):
                SendCANPacket(&can_send);
                state = CHECK_CAN;
                break;
            case(QUEUE_ERROR):
                state = SEND_TELE;
                break;
            case(CHECK_CAN):
                switch(ReadCAN(&can_recieve)){
                    case(ID_MOTOR_UNIT_MODE_SEL):
                        if(GetModeFromPacket(&can_recieve) == MOTOR_UNIT_MODE_PWM) {
                            //<init stuff for PWM>
                            mode = MOTOR_UNIT_MODE_PWM;
                            state = SET_PWM;
                        }
                        else if (GetModeFromPacket(&can_recieve) == MOTOR_UNIT_MODE_PID) {
                            //<init stuff for PID>
                            mode = MOTOR_UNIT_MODE_PID;
                            state = CALC_PID;
                        } else {
                            StripLights_DisplayClear(StripLights_BLACK);
                            mode = 0xFF;
                            state = UNINIT;
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PWM_DIR_SET):
                        if(mode == MOTOR_UNIT_MODE_PWM){
                            state = SET_PWM;
                        } else {
                            state = QUEUE_ERROR;
                        }
                        break;
                        
                    case(ID_MOTOR_UNIT_PID_P_SET):
                        //Set Global P constant
                        state = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_I_SET):
                        //Set Global I constant
                        state = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_D_SET):
                        //Set Global D constant
                        state = SEND_TELE;
                        break;
                    
                    case(ID_MOTOR_UNIT_PID_POS_TGT_SET):
                        if(mode == MOTOR_UNIT_MODE_PID ) {//&& PID values set
                            
                        } else {
                            state = QUEUE_ERROR;
                        }
                        break;
                    /* 
                    case(ID_MOTOR_UNIT_ENC_PPJR_SET):
                        break;
                    
                    case(ID_MOTOR_UNIT_MAX_JNT_REV_SET):
                        break;
                    */
                    default:
                        if(mode == MOTOR_UNIT_MODE_PID){ //need to check if values set;
                            state = CALC_PID;
                        } else if( mode == MOTOR_UNIT_MODE_PWM){
                            state = SEND_TELE;
                        } else {
                            StripLights_DisplayClear(StripLights_BLACK);
                            mode = 0xFF;
                            state = UNINIT;
                        }
                        break;
                }
                //PrintCanPacket(can_recieve);
                sprintf(txData, "Mode: %x \r\n", mode);
               // UART_UartPutString(txData);
            default:
               /* StripLights_DisplayClear(StripLights_BLACK);
                state = UNINIT;
                mode = 0xFF;*/
                break;

        }
        sprintf(txData, "Mode: %x State:%x \r\n", mode, state);
        //UART_UartPutString(txData);

  

        
    }
}
 


void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    initalize_LEDs(LOW_LED_POWER);
    
    //display Dip Status
    address = Can_addr_Read();
    UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", address);
    UART_UartPutString(txData);
    ERROR_LED_Write(~(address >> 3 & 1));
    Debug_2_Write(~(address >> 2) & 1);
    Debug_1_Write(~(address >> 1) & 1);
    CAN_LED_Write(~address & 1);
    
    InitCAN(0x4, (int)address);
    Timer_1_Start();
    QuadDec_Start();

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
}

void PrintCanPacket(CANPacket receivedPacket){
    for(int i = 0; i < 8; i++ ) {
        sprintf(txData,"Byte%d %x   ", i+1, receivedPacket.data[i]);
        UART_UartPutString(txData);
    }

    sprintf(txData,"\r\n");
    UART_UartPutString(txData);
}

/*Returns the Packet ID or 0xFF if there is no Packet
This pulls from the CAN lib's FIFO
Also Triggers LED
*/
uint8_t ReadCAN(CANPacket *receivedPacket){
    volatile int error = PollAndReceiveCANPacket(receivedPacket);
    if(!error){
        CAN_check_delay = 0;
        CAN_LED_Write(LED_ON);
        CAN_time_LED = 0;
        return receivedPacket->data[0];
    }
   // sprintf(txData, "Mode: %x \r\n", mode);
    return 0xFF;//Means Errored Out
    
}

/* [] END OF FILE */
