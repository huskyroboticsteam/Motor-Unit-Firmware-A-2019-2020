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

#include "my_can.h"

//Recieve:
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
            ratio = 1;
            flipEncoder = -1;
            kp = 50;
            ki = 3;
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
            ratio = 1;
            break;
        case 0b101: // diff wrist 2
            message_id = 0b10101;
            disable_limit = 1;
            shift = 5;
            ratio = 1;
            break;
        case 0b110: // hand
            message_id = 0b10110;
            shift = 6;
            ratio = 1;
            break;
    }
    
    CAN_RX_MAILBOX_0_SHIFT = CAN_RX_MAILBOX_0_SHIFT << shift;
    CAN_RX_MAILBOX_1_SHIFT = CAN_RX_MAILBOX_1_SHIFT << shift;
    CAN_RX_MAILBOX_0 += shift;
    CAN_RX_MAILBOX_1 += shift;
    set_CAN_ID(0b1);
    
    if(uart_debug) {
        sprintf(txData, "CAN dip setting:  %x Message ID: %ld\r\n",setting, message_id);
        UART_UartPutString(txData); 
        sprintf(txData, "Can shift: %d   P0Mailbox: %d P1Mailbox %d\r\n",shift, CAN_RX_MAILBOX_0, CAN_RX_MAILBOX_1);
        UART_UartPutString(txData); 
    }
}


void set_CAN_ID(uint32 priority) {
    message.id = (priority << 10) | (message_id << 5) | 0b00010;
}

void CAN_Send_Encoder(void){
    int16 ticks = QuadDec_GetCounter();
    data.byte[0u] = 0x14u;
    data.byte[1u] = LO8(ticks);
    data.byte[2u] = HI8(ticks);
    data.byte[3u] = 0;
    data.byte[4u] = 0;
    CAN_SendMsg(&message);
    if(uart_debug == 2) {
        sprintf(txData, "CAN_Send_Encoder: byte[0u] %x byte[1u] %x byte[2u] %x\n QuadDec Count %d\r\n",
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

inline void set_data(uint16 addr){
        //set mode
        if(CAN_RX_DATA_BYTE1(addr) == 0x00) {
            if(CAN_RX_DATA_BYTE2(addr) == 1 || CAN_RX_DATA_BYTE2(addr) == 0) {
                mode = CAN_RX_DATA_BYTE2(addr);
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
            if(Can_rx_angle.b1 != CAN_RX_DATA_BYTE2(addr)) {
                Can_rx_angle.b1 = CAN_RX_DATA_BYTE2(addr);
                Can_rx_angle.b2 = CAN_RX_DATA_BYTE3(addr);
                Can_rx_angle.b4 = CAN_RX_DATA_BYTE5(addr);
            }
            Can_rx_angle.b3 = CAN_RX_DATA_BYTE4(addr);
            Can_rx_angle.done = 0;
            complete = 1;
        } 
        //model requst
        else if (CAN_RX_DATA_BYTE1(addr) == 0x10){
            model_req = 1;
        }
}

void set_Position(int degrees) {
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


/* [] END OF FILE */
