/* ========================================
 *
 *  This project was written to have a little
 *  fun with the NeoPixel LED rings that are 
 *  sold by Adafruit.com.  They use the WS2812
 *  RGB LED modules that allow you to string
 *  a thousand or more RGB LEDs together on a
 *  single IO pin.
 *
 *  The StripLight component makes using these
 *  module very easy, so you can use your time
 *  to code fun light patterns instead of worrying
 *  about tight timing loops, so enjoy.
 *
 *  To use, make sure you have the "Din" pin to the
 *  GPIO pin that you have connected your LED ring
 *  to.  Also set the "LEDs_per_strip" parameter to
 *  the number of LEDs in your ring, then build the
 *  project and reprogram your PSoC.
 *
 *  Press the switch to advance to the next pattern.
 *
 *  Pin Din  P02  Serial data to WS2812 module/s
 *      SW1  P07  Mode Switch.
 *
 *  4-2-2014   1.0  Mark Hastings  First code
 *  4-4-2014   1.1  Mark Hastings  Some minor changes
 * 10-5-2014   1.2  Mark Hastings  Added some fun patterns for the LED rings.
 *
 * ========================================
*/
 
#include <project.h>

// Function prototypes for pattern functions.
void SingleLED(uint32 delay);
void RgbChase(uint32 delay);
void Clock(uint32 delay);
void Rainbow(uint32 delay);
void OppositeRings(uint32 delay);
void OneColor(uint32 delay);
void SingleLedMultiColor(uint32 delay);

extern const uint32 StripLights_CLUT[ ];

int main()
{
    // Initialize StripLights
    StripLights_Start();  
	
	// Set dim level 0 = full power, 4 = lowest power
    StripLights_Dim(1); 
	
	// Clear all memory to black
	StripLights_MemClear(StripLights_BLACK);

	// Enable global interrupts, required for StripLights
    CyGlobalIntEnable;    

	// Loop through the different patterns each time SW1 is pressed.
	for(;;)
	{
		SingleLedMultiColor(100);
		OneColor(20);
		SingleLED(50);
		OppositeRings(130);
		RgbChase(100);
		Rainbow(30);
	}
}

/************************************************
 *                    SingleLED()
 *
 *  Rotate a single LED around the ring.
 *
 ************************************************/
void SingleLED(uint32 delay)
{
    uint32 ledPosition = 0;  // On LED position

	// Loop until SW1 pressed
    for(;;)  
    {
		// Wait for last update to finish
	    while( StripLights_Ready() == 0);                 
		
		// Clear all LEDs to background color
		StripLights_MemClear(StripLights_BLACK);   
		
		// Set the color of a single LED
	    StripLights_Pixel(ledPosition, 0, StripLights_RED ); 

		// Trigger update of all LEDs at once
        StripLights_Trigger(1);    
		
		// Loop delay
        CyDelay(delay);    

		// Advance to next position.  If too far, start back at 0
		ledPosition++;  
		if(ledPosition >= StripLights_TOTAL_LEDS) ledPosition = 0;

		// If SW1 is pressed, leave loop
		if(SW1_Read() == 0) break; 
    }	
	
	// Wait for button release and delay to debounce switch
	while(SW1_Read() == 0);   
	CyDelay(50);
}

/************************************************
 *                    SingleLED()
 *
 *  Rotate a single LED around the ring.
 *
 ************************************************/
void SingleLedMultiColor(uint32 delay)
{
    uint32 ledPosition = 0;  // On LED position
	uint32 colorIndex = 0;

	// Loop until SW1 pressed
    for(;;)  
    {
		
		// Wait for last update to finish
	    while( StripLights_Ready() == 0);                 
		
		// Clear all LEDs to background color
		StripLights_MemClear(StripLights_BLACK);   
		
		// Set the color of a single LED
	    StripLights_Pixel(ledPosition, 0,  StripLights_getColor( colorIndex ) ); 

		// Trigger update of all LEDs at once
        StripLights_Trigger(1);    
		
		// Loop delay
        CyDelay(delay);    

		// Advance to next position.  If too far, start back at 0
		ledPosition++;  
		if(ledPosition >= StripLights_TOTAL_LEDS) ledPosition = 0;
		
		colorIndex++;  
        if(colorIndex >= StripLights_COLOR_WHEEL_SIZE) colorIndex = 0;

		// If SW1 is pressed, leave loop
		if(SW1_Read() == 0) break; 
    }	
	
	// Wait for button release and delay to debounce switch
	while(SW1_Read() == 0);   
	CyDelay(50);
}



/************************************************
 *                   OppositeRings()
 *
 *  A green and red LEDs go around the ring in 
 *  opposite directions, with tails.
 *
 ************************************************/
void OppositeRings(uint32 delay)
{
    uint32 fwdLED = 0;  // Forward LED Position
	uint32 bwdLED = 0;  // Backward LED Postion

	uint32 oldColor;    // Temp Color
	uint32 loop;        // Loop counter
	
	// Loop until button pressed
	for(;;)
	{
		// Loop through one revolution
        for(fwdLED = 0; fwdLED < StripLights_TOTAL_LEDS; fwdLED++)
	    {
			// Calculate backward LED position
			bwdLED = StripLights_TOTAL_LEDS - fwdLED;
			
			// Wait for last update to complete
			while( StripLights_Ready() == 0);
			
			// Loop around and dim all the LEDs to create tails
			for(loop = 0; loop < StripLights_TOTAL_LEDS; loop++)
			{
				oldColor = StripLights_GetPixel(loop, 0);
				oldColor = (oldColor >> 1) & 0x007F7F7F;
				StripLights_Pixel(loop, 0, oldColor );	
			}

			// Blend the forward LED with existing colors
			oldColor = StripLights_GetPixel(fwdLED, 0) | StripLights_GREEN;
		    StripLights_Pixel(fwdLED, 0, oldColor );
			
			// Blend the backward LED with existing colors
			oldColor = StripLights_GetPixel(bwdLED, 0) | StripLights_RED;
		    StripLights_Pixel(bwdLED, 0,  oldColor );
			
			// Udate all the LEDs at once
	        StripLights_Trigger(1);
			
			// Loop delay
			CyDelay(delay);
		
			// Leave loop is SW1 pressed
		    if(SW1_Read() == 0) break;
	    }

		// Leave if SW1 pressed
	    if(SW1_Read() == 0) break;
    }
	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);
	CyDelay(50);
}

/************************************************
 *                    RgbChase()
 *
 *  Rotate three LED colors around the ring.
 *  Make tails by dimming the LEDs each time.
 *
 ************************************************/
void RgbChase(uint32 delay)
{
    uint32 redPosition   = 0; // Initial color LED positions
	uint32 greenPosition = StripLights_TOTAL_LEDS/3;
	uint32 bluePosition  = (StripLights_TOTAL_LEDS * 2)/3;
	
	uint32 oldColor;   // Temp color value
	uint32 loop;       // Loop counter
	
	// Loop until SW1 pressed
    for(;;)
    {
		// Wait for last update to complete
		while( StripLights_Ready() == 0);
		
		// Loop through and dim all LEDs by half
		for(loop = 0; loop < StripLights_TOTAL_LEDS; loop++)
		{
			oldColor = StripLights_GetPixel(loop, 0);
			oldColor = (oldColor >> 1) & 0x007F7F7F;
			StripLights_Pixel(loop, 0, oldColor );	
		}
		
		// Set the three LEDs at their new position
	    StripLights_Pixel(redPosition,   0,  StripLights_RED );
	    StripLights_Pixel(greenPosition, 0,  StripLights_GREEN );
		StripLights_Pixel(bluePosition,  0,  StripLights_BLUE );
		
		// Trigger to update all the LEDs at once
        StripLights_Trigger(1);
		
		// Loop delay in mSeconds
        CyDelay(delay);
		
		// Calculate new LED positions around the ring
	    redPosition   = (redPosition + 1)   % StripLights_TOTAL_LEDS;
	    greenPosition = (greenPosition + 1) % StripLights_TOTAL_LEDS;
	    bluePosition  = (bluePosition + 1)  % StripLights_TOTAL_LEDS;
	
        // If SW1 pressed, leave loop
	    if(SW1_Read() == 0) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);
	CyDelay(50);
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
    uint32 startColor = 0;  // Index color in colorwheel
	uint32 ledPosition = 0; // LED position when setting color         
    uint32 color = 0;       // Temp color to set LED
	
    for(;;)
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

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}
/************************************************
 *                    OneColor()
 *
 *  Use the colorwheel section of the color lookup
 *  table to write all LEDs the same color.
 *
 ************************************************/
void OneColor(uint32 delay)
{
    uint32 color = 0;  // Index color in colorwheel
	uint32 nextColor = 0;
	uint32 pct = 0;
	uint32 toColor, fromColor, newColor;
	uint32 ledPosition = 0; // LED position when setting color         
	
    for(;;)
    {   
		nextColor = color + 1;
		if(nextColor >= StripLights_COLOR_WHEEL_SIZE) nextColor = 0;
		
		fromColor = StripLights_CLUT[color];
		toColor   = StripLights_CLUT[nextColor];  

		for(pct = 0; pct <= 100; pct += 10)
		{
		    newColor  = (((pct * (toColor & 0x00FF0000)) + ((100-pct) * (fromColor & 0x00FF0000)))/100) & 0x00FF0000;
            newColor |= (((pct * (toColor & 0x0000FF00)) + ((100-pct) * (fromColor & 0x0000FF00)))/100) & 0x0000FF00;
            newColor |= (((pct * (toColor & 0x000000FF)) + ((100-pct) * (fromColor & 0x000000FF)))/100) & 0x000000FF;	
			
			// Wait for last update to complete
			 while( StripLights_Ready() == 0); 
			
			// Loop through all LEDs giving each one a different color from the color wheel
	        for(ledPosition = 0; ledPosition <= StripLights_TOTAL_LEDS; ledPosition++)
	        {
	            StripLights_Pixel(ledPosition, 0, newColor);
	        }
 		
		    // Update the LEDs all at once
	  	    StripLights_Trigger(1); 
			
			CyDelay(delay);   // Loop delay
	    } 
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		color++;  
        if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}



/* [] END OF FILE */
