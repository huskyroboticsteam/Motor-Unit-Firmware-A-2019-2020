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

#define REV2
#define LED_ON   (0u)
#define LED_OFF  (1u)

//LED
uint8 time_LED = 0;

//Uart variables
volatile uint8 uart_debug = 2;
#define PWM_PERIOD = 255;

//drive varaible
int GEAR_RATIO;
int pwm_compare;
uint8 invalidate = 0;

//drive mode
uint8 mode = 2;

//flags
uint8 send_data = 1;
uint8 model_req = 0;
uint8 disable_limit = 0;

//Status and Data Structs
struct Can_data Can_rx_pwm, Can_rx_angle;
struct Error stall;
struct Error command_failed;
struct Error invalid_arg;


int mailbox = 0x000;
uint8 emergency = 0;
char8 txData[TX_DATA_SIZE];
/* Global variables used to store configuration and data for BASIC CAN mailbox */
CAN_DATA_BYTES_MSG data;
CAN_TX_MSG message;

volatile uint8 drive = 0;


CY_ISR(Period_Reset_Handler) {
    int timer = Timer_1_ReadStatusRegister();
    if(uart_debug) {
        sprintf(txData,"Period interupt triggerd %x\r\n", timer);
        //UART_UartPutString(txData);
    }
    send_data = 1;
    invalidate++;
    time_LED++;
    if(invalidate >= 20){
        set_PWM(0);   
        Can_rx_pwm.done = 1;
    }
    
    #ifdef REV2
        if(time_LED >= 5){
            Test_LED_Write(LED_OFF);
            
            
        }
    #endif
    #ifdef REV1
        if(time_LED){
            Test_LED_W
    #endif
}
  
CY_ISR(Pin_Limit_Handler){
    if(uart_debug) {
        sprintf(txData,"Limit interupt triggerd\r\n");
        UART_UartPutString(txData);
    }
    set_PWM(pwm_compare);
    QuadDec_SetCounter(0);
}

int main(void)
{ 
    #ifdef REV2
        Test_LED_Write(LED_ON);
        Error_Write(LED_ON);
    #endif
    stall.code = 0x01;
    stall.done = 1;
    command_failed.code = 0x02;
    command_failed.done = 1;
    invalid_arg.code = 0x03;
    invalid_arg.done = 1;
    uint8 error;
        /* BASIC CAN mailbox configuration */
    message.dlc = 5u;
    message.ide = MESSAGE_IDE;
    message.irq = MESSAGE_IRQ;
    message.msg = &data;
    message.rtr = MESSAGE_RTR;
    
    #ifdef REV2
        Test_LED_Write(0);
        Error_Write(0);
    #endif

    initialize();
    initialize_can_addr();
    int up = 0;
    int test = 0;
    pwm_compare = 0;
    set_PWM(0);
    
    #ifdef REV2
        Test_LED_Write(LED_OFF);
        Error_Write(LED_OFF);
    #endif
    
    for(;;)
    {
       
    }
}

void emergency_halt(void) {
    PWM_Motor_Stop();
    emergency = 1;
    // stops all motors;
    // waits for restart CAN signal.
}

void initialize(void) {
    int can_start = CAN_Start();
    Status_Reg_Switches_InterruptEnable();
    Timer_1_Start();
    QuadDec_Start();
    PWM_Motor_Start();  
    
    CAN_GlobalIntEnable();
    CyIntSetVector(CAN_ISR_NUMBER, ISR_CAN);
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
    
    if(uart_debug) {
        UART_Start();
        sprintf(txData, "CAN_Start():  %u\r\n",can_start);
        UART_UartPutString(txData); 
    }
}








/* [] END OF FILE */
