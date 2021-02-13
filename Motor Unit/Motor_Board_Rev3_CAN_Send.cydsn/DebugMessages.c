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
#include "DebugMessages.h"
#include "cyapicallbacks.h"
#include <stdio.h>
#include <stdlib.h>

extern char8 txData[TX_DATA_SIZE];
extern volatile uint8_t address;

void InitializeMessage(void){
    UART_UartPutString("\r\n-------------------------Reset-------------------------");
    sprintf(txData, "\r\n\r\nAddr: %x \r\n", address);
    UART_UartPutString(txData);
    UART_UartPutString("\r\nWelcome to Motor CAN Tester press enter to continue \r\n");
    while(UART_UartGetChar() == 0){//y in ascii
    }
    UART_SpiUartClearRxBuffer(); 
    //clear the line return;
    UART_UartPutString("\r\n-------------------------WARNING-------------------------");
    UART_UartPutString("\r\nMake Sure the motors CAN MOVE FREELY. \r\nBe prepared to disconnect power from the system at any point\r\n");
}

uint8_t SelectModeMessage(void){
    UART_UartPutString("\r\n-------------------------MODE SEL-------------------------");
    UART_UartPutString("\r\nSelect a mode(type a number): \r\n 0: PWM \r\n 1: PID \r\nMode: ");
    uint8_t response = UART_UartGetChar();
    while (response < 48 + 0 || response > 48 + 1) {
        response = UART_UartGetChar();
    }
    switch(response) {
        case(48):
            UART_UartPutString("\r\nPWM Mode Selected\r\n");
            return 0;
            break;
        case(49):
            UART_UartPutString("\r\nPID Mode Selected\r\n");
            return(NeedToImplementMessage());
            break;
        case(50):
            UART_UartPutString("\r\nCAN SEND Mode Selected\r\n");
            return(NeedToImplementMessage());
            break;
        case(51):
            UART_UartPutString("\r\nCAN READ Mode Selected\r\n");
            return(NeedToImplementMessage());
            break;
        default:
            UART_UartPutString("\r\nERROR SENDING BACK TO MODE SELECT\r\n");
            return(0xFF);
            break;
    }
}

uint8_t SetTargetSerial(void) {
    UART_UartPutString("\r\n-------------------------SERIAL VALUE-------------------------");
    UART_UartPutString("\r\nSerial are values between 1-63. 0 is broadcast and is disabled for saftey \r\nValue: ");
    uint8_t serial = 0;   
    do {
        serial = ReadNumberFromUART();
    } while (serial <= 0 || serial > 63);
    sprintf(txData, "Serial Value: %d\r\n", serial);
    UART_UartPutString(txData);
    return serial;
}

int32_t SetMotorPWM(void){
    UART_SpiUartClearRxBuffer();
    UART_UartPutString("\r\n-------------------------PWM VALUE-------------------------");
    UART_UartPutString("\r\nSet a PWM value between  −32,768 and 32,767\r\nValue: ");
    int32_t result = ReadNumberFromUART();
    sprintf(txData, "PWM Value: %d\r\n", result);
    UART_UartPutString(txData);
    return(result);
}

int32_t ReadNumberFromUART(void) {
    char buffer[100];
    uint8_t size = 100;
    StoreUARTBufferToArray(buffer,size);
    return atoi(buffer);
}

void StoreUARTBufferToArray(char* buffer, uint8_t size){
    uint8_t index = 1;   
    uint8_t response;
    
    do {
        response = UART_UartGetChar();
    } while(response == 0);
    
    buffer[0] = response;
    
    while(response != '\r' && index < size - 1){
        do { 
            response = UART_UartGetChar();
        } while(response == 0);
        buffer[index] = response;
        index++;
    }
    buffer[index] = 0; 
}

uint8_t NeedToImplementMessage(void){
    UART_UartPutString("\r\n---NOT IMPLEMENTED YET---\r\n");
    return 0xFF;
    
}


/* [] END OF FILE */
