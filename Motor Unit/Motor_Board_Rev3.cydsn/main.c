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
CAN_RX_CFG rxMailbox;
CY_ISR_PROTO(ISR_CAN);


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
    CAN_Start();

    
    rxMailbox.rxmailbox = 0;
    rxMailbox.rxacr = 0x20F<<21;
    rxMailbox.rxamr = 0x001FFFFF;//0x001FFFF9;
    rxMailbox.rxcmd = CAN_RX_CMD_REG(CAN_RX_MAILBOX_0);//need to know what this is
    CAN_RxBufConfig(&rxMailbox);
    
    rxMailbox.rxmailbox = 1;
    rxMailbox.rxacr = 0x10F<<21;
    rxMailbox.rxamr = 0x001FFFFF;//0x001FFFF9;
    rxMailbox.rxcmd = CAN_RX_CMD_REG(CAN_RX_MAILBOX_1);//5 << 16 | 1 << 5;
    CAN_RxBufConfig(&rxMailbox);
    
    CAN_GlobalIntEnable();
    /* Set CAN interrupt handler to local routine */
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);

    
    //InitCAN(0x4, Can_addr_Read());
    Timer_1_Start();
    QuadDec_Start();

    CAN_Start();

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
}

CY_ISR(ISR_CAN)
{
    sprintf(txData, "CAN MSG ");
    UART_UartPutString(txData);
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;
    if(CAN_BUF_SR_REG & 1) { // mailbox0 is full
        sprintf(txData, "MAILBOX 0 Byte 4 %x", CAN_RX_DATA_BYTE4(CAN_RX_MAILBOX_0));
        UART_UartPutString(txData);
        sprintf(txData, " |||     Byte ID %lx \r\n", CAN_GET_RX_ID(CAN_RX_MAILBOX_0));
        UART_UartPutString(txData);
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_0);
    }
    if(CAN_BUF_SR_REG & 2) { // mailbox0 is full
        sprintf(txData, "MAILBOX 1 Byte 4 %x", CAN_RX_DATA_BYTE4(CAN_RX_MAILBOX_1));
        UART_UartPutString(txData);
        sprintf(txData, " |||     Byte ID %lx \r\n", CAN_GET_RX_ID(CAN_RX_MAILBOX_1));
        UART_UartPutString(txData);
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_1);
    }
}





/* [] END OF FILE */
