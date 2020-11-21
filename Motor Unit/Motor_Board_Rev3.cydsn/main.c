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

#ifdef RGB_LED_ARRAY
#include "LED_Array.h"
#endif

#include "Motor_Unit_CAN.h"
#include "Motor_Unit_FSM.h"
#include "PositionPID.h"



extern const uint32 StripLights_CLUT[ ];

extern uint8_t motorUnitState;
extern uint8_t motorUnitMode;

//LED
uint8 CAN_time_LED = 0;
uint8_t ERRORTimeLED = 0;

//PID Constants
int32_t kPosition   = 0;
int32_t kIntegral   = 0;
int32_t kDerivative = 0;
uint32_t kPPJR      = 0;//pulses per joint revolution

int32_t millidegreeTarget = 0;


//Uart variables
char8 txData[TX_DATA_SIZE];

//drive varaible
uint8 invalidate = 0;
int32_t currentPWM = 0;
uint8_t ignoreLimSw = 0;


uint8 address = 0;

//Status and Data Structs
volatile uint8 drive = 0;
uint8_t CAN_check_delay = 0;


CY_ISR(Period_Reset_Handler) {
    int timer = Timer_PWM_ReadStatusRegister();
    invalidate++;
    CAN_time_LED++;
    CAN_check_delay ++;
    ERRORTimeLED++;
    if(invalidate >= 20){
        set_PWM(0, 0, 0);   
    }
    if(ERRORTimeLED >= 3) {
        ERROR_LED_Write(LED_OFF);
        Debug_1_Write(LED_OFF);
        Debug_2_Write(LED_OFF);
    }
    if(CAN_time_LED >= 3){
        CAN_LED_Write(LED_OFF);
    }
}
  
CY_ISR(Pin_Limit_Handler){
   /* if(uart_debug) {
        sprintf(txData,"Limit interupt triggerd\r\n");
        UART_UartPutString(txData);
    }*/
    set_PWM(currentPWM, ignoreLimSw, Status_Reg_Switches_Read());
    
    //for only one of the limit switches
    QuadDec_SetCounter(0);
}

int main(void)
{ 
    Initialize();
    #ifdef RGB_LED_ARRAY
    StripLights_DisplayClear(StripLights_BLACK);
    #endif
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
                set_PWM(currentPWM, ignoreLimSw, Status_Reg_Switches_Read());
                motorUnitState = SEND_TELE;
                break;
            case(CALC_PID):
                SetPosition(millidegreeTarget);   
                motorUnitState = SEND_TELE;
                break;
            case(SEND_TELE):
                //SendCANPacket(&can_send);
                motorUnitState = CHECK_CAN;
                break;
            case(QUEUE_ERROR):
                motorUnitState = SEND_TELE;
                break;
            case(CHECK_CAN):
                NextStateFromCAN(&can_recieve);
                PrintCanPacket(can_recieve);
                //sprintf(txData, "Mode: %x \r\n", mode);
                //UART_UartPutString(txData);
                break;
            default:
                GotoUninitState();
                break;

        }
        //sprintf(txData, "Mode: %x State:%x \r\n", motorUnitMode, motorUnitState);
        //UART_UartPutString(txData);
        //PackIntIntoDataMSBFirst(test_packet.data, 12345, 1);
        //sprintf(txData, "Mode: %d \r\n", DecodeBytesToIntMSBFirst(test_packet.data, 1, 5));
        //UART_UartPutString(txData);
        
        //sprintf(txData, "P: %d I: %d D: %d PPJ: %d Ready: %d \r\n", kPosition, kIntegral ,kDerivative, kPPJR, PIDconstsSet());
       // UART_UartPutString(txData);

        
    }
}
 


void Initialize(void) {
    CyGlobalIntEnable; /* Enable global interrupts. LED arrays need this first */
    #ifdef RGB_LED_ARRAY
    initalize_LEDs(LOW_LED_POWER);
    #endif
    Status_Reg_Switches_InterruptEnable();
    
    //display Dip Status
    address = Can_addr_Read();
    UART_Start();
    sprintf(txData, "Dip Addr: %x \r\n", address);
    UART_UartPutString(txData);
    
    #ifdef DEBUG_LEDS
    ERROR_LED_Write(~(address >> 3 & 1));
    Debug_2_Write(~(address >> 2) & 1);
    Debug_1_Write(~(address >> 1) & 1);
    CAN_LED_Write(~address & 1);
    #endif
    
    InitCAN(0x4, (int)address);
    Timer_PWM_Start();
    QuadDec_Start();
    PWM_Motor_Start();  

    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_PWM_StartEx(Period_Reset_Handler);
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
        CAN_LED_Write(LED_ON);
        CAN_time_LED = 0;
        return receivedPacket->data[0];
    }
   // sprintf(txData, "Mode: %x \r\n", mode);
    return 0xFF;//Means Errored Out
    
}

void DisplayErrorCode(uint8_t code) {
    ERRORTimeLED = 0;
    ERROR_LED_Write(LED_ON);
    
    #ifdef DEBUG_LEDS
    switch(code)
    {   
        //case0: CAN Packet ERROR
        case 1://Mode Error
            Debug_1_Write(LED_ON);
            break;
        case 2:
            Debug_2_Write(LED_ON);
            break;
        case 3:
            Debug_1_Write(LED_ON);
            Debug_2_Write(LED_ON);
            break;
    }
    #endif
}

/* [] END OF FILE */
