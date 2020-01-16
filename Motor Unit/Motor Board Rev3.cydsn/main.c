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

//CAN variables
uint32 message_id = 0;
#define MESSAGE_IDE             (0u)    /* Standard message */
#define MESSAGE_IRQ             (0u)    /* No transmit IRQ */
#define MESSAGE_RTR             (0u)    /* No RTR */
uint16 CAN_RX_MAILBOX_1_SHIFT  = 0b1;
uint32 CAN_RX_MAILBOX_0_SHIFT  = 0b10000000;
uint16 CAN_RX_MAILBOX_1 = 0u;
uint16 CAN_RX_MAILBOX_0 = 7u;
int CAN_TIMEOUT;

CY_ISR_PROTO(ISR_CAN);

//Uart variables
volatile uint8 uart_debug = 2;
#define PWM_PERIOD = 255;


//drive varaible
int GEAR_RATIO;
int pwm_compare;
uint8 invalidate = 0;

//PID varaibles
int8 flipEncoder = 1;
int16 final_angle = 0;
int i = 0;
int lastp = 0;
int kp;
int ki;
int kd;
double ratio;
uint8 complete = 0;
uint8 maxV = 0;

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
        if(!emergency) {

            
                //Mode 0 packets
                if(!Can_rx_pwm.done) {
                    if(mode == 0) {
                        if(uart_debug) {
                            sprintf(txData, "B1: %d, B2: %d done %x\r\n",Can_rx_pwm.b1, Can_rx_pwm.b2, Can_rx_pwm.done);
                            UART_UartPutString(txData);
                        }
                        Can_rx_pwm.done = 1;
                        if(Can_rx_pwm.b2 & 0b01) {
                            set_PWM((int)Can_rx_pwm.b1);
                        }
                        else {
                            set_PWM(-(int)Can_rx_pwm.b1);
                        }
                    } else {
                        command_failed.done = 0;
                        command_failed.param = 0x02;
                        if(uart_debug) {
                            sprintf(txData, "Mode is not set to 0, mode is %d\r\n",mode);
                            UART_UartPutString(txData);
                        }
                    }
                }
                
                // Mode 1 packets
               // if(!Can_rx_angle.done){
                    if(mode == 1){
                        if(uart_debug) {
                            sprintf(txData, "B1: %d, B3: %d done %x\r\n",Can_rx_angle.b1, Can_rx_angle.b3, Can_rx_pwm.done);
                            UART_UartPutString(txData);
                        }
                        //Can_rx_angle.done = 1;
                        complete = 0;
                        maxV = Can_rx_angle.b3;
                        i = 0;
                        
                       // final_angle = final_angle | (int16)Can_rx_angle.b2 << 8;
                       // final_angle = final_angle | (int16)Can_rx_angle.b1;
                        final_angle = ((uint16_t)Can_rx_angle.b2) << 8 | Can_rx_angle.b1;
                        set_Position(final_angle);
                    }
                    else if(!Can_rx_pwm.done) {
                        command_failed.done = 0;
                        command_failed.param = 0x04;
                        if(uart_debug) {
                            sprintf(txData, "Mode is not set to 1, mode is %d\r\n", mode);
                            UART_UartPutString(txData);
                        }
                    }
                //}
                
                if(mode != 1 && mode != 0) {
                    Can_rx_angle.done = 1;
                    Can_rx_pwm.done = 1;
                }
            
            //Sends periodic data
            if(send_data) {
                if(uart_debug) {
                    sprintf(txData,"\nSending Data... \r\n");
                   // UART_UartPutString(txData);
                }
                CAN_Send_Encoder(); 
                send_data = 0;
            }
            
            //Sends model
            if(model_req) {
                CAN_Send_Model();
                model_req = 0;
            }

        }
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
   // ADC_SAR_Seq_1_Start();
    //ADC_SAR_Seq_1_StartConvert();
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


CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;
    if(uart_debug) {
        UART_UartPutString("\n Can rx triggered\n");   
    }
    /* Switch status message received */
    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_0_SHIFT) != 0u)
    {   
        if(uart_debug){
            UART_UartPutString("P0 recieved\n");    
        }
        #ifdef REV2
        time_LED = 0;
        Test_LED_Write(LED_ON);
        #endif
        set_data(CAN_RX_MAILBOX_0);
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_0);
    }

    if ((CAN_BUF_SR_REG & CAN_RX_MAILBOX_1_SHIFT) != 0u)
    {
        if(uart_debug){
            UART_UartPutString("P1 recieved\n\n");    
        }
        #ifdef REV2
        time_LED = 0;
        Test_LED_Write(LED_ON);
        #endif
        set_data(CAN_RX_MAILBOX_1);
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(CAN_RX_MAILBOX_1);
    }
    
}

inline void set_data(uint16 addr){
        //set mode
        if(CAN_RX_DATA_BYTE1(addr) == 0x00) {
            if(CAN_RX_DATA_BYTE2(addr) == 1 || CAN_RX_DATA_BYTE2(addr) == 0) {
                mode = CAN_RX_DATA_BYTE2(addr);
                if(mode == 1){
                    final_angle = QuadDec_GetCounter() * flipEncoder;
                    i = 0;
                }
            }
            else {
                invalid_arg.param = 0x00;
                invalid_arg.done = 0;
            }
            complete = 1;
        } 
        //pwm
        else if(CAN_RX_DATA_BYTE1(addr) == 0x02) {
            Can_rx_pwm.b1 = CAN_RX_DATA_BYTE2(addr);
            Can_rx_pwm.b2 = CAN_RX_DATA_BYTE3(addr);
            Can_rx_pwm.b3 = CAN_RX_DATA_BYTE4(addr);
            Can_rx_pwm.b4 = CAN_RX_DATA_BYTE5(addr);
            Can_rx_pwm.done = 0;
        } 
        //angle
        else if(CAN_RX_DATA_BYTE1(addr) == 0x04) {
            Can_rx_angle.b1 = CAN_RX_DATA_BYTE2(addr);
            Can_rx_angle.b2 = CAN_RX_DATA_BYTE3(addr);
            Can_rx_angle.b3 = CAN_RX_DATA_BYTE4(addr);
            Can_rx_angle.b4 = CAN_RX_DATA_BYTE5(addr);
            Can_rx_angle.done = 0;
            if((((uint16_t)Can_rx_angle.b2) << 8 | Can_rx_angle.b1) != final_angle){
                 i=0;
            }
            complete = 1;
        } 
        //model requst
        else if (CAN_RX_DATA_BYTE1(addr) == 0x10){
            model_req = 1;
        }
}





/* [] END OF FILE */
