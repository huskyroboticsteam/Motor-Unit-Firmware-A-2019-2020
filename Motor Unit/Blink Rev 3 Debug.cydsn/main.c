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
#include "project.h"

int led_count = 0;
void Rainbow(uint32 delay);
void set_PWM(int compare);
int status = 0;
int disable_limit = 1;

uint32 startColor = 0;  // Index color in colorwheel
uint32 ledPosition = 0; // LED position when setting color         
uint32 color = 0;       // Temp color to set LED

extern const uint32 StripLights_CLUT[ ];
int main(void)
{
    // Initialize StripLights
    StripLights_Start();  
	
	// Set dim level 0 = full power, 4 = lowest power
    StripLights_Dim(4); 
	
	// Clear all memory to black
	StripLights_MemClear(StripLights_BLUE);
    StripLights_Trigger(1); 
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    //led_timer_StartEx(Period_Reset_Handler);
   // Timer_1_Start();
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    uint32_t color = 0;
    int test = 0;
    int up;

    //StripLights_Trigger(1);
    PWM_Motor_Start();  
    
    for(;;)
    {

        
        ERROR_LED_Write((Status_Reg_1_Read()>>0) & 0b1 );
        Debug_1_Write((Status_Reg_1_Read()>>2) & 0b1);
        Debug_2_Write((Status_Reg_1_Read() >> 1) & 0b1);
        CAN_LED_Write((Status_Reg_1_Read()>>3) & 0b1);
        
        Rainbow(100);
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
    }
}

/************************************************
 *                    Rainbow()
 *
 *  Use the colorwheel section of the color lookup
 *  table to create a rotating rainbow.
 *
 ************************************************/
void Rainbow(uint32 delay)
{
	
		// Wait for last update to complete
        while( StripLights_Ready() == 0);  
		
		// Set new start color
        color = startColor;    
		
		// Loop through all LEDs giving each one a different color from the color wheel
        for(ledPosition = 0; ledPosition <= StripLights_TOTAL_LEDS; ledPosition++)
        {
            StripLights_Pixel(ledPosition, 0, StripLights_getColor( color ));
            color++;
            if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
        }
		
		// Update the LEDs all at once
		StripLights_Trigger(1); 
		
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		startColor++;  
        if(startColor >= StripLights_COLOR_WHEEL_SIZE) startColor = 0;
    
        CyDelay(delay);   // Loop delay

	   // if(SW1_Read() == 0) break;  // If SW1 pressed leave

}

void set_PWM(int compare) {
   /* pwm_compare = compare;
    #ifdef REV2
    compare = -compare;
    #endif
     if(uart_debug) {
        sprintf(txData, "PWM:%d disable_limit: %d\r\n",compare,disable_limit);
        UART_UartPutString(txData); 
    }
    invalidate = 0;*/
    if (compare < -255 || compare > 255) { return; }
    //uint8 status = Status_Reg_Switches_Read();
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

/* [] END OF FILE */
