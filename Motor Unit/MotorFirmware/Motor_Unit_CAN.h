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

/* [] END OF FILE */

#ifndef MOTOR_CAN_H
#define MOTOR_CAN_H
    #include <project.h>
    #include "../CANLib/CANLibrary.h"
    void NextStateFromCAN(CANPacket *receivedPacket, CANPacket *packetToSend);
    void SendEncoderData(CANPacket *packetToSend);
    #define NO_NEW_CAN_PACKET 0xFFFF
#endif
    