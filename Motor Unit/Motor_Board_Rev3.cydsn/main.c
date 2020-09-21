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

#include "cyapicallbacks.h"
#include <stdio.h>
#include <stdint.h>
#include "MotorDrive.h"
#include "LED_Array.h"
#include "Motor_Unit_CAN.h"
#include "Motor_Unit_FSM.h"



extern const uint32 StripLights_CLUT[ ];

extern uint8_t motorUnitState;
extern uint8_t motorUnitMode;

//LED
uint8 CAN_time_LED = 0;

//Uart variables
char8 txData[TX_DATA_SIZE];

//drive varaible
uint8 invalidate = 0;
int currentPWM = 0;


uint8 address = 0;

//Status and Data Structs
volatile uint8 drive = 0;
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
    CANPacket can_recieve;
    CANPacket can_send;
    CANPacket test_packet;
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
        switch(motorUnitState) {
            case(UNINIT):
                //idle animation
                motorUnitState = CHECK_CAN;
                break;
            case(SET_PWM):
                set_PWM(currentPWM,1,0);
                StripLights_MemClear(StripLights_BLACK);
                StripLights_Pixel(0, 0, get_color_packet(0,0,255));
                StripLights_Trigger(1);
                motorUnitState = SEND_TELE;
                break;
            case(CALC_PID):
                StripLights_MemClear(StripLights_BLACK);
                StripLights_Pixel(1, 0, get_color_packet(0,0,255));
                StripLights_Trigger(1);
                motorUnitState = SEND_TELE;
                break;
            case(SEND_TELE):
                SendCANPacket(&can_send);
                motorUnitState = CHECK_CAN;
                break;
            case(QUEUE_ERROR):
                motorUnitState = SEND_TELE;
                break;
            case(CHECK_CAN):
                NextStateFromCAN(&can_recieve);
                //PrintCanPacket(can_recieve);
                //sprintf(txData, "Mode: %x \r\n", mode);
                //UART_UartPutString(txData);
                break;
            default:
                gotoUninitState();
                break;

        }
        //sprintf(txData, "Mode: %x State:%x \r\n", motorUnitMode, motorUnitState);
        //UART_UartPutString(txData);
        //PackIntIntoDataMSBFirst(test_packet.data, 12345, 1);
        //sprintf(txData, "Mode: %d \r\n", DecodeBytesToIntMSBFirst(test_packet.data, 1, 5));
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
    PWM_Motor_Start();  

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
}

//debug tool for that prints packet to UART
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
