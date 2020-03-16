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

#include "CAN.h"


//CAN variables
uint32 message_id = 0;

int CAN_TIMEOUT;
int mailbox = 0x000;
uint8 emergency = 0;
char8 txData[TX_DATA_SIZE];
/* Global variables used to store configuration and data for BASIC CAN mailbox */
CAN_DATA_BYTES_MSG data;
CAN_TX_MSG message;

/* BASIC CAN mailbox configuration */
message.dlc = 5u;
message.ide = MESSAGE_IDE;
message.irq = MESSAGE_IRQ;
message.msg = &data;
message.rtr = MESSAGE_RTR;
    


CY_ISR_PROTO(ISR_CAN);

CY_ISR(ISR_CAN)
{
    /* Clear Receive Message flag */
    CAN_INT_SR_REG = CAN_RX_MESSAGE_MASK;
    if(uart_debug) {
        UART_UartPutString("\n Can rx triggered\n");   
    }
    /* Switch status message received */
    if (CAN_BUF_SR_REG & 0b1)
    {   
        if(uart_debug){
            UART_UartPutString("P0 recieved\n");    
        }
        set_data(0b0);
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(0b0);
    }

    if (CAN_BUF_SR_REG & 0b10)
    {
        if(uart_debug){
            UART_UartPutString("P1 recieved\n\n");    
        }
        
        set_data(0b1);
        /* Acknowledges receipt of new message */
        CAN_RX_ACK_MESSAGE(0b1);
    }
    
}

inline void set_data(uint16 addr){
        //set mode
        switch(CAN_RX_DATA_BYTE1(addr)) {
            case 0x00: 
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
                break;
            case 0x02:
                Can_rx_pwm.b1 = CAN_RX_DATA_BYTE2(addr);
                Can_rx_pwm.b2 = CAN_RX_DATA_BYTE3(addr);
                Can_rx_pwm.b3 = CAN_RX_DATA_BYTE4(addr);
                Can_rx_pwm.b4 = CAN_RX_DATA_BYTE5(addr);
                Can_rx_pwm.done = 0;
                break;
            case 0x04:
                Can_rx_angle.b1 = CAN_RX_DATA_BYTE2(addr);
                Can_rx_angle.b2 = CAN_RX_DATA_BYTE3(addr);
                Can_rx_angle.b3 = CAN_RX_DATA_BYTE4(addr);
                Can_rx_angle.b4 = CAN_RX_DATA_BYTE5(addr);
                Can_rx_angle.done = 0;
                if((((uint16_t)Can_rx_angle.b2) << 8 | Can_rx_angle.b1) != final_angle){
                     i=0;
                }
                complete = 1;
                break;
            case 0x10:
                model_req = 1;
                break;
            default:
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
/* [] END OF FILE */
