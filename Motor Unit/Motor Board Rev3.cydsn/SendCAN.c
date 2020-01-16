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
