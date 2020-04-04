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
#include "../CANLib/CANLibrary.h"
#include "MotorDrive.h"
#include "LED_Array.h"

//LED
uint8 time_LED = 0;

//Uart variables
char8 txData[TX_DATA_SIZE];

//drive varaible
uint8 invalidate = 0;

//drive mode
volatile uint8 mode = 2;

//Status and Data Structs
volatile uint8 drive = 0;

int test;


CY_ISR(Period_Reset_Handler) {
    int timer = Timer_1_ReadStatusRegister();
   /* if(uart_debug) {
        sprintf(txData,"Period interupt triggerd %x\r\n", timer);
        //UART_UartPutString(txData);
    }*/
    invalidate++;
    time_LED++;
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
    set_all_LED_Colors(get_color_packet(255,0,0));
    CANPacket my6Pack;
    for(;;)
    {
        for(int i = 0; i < 255; i++) {
            colorShift(get_color_packet(255, 0, 255),
                       get_color_packet(0, 255, 0)  , i, 255);
            CyDelay(20);
        }
        for(int i = 0; i < 255; i++) {
            colorShift(get_color_packet(255, 0, 255),
                       get_color_packet(0, 255, 0)  , 255 - i, 255);
            CyDelay(20);
        }
        
        /*
        if(!PollAndReceiveCANPacket(&my6Pack)) {
            for(int i = 0; i < 8; i++ ) {
                sprintf(txData,"Byte%d %x   ", i+1, my6Pack.data[i]);
                UART_UartPutString(txData);
            }
                sprintf(txData,"\r\n");
                UART_UartPutString(txData);
            //CyDelay(100);
        }
        */
    }
}
 


void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    initalize_LEDs(LOW_LED_POWER);
 
    UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", Can_addr_Read());
    UART_UartPutString(txData);
    
    InitCAN(0x4, Can_addr_Read());
    Timer_1_Start();
    QuadDec_Start();
    CAN_GlobalIntEnable();

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
}








/* [] END OF FILE */
