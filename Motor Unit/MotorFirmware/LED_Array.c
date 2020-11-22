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
#include "LED_Array.h"
#include "project.h"

extern const uint32 StripLights_CLUT[ ];

void colorShift(uint32_t color1, uint32_t color2,
                uint32_t transition, uint32_t increment) 
    {
        int16_t g1 = (uint8)(color1 & 0x000000FF);  // Write Green
        int16_t r1 = (uint8)((color1 >> 8) & 0x000000FF);  // Write Red
        int16_t b1 = (uint8)((color1 >> 16) & 0x000000FF);  // Write Blue
        
        int16_t g2 = (uint8)(color2 & 0x000000FF);  // Write Green
        int16_t r2 = (uint8)((color2 >> 8) & 0x000000FF);  // Write Red
        int16_t b2 = (uint8)((color2 >> 16) & 0x000000FF);  // Write Blue
        
        
        double r_inc = r2 - r1;
        double g_inc = g2 - g1;
        double b_inc = b2 - b1;
        
        r_inc /= increment;
        g_inc /= increment;
        b_inc /= increment;
        
        uint8_t r = r_inc*transition + r1;
        uint8_t g = g_inc*transition + g1;
        uint8_t b = b_inc*transition + b1;
        
        set_all_LED_Colors(get_color_packet(r,g,b));
        
    }

void initalize_LEDs(uint8_t brightness) {
    // Initialize StripLights   
    StripLights_Start();  
    
	if(brightness > 4) brightness = 4;
	// Set dim level 0 = full power, 4 = lowest power
    StripLights_Dim(brightness); 
	
	// Clear all memory to orange
	StripLights_MemClear(StripLights_ORANGE);
    StripLights_Trigger(1);    
}

void set_all_LED_Colors(uint32_t color) {
    if(StripLights_Ready()) {
        for(uint8_t ledPosition = 0; ledPosition <= StripLights_TOTAL_LEDS; ledPosition++){
           // if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
            StripLights_Pixel(ledPosition, 0, color);
        }
        StripLights_Trigger(1);
    }
}

//0 - 255 for each rgb value
//returns what the striplight library expects for "color"
uint32_t get_color_packet(uint8_t r, uint8_t g, uint8_t b) {
    return (b << 16 | r << 8 | g);
}


/* [] END OF FILE */
