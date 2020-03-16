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

//LED
uint8 time_LED = 0;

//Uart variables
volatile uint8 uart_debug = 2;
#define PWM_PERIOD = 255;

//drive varaible
int pwm_compare;
uint8 invalidate = 0;

//drive mode
uint8 mode = 2;

//Status and Data Structs
struct Can_data Can_rx_pwm, Can_rx_angle;
volatile uint8 drive = 0;


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
        Can_rx_pwm.done = 1;
    }
}
  
CY_ISR(Pin_Limit_Handler){
   /* if(uart_debug) {
        sprintf(txData,"Limit interupt triggerd\r\n");
        UART_UartPutString(txData);
    }*/
    set_PWM(pwm_compare, 0, 0);
    QuadDec_SetCounter(0);
}

int main(void)
{ 
    initialize();
    //initialize_can_addr();
    int up = 0;
    int test = 0;
    pwm_compare = 0;
    set_PWM(0, 0, 0);
    
    for(;;)
    {
       
    }
}
 


void initialize(void) {
    InitCAN(0x4,0x1);
    Status_Reg_Switches_InterruptEnable();
    Timer_1_Start();
    QuadDec_Start();
    PWM_Motor_Start();  
    CAN_GlobalIntEnable();
    CyGlobalIntEnable; /* Enable global interrupts. */
    isr_Limit_1_StartEx(Pin_Limit_Handler);
    isr_period_StartEx(Period_Reset_Handler);
    
}








/* [] END OF FILE */
