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
#include "DebugMessages.h"

//LED
uint8 time_LED = 0;
extern const uint32 StripLights_CLUT[ ];
uint8_t send_animation = 0;

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

int test;
CAN_RX_CFG rxMailbox;
//CY_ISR_PROTO(ISR_CAN);


CY_ISR(Period_Reset_Handler) {
    volatile int timer = Timer_1_ReadStatusRegister();
    invalidate++;
    time_LED++;
    send_animation = send_animation >= 12 ? 0 : send_animation;
    StripLights_MemClear(StripLights_BLACK);
    StripLights_Pixel(send_animation/3, 0, get_color_packet(0,0,255));
    StripLights_Trigger(1);
    send_animation++;
    if(invalidate >= 20){
        set_PWM(0, 0, 0);   
    }
}
  
CY_ISR(Pin_Limit_Handler){
    set_PWM(0, 0, 0);
    QuadDec_SetCounter(0);
}

int main(void)
{ 
    Initialize();
    set_all_LED_Colors(get_color_packet(0,0,255));
    CANPacket can_recieve;
    CANPacket can_send;
    volatile int error = 0;
    can_send.id = 0x4 << 6 | 0xf;
    uint8_t destSerial = 1;
    for(;;)
    {
        switch(mode){
            case(UNINIT):
                InitializeMessage();
                destSerial = SetTargetSerial();
                mode = MODE_SEL;
                break;
            case(MODE_SEL):
                mode = SelectModeMessage();
                AssembleModeSetPacket(&can_send, 0x4, destSerial, mode);
                SendCANPacket(&can_send);
                if(mode == UNINIT){
                    mode = MODE_SEL;
                }
                break;
            case(CONSTRUCT_PWM):
                AssemblePWMDirSetPacket(&can_send, 0x4, destSerial, SetMotorPWM());
                SendCANPacket(&can_send);
                UART_UartPutString(txData);
                mode = SEND_PACKET;
                break;
            case(CONSTRUCT_PID):
                mode = SEND_PACKET;
                break;
            case(SEND_PACKET):
                mode = CONSTRUCT_PWM;
                break;
            case(READ_CAN):
            default:
                mode = UNINIT;
                break;
        }
    }
}
 


void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    initalize_LEDs(LOW_LED_POWER);
    
    //display Dip Status
    address = Can_addr_Read();
    UART_Start();
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

/*
void ReadCan(CANPacket *receivedPacket){
    uint8_t error = PollAndReceiveCANPacket(receivedPacket);
    if(error){
        return 1;
    }
    
}
*/
/* [] END OF FILE */
