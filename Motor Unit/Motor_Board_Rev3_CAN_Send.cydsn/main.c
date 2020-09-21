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
   /* if(uart_debug) {
        sprintf(txData,"Period interupt triggerd %x\r\n", timer);
        //UART_UartPutString(txData);
    }*/
    invalidate++;
    time_LED++;
    send_animation = send_animation >= 12 ? 0 : send_animation;
    StripLights_MemClear(StripLights_BLACK);
    StripLights_Pixel(send_animation/3, 0, get_color_packet(0,0,255));
    StripLights_Trigger(1);
    send_animation++;
    if(invalidate >= 20){
        set_PWM(0, 0, 0);   
        //Can_rx_pwm.done = 1;
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
    set_all_LED_Colors(get_color_packet(0,0,255));
   // CyDelay(2000);
    CANPacket can_recieve;
    CANPacket can_send;
    volatile int error = 0;
    can_send.id = 0x4 << 6 | 0xf;
    can_send.dlc = 0x8;
    uint8_t test = 0;

    for(int i = 0; i < 8; i++) {
        can_send.data[i] = i;
    }
    for(;;)
    {
    switch(address) {
        case(0)://spam
            can_send.data[0] = test;
            if(test == 0 && can_send.data[1] == 1) {
                can_send.data[1] = 0;
            } else if (test == 0) {
                can_send.data[1] = 1;
            }
            test++;
            SendCANPacket(&can_send);
            CyDelay(10);//send rate of bottom board
        break;
        case(1):
            can_send.data[0] = 0;
            can_send.data[1] = MOTOR_UNIT_MODE_PWM;
            SendCANPacket(&can_send);
            CyDelay(1000);
            can_send.data[0] = 0;
            can_send.data[1] = MOTOR_UNIT_MODE_PID;
            SendCANPacket(&can_send);
            CyDelay(1000);
        break;
        case(2):
            for(int i = 0; i < 8; i++) {
                can_send.data[i] = 0;
             }
            can_send.data[0] = 0;
            can_send.data[1] = MOTOR_UNIT_MODE_PWM;
            SendCANPacket(&can_send);
            CyDelay(1000);
            can_send.data[0] = 3;
            for(int i = 0; i < 65535; i+= 1000) {
            PackIntIntoDataMSBFirst(can_send.data,i,1);
            SendCANPacket(&can_send);
            CyDelay(100);
            PackIntIntoDataMSBFirst(can_send.data,-i,1);
            SendCANPacket(&can_send);
            CyDelay(100);
            
            }
            
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

/*
void ReadCan(CANPacket *receivedPacket){
    uint8_t error = PollAndReceiveCANPacket(receivedPacket);
    if(error){
        return 1;
    }
    
}
*/
/* [] END OF FILE */
