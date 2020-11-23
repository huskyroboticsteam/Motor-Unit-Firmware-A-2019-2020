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
    void NextStateFromCAN(CANPacket *receivedPacket);
    void SendEncoderData(CANPacket *packetToSend);
#endif
    