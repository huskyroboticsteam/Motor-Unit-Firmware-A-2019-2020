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
#define TX_DATA_SIZE            (100u)
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

            //Tests if there are still drive packets that still need to be done
            //drive = !Can_rx_pwm.done | !Can_rx_angle.done;
            
            //Handles Can drive recieve packets
            //if (drive)
            //{           
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
            //}
            
            //Tests if there are any errors
          //  error = !stall.done | !invalid_arg.done | !command_failed.done; 
            
            //sends errors over CAN
            /*if(error){
                if(!stall.done) {
                    CAN_Send_Error(stall.code, stall.param);
                    stall.done = 1;
                }
                if(!invalid_arg.done) {
                    CAN_Send_Error(invalid_arg.code, invalid_arg.param);
                    invalid_arg.done = 1;
                }
                if(!command_failed.done) {
                    CAN_Send_Error(command_failed.code, command_failed.param);
                    command_failed.done = 1;
                }
            }*/
            
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
            //PWM test code
            /*CyDelay(100);
            if(up){
                test += 10;
            } else {
                test -= 10;   
            }
            if(test > 255) {
                up = 0;   
            } else if (test < -255) {
                up = 1;
            }
            set_PWM(test);
            */

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

//Recieve:
//1 00010 11010 0x45A General
//1 00010 10000 0x450 BBB to base rotation
//1 00010 10001 0x451 
//1 00010 10010 0x452
//1 00010 10011 0x453
//1 00010 10100 0x454
//1 00010 10101 0x455
//1 00010 10110 0x456
//Send:
//1 10000 00010 0x602 base rotation to BBB 
//1 10001 00010 0x622 shoulder to BBB
//1 10010 00010 0x642 elbow ""
//1 10011 00010 0x662 forearm rotation ""
//1 10100 00010 0x682 diff wrist 1 ""
//1 10101 00010 0x6A2 diff wrist 2 ""
//1 10110 00010 0x6C2 hand ""
void initialize_can_addr(void) {
    uint8 setting = Can_addr_Read();
    uint8 shift = 0;
    switch(Can_addr_Read()) {
        case 0b000: //Base rotation
            message_id = 0b10000;
            shift = 0;
            ratio = 1;
            break;
        case 0b001: // shoulder
            message_id = 0b10001;
            shift = 1;
            ratio = 14.45;
            #ifdef REV2
                flipEncoder = 1;
            #endif
            kp = 50;
            ki = 12;
            kd = 10;
            break;
        case 0b010: // elbow
            message_id = 0b10010;
            shift = 2;
            ratio = 2.8;
            break;
        case 0b011: // forearm rotation
            message_id = 0b10011;
            disable_limit = 1;
            shift = 3;
            ratio = 1;

            break;
        case 0b100: // diff wrist 1
            message_id = 0b10100;
            disable_limit = 1;
            shift = 4;
            ratio = 1.3888;
            kp = 20;
            ki = 30;
            kd = 10;
            flipEncoder = -1;
            break;
        case 0b101: // diff wrist 2
            message_id = 0b10101;
            disable_limit = 1;
            flipEncoder = -1;
            shift = 5;
            ratio = 1.3888;
            kp = 50;
            ki = 40;
            kd = 10;
            break;
        case 0b110: // hand
            message_id = 0b10110;
            shift = 6;
            ratio = 1;
            break;
        default:
            message_id = 0b11010;
            shift = 7;
            CAN_RX_MAILBOX_1_SHIFT = 0b10000000 << shift;
            CAN_RX_MAILBOX_0_SHIFT = 0b10000000 << (shift+1);
            CAN_RX_MAILBOX_0 = 15u;
            CAN_RX_MAILBOX_1 = 14u;
            break;
    }
    
    if(shift != 7) {
    CAN_RX_MAILBOX_0_SHIFT = CAN_RX_MAILBOX_0_SHIFT << shift;
    CAN_RX_MAILBOX_1_SHIFT = CAN_RX_MAILBOX_1_SHIFT << shift;
    CAN_RX_MAILBOX_0 += shift;
    CAN_RX_MAILBOX_1 += shift;
    }
    set_CAN_ID(0b1);
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %ld\r\n",setting, message_id);
        UART_UartPutString(txData); 
        sprintf(txData, "Can shift: %d   P0Mailbox: %d P1Mailbox %d\r\n",shift, CAN_RX_MAILBOX_0, CAN_RX_MAILBOX_1);
        UART_UartPutString(txData); 
        sprintf(txData, "disable_limit: %d\r\n",disable_limit);
        UART_UartPutString(txData); 
    }
}

void set_CAN_ID(uint32 priority) {
    message.id = (priority << 10) | (message_id << 5) | 0b00010;
}

    // takes between -255 and 255
void set_PWM(int compare) {
    pwm_compare = compare;
    #ifdef REV2
    compare = -compare;
    #endif
     if(uart_debug) {
        sprintf(txData, "PWM:%d disable_limit: %d\r\n",compare,disable_limit);
        UART_UartPutString(txData); 
    }
    invalidate = 0;
    if (compare < -255 || compare > 255) { return; }
    uint8 status = Status_Reg_Switches_Read();
    if (compare < 0 && (!(status & 0b01) || disable_limit) ) {
        Pin_Direction_Write(0);
        PWM_Motor_WriteCompare(-compare);
    } else if (compare > 0 && (!(status & 0b10) || disable_limit) ){
        Pin_Direction_Write(1);
        PWM_Motor_WriteCompare(compare);
    } else {
        PWM_Motor_WriteCompare(0);
        
    }
}

void CAN_Send_Encoder(void){
    int16 ticks = QuadDec_GetCounter();
    int16 angle = (((double)ticks)/ratio)*10;
    data.byte[0u] = 0x14u;
    data.byte[1u] = LO8(angle);
    data.byte[2u] = HI8(angle);
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug == 2) {
        sprintf(txData, "CAN_Send_Encoder: byte[0u] %x byte[1u] %x byte[2u] %x QuadDec Count %d\r\n",
            data.byte[0u],data.byte[1u],data.byte[2u],
            QuadDec_GetCounter());
        UART_UartPutString(txData);    
    }
}

void CAN_Send_Telemetry(void) {
    data.byte[0u] = 0x18u;
    data.byte[1u] = 0;
    data.byte[2u] = 0;
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug == 2) {
        sprintf(txData, "Telemerty: byte[0u] %x byte[1u] %x\r\n",(uint8)data.byte[0u],(uint8)data.byte[1u]);
        UART_UartPutString(txData); 
    }
}

void CAN_Send_Model(void) {
    data.byte[0u] = 0x12u;
    data.byte[1u] = 0x00u;
    data.byte[2u] = 0;
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug == 2) {
        sprintf(txData, "Model: byte[0u] %x byte[1u] %x\r\n",data.byte[0u],data.byte[1u]);
        UART_UartPutString(txData); 
    }
}

void CAN_Send_Error(uint8 code, uint8 param) {
    data.byte[0u] = 0xffu;
    data.byte[1u] = code;
    data.byte[2u] = param;
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug == 2) {
        sprintf(txData, "Error: byte[0u] %x byte[1u] %x byte[2u] %x\r\n",data.byte[0u],data.byte[1u], data.byte[2u]);
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

void set_Position(int16 degrees) {
    if(uart_debug) {
        sprintf(txData, "complete: %d\r\n",complete);
        UART_UartPutString(txData);
    }
    //while(!complete) {
        int PWM = position_PID(degrees_to_tick(degrees));
        if(uart_debug) {
            sprintf(txData, "PWM: %d\r\n",PWM);
            UART_UartPutString(txData);
        }
        if(PWM > maxV){
            set_PWM(maxV);   
        } else if(PWM < -maxV) {
            set_PWM(-maxV);
        } else {
            set_PWM(PWM);   
        }
   // }
}

int degrees_to_tick(int16 degrees){
    int ticks = (int)((double)degrees * ratio);
    if(uart_debug) {
        sprintf(txData, "degree: %d ticks: %d\r\n", degrees, ticks);
        UART_UartPutString(txData);
    }
    return(ticks);
}

int position_PID(int target){
    int16 current =  QuadDec_GetCounter() * flipEncoder;
    int p = target - current;
    if(p <= 5 && p >= -5) {
        if(uart_debug) {
            sprintf(txData, "p: %d\r\n",p);
            UART_UartPutString(txData);
        }
      //complete =  1;
      return(0);
    }
    i = i + p;
    if ( i > 500) {
        i = 500;   
    }
    if ( i < -500) {
        i = -500;
    }
    int d = p - lastp;
    lastp = p;
    if(uart_debug) {
        sprintf(txData, "p: %d, i: %d d %d current %d\r\n",p, i, d, current);
        UART_UartPutString(txData);
    }
    return (p*kp/10 + i*ki/10 + d*kd/10);
}

/*
void set_Speed(int current_spd, int speed) {
    // gathers current speed and modifies pwm to get desired speed
}
    */

/* [] END OF FILE */
