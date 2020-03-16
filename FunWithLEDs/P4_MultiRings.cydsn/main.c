/* ========================================
 *
 *  This project was written to have a little
 *  fun with the NeoPixel LED rings that are 
 *  sold by Adafruit.com.  They use the WS2812
 *  RGB LED modules that allow you to string
 *  a thousand or more RGB LEDs together on a
 *  single IO pin.
 * 
 *  This project takes the "P4_OneRing" project
 *  to the next level by allowing the control
 *  of multiple rings on the same string.
 *
 *  The StripLight component makes using these
 *  module very easy, so you can use your time
 *  to code fun light patterns instead of worrying
 *  about tight timing loops, so enjoy.
 *
 *  To use, make sure you have the "Din" pin to the
 *  GPIO pin that you have connected your LED ring
 *  to.  Also set the "LEDs_per_strip" parameter to
 *  the total number of LEDs in all your rings.  Also
 *  set the constant "RING_LEDS" to the number of LEDs
 *  in a single ring and the "RINGS" constant to the 
 *  number of rings on your string.  You can find 
 *  these constants in the code below. Build the project
 *  then impress your friends and co-workers.
 *
 *  The project will advance through the different 
 *  patterns automatically.  Set the constant
 *  "PATTERN_INTERVAL" for the desired interval.
 *
 *  Pin Din  P02  Serial data to WS2812 module/s
 *      SW1  P07  Mode Switch.
 *
 *  11-18-2014 Mark Hastings  Initial version
 *  11-24-2014 Mark Hastings  Minor changes and comments
 * ========================================
*/
 
#include <project.h>
#include <stdlib.h>

#define RING_LEDS        (12)    // Number of LEDs per ring
#define RINGS            (12)    // Number of rings on a string
#define PATTERN_INTERVAL (10000) // 10 seconds (10,000 msec)

#define ONOFF_RANDOM  0
#define ONOFF_SEQ     1
#define ONOFF_CHASE   2
#define ONOFF_ALLON   3

#define EVEN_MASK  0xAAAAAAAA
#define ODD_MASK   0x55555555

#define CHASE0_MASK  0x6DB6
#define CHASE1_MASK  0xDB6D
#define CHASE2_MASK  0xB6DB

#define SPARKLE_ONE   (0)
#define SPARKLE_MULTI (1)

// Chase pattern array
uint32 chaseArray[3] = {CHASE0_MASK, CHASE1_MASK, CHASE2_MASK };

// Pattern function prototypes
void SingleLED(uint32 delay, uint32 mode);
void RgbChase(uint32 delay, uint32 mode);
void Rainbow(uint32 delay, uint32 mode);
void OppositeRings(uint32 delay, uint32 mode);
void OneColor(uint32 delay, uint32 mode);
void Sparkle(uint32 delay, uint32 mode);
void RingRainbow(uint32 delay, uint32 mode);

// Misc function prototypes
void RingOnOff(uint32 mode);  // Different modes to flash the rings
CY_ISR_PROTO(TicTocIsr);      // Timer ISR
uint32 TimeOut(void);

int32 ticTocCounter = 0;      // Timeout counter

extern const uint32 StripLights_CLUT[ ];  // CLUT (Color lookup table array)

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
	
	isr1_StartEx(TicTocIsr);

	// Loop through the different patterns each time SW1 is pressed.
	for(;;)
	{
		RingRainbow(100, ONOFF_ALLON);
		Sparkle(100, SPARKLE_MULTI);
		Sparkle(150, SPARKLE_ONE);
		OppositeRings(120, ONOFF_ALLON);
		OneColor(250, ONOFF_CHASE);
		OneColor(10, ONOFF_ALLON);
		SingleLED(50, ONOFF_ALLON);
		RgbChase(100, ONOFF_ALLON);
		Rainbow(100, ONOFF_CHASE);  
		Rainbow(100, ONOFF_ALLON);
	}
}

// Simple timer ISR
/************************************************
 *                    TicTocIsr()
 *
 *  Simple Timer ISR
 *
 ************************************************/
CY_ISR(TicTocIsr)
{
    ticTocCounter++;    	
}

/************************************************
 *                    TimeOut()
 *
 *  Check to see if the timer has expired.
 *
 * Return:  1 if timer has expired
 *          0 if timer has not expired
 *
 ************************************************/
uint32 TimeOut(void)
{
    uint32 timeOut = 0;
	if(ticTocCounter > PATTERN_INTERVAL)
	{
	    timeOut = 1;
		ticTocCounter  = 0;
	}
	
	return(timeOut);
}

/************************************************
 *                    SingleLED()
 *
 *  Rotate a single LED around the ring.
 *
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 *
 ************************************************/
void SingleLED(uint32 delay, uint32 mode)
{
    uint32 ledPosition = 0;  // On LED position
	uint32 rings = 0;

	// Loop until SW1 pressed
    for(;;)  
    {
		// Wait for last update to finish
	    while( StripLights_Ready() == 0);                 
		
		// Clear all LEDs to background color
		StripLights_MemClear(StripLights_BLACK);   
		
		// Set the color of a single LED
		for(rings = 0; rings <= RINGS; rings++ )
		{
		    StripLights_Pixel((ledPosition + (rings * RING_LEDS)), 0, StripLights_RED );	
		}
	     

		// Trigger update of all LEDs at once
		RingOnOff(mode);
        StripLights_Trigger(1);    
		
		// Loop delay
        CyDelay(delay);    

		// Advance to next position.  If too far, start back at 0
		ledPosition++;  
		if(ledPosition >= RING_LEDS) ledPosition = 0;

		// If SW1 is pressed, leave loop
		if(SW1_Read() == 0) break; 
		if(TimeOut()) break;
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
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void OppositeRings(uint32 delay, uint32 mode)
{
    uint32 fwdLED = 0;  // Forward LED Position
	uint32 bwdLED = 0;  // Backward LED Postion
	uint32 rings = 0;

	uint32 oldColor;    // Temp Color
	uint32 loop;        // Loop counter
	
	// Loop until button pressed
	for(;;)
	{
		// Loop through one revolution
        for(fwdLED = 0; fwdLED < RING_LEDS; fwdLED++)
	    {
			// Calculate backward LED position
			bwdLED = RING_LEDS - fwdLED;
			
			// Wait for last update to complete
			while( StripLights_Ready() == 0);
			
			
			for(rings = 0; rings <= RINGS; rings++ )
		    {
		       
				// Loop around and dim all the LEDs to create tails
				for(loop = 0; loop < RING_LEDS; loop++)
				{
					oldColor = StripLights_GetPixel((loop + (rings * RING_LEDS)), 0);
					oldColor = (oldColor >> 1) & 0x007F7F7F;
					// stripLights_Pixel(loop, 0, oldColor );	
					StripLights_Pixel((loop + (rings * RING_LEDS)), 0, oldColor );
				}

				// Blend the forward LED with existing colors
				oldColor = StripLights_GetPixel((fwdLED + (rings * RING_LEDS)), 0) | StripLights_GREEN;
			    StripLights_Pixel((fwdLED + (rings * RING_LEDS)), 0, oldColor );
				
				// Blend the backward LED with existing colors
				oldColor = StripLights_GetPixel((bwdLED + (rings * RING_LEDS)), 0) | StripLights_RED;
			    StripLights_Pixel((bwdLED + (rings * RING_LEDS)), 0,  oldColor );
			
			}
			// Udate all the LEDs at once
			RingOnOff(mode);
	        StripLights_Trigger(1);
			
			// Loop delay
			CyDelay(delay);
		
			// Leave loop is SW1 pressed
		    if(SW1_Read() == 0) break;
			
	    }

		// Leave if SW1 pressed
	    if(SW1_Read() == 0) break;
		if(TimeOut()) break;
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
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void RgbChase(uint32 delay, uint32 mode)
{
    uint32 redPosition   = 0; // Initial color LED positions
	uint32 greenPosition = RING_LEDS/3;
	uint32 bluePosition  = (RING_LEDS * 2)/3;
	uint32 rings;
	
	uint32 oldColor;   // Temp color value
	uint32 loop;       // Loop counter
	
	// Loop until SW1 pressed
    for(;;)
    {
		// Wait for last update to complete
		while( StripLights_Ready() == 0);
		
		for(rings = 0; rings <= RINGS; rings++ )
		{
		
			// Loop through and dim all LEDs by half
			for(loop = 0; loop < RING_LEDS; loop++)
			{
				oldColor = StripLights_GetPixel(( loop + (rings * RING_LEDS)), 0);
				oldColor = (oldColor >> 1) & 0x007F7F7F;
				StripLights_Pixel((loop + (rings * RING_LEDS)), 0, oldColor );	
			}
			
			// Set the three LEDs at their new position
		    StripLights_Pixel((redPosition   + (rings * RING_LEDS)), 0,  StripLights_RED );
		    StripLights_Pixel((greenPosition + (rings * RING_LEDS)), 0,  StripLights_GREEN );
			StripLights_Pixel((bluePosition  + (rings * RING_LEDS)), 0,  StripLights_BLUE );
			

		}
		// Trigger to update all the LEDs at once
		RingOnOff(mode);
	     StripLights_Trigger(1);
		
		// Calculate new LED positions around the ring
	    redPosition   = (redPosition + 1)   % RING_LEDS;
	    greenPosition = (greenPosition + 1) % RING_LEDS;
	    bluePosition  = (bluePosition + 1)  % RING_LEDS;
	
		// Loop delay in mSeconds
	        CyDelay(delay);
			
        // If SW1 pressed, leave loop
	    if(SW1_Read() == 0) break;
		if(TimeOut()) break;
	    
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
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void Rainbow(uint32 delay, uint32 mode)
{
    uint32 startColor = 0;  // Index color in colorwheel
	uint32 ledPosition = 0; // LED position when setting color         
    uint32 color = 0;       // Temp color to set LED
	uint32 rings = 0;
	
    for(;;)
    {   
		// Wait for last update to complete
        while( StripLights_Ready() == 0);  
		
		// Set new start color
        color = startColor;    
		
		for(rings = 0; rings <= RINGS; rings++ )
		{
			// Loop through all LEDs giving each one a different color from the color wheel
	        for(ledPosition = 0; ledPosition <= RING_LEDS; ledPosition++)
	        {
	            StripLights_Pixel((ledPosition + (rings * RING_LEDS)), 0, StripLights_getColor( color ));
	            color++;
	            if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
	        }
		}
		
		// Update the LEDs all at once
		RingOnOff(mode);
		StripLights_Trigger(1); 
		
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		startColor++;  
        if(startColor >= StripLights_COLOR_WHEEL_SIZE) startColor = 0;
    
        CyDelay(delay);   // Loop delay

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
		if(TimeOut()) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}

/************************************************
 *                    RingRainbow()
 *
 *  Use the colorwheel section of the color lookup
 *  table to create a rainbow across the rings.
 *  Each ring will have a different color, but the
 *  entire ring will be the same color.
 *
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void RingRainbow(uint32 delay, uint32 mode)
{
    uint32 startColor = 0;  // Index color in colorwheel        
    uint32 color = 0;       // Temp color to set LED
	uint32 ring = 0;
	uint32 xpos1, xpos2;
	
    for(;;)
    {   
		// Wait for last update to complete
        while( StripLights_Ready() == 0);  
		
		color = startColor;
		for(ring = 0; ring <= RINGS; ring++ )
		{
			xpos1 = ring * RING_LEDS;
			xpos2 = xpos1 + RING_LEDS - 1;

			StripLights_DrawLine(xpos1, 0, xpos2, 0, StripLights_CLUT[color]);
			
			color++;
	         if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;
			
		}
		
		startColor++;
		if(startColor >= StripLights_COLOR_WHEEL_SIZE) startColor = 0;
		
		RingOnOff(mode);
	  	StripLights_Trigger(1); 
			
		CyDelay(delay);  // Loop delay
		
	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
		if(TimeOut()) break;
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
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void OneColor(uint32 delay, uint32 mode)
{
    uint32 color;  // Index color in colorwheel
	uint32 nextColor = 0;
	uint32 pct = 0;
	uint32 toColor, fromColor, newColor;
	uint32 ledPosition = 0; // LED position when setting color  
	uint32 rings = 0;
	
	color = rand() % StripLights_COLOR_WHEEL_SIZE;
	
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
	        for(ledPosition = 0; ledPosition <= RING_LEDS; ledPosition++)
	        {
				for(rings = 0; rings <= RINGS; rings++ )
		        {
	                StripLights_Pixel((ledPosition + (rings * RING_LEDS)), 0, newColor);
				}
	        }
 		
		    // Update the LEDs all at once
			RingOnOff(mode);
	  	    StripLights_Trigger(1); 
			
			if(SW1_Read() == 0) break;  // If SW1 pressed leave
			CyDelay(delay);   // Loop delay
	    } 
        // Each time through the main loop start with different color
		// Wrap around at end of color wheel
		color++;  
        if(color >= StripLights_COLOR_WHEEL_SIZE) color = 0;

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
		if(TimeOut()) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}

/************************************************
 *                    Sparkle()
 *
 *  Use the colorwheel to randomly paint rings a
 *  different color.
 *
 * Params:  
 *   delay: Time in msec between loop iterations
 *   mode:  Flash mode.
 ************************************************/
void Sparkle(uint32 delay, uint32 mode)
{
    uint32 color;  // Index color in colorwheel
	uint32 ring;
	uint32 xpos1, xpos2;
	
	
    for(;;)
    { 
		color = rand() % StripLights_COLOR_WHEEL_SIZE;
		ring = rand() % RINGS;
		
		xpos1 = ring * RING_LEDS;
		xpos2 = xpos1 + RING_LEDS - 1;
		
		if(mode == SPARKLE_ONE)
		   StripLights_MemClear(StripLights_BLACK);
		
		StripLights_DrawLine(xpos1, 0, xpos2, 0, StripLights_CLUT[color]);
		
	  	StripLights_Trigger(1); 
			
		CyDelay(delay);   // Loop delay

	    if(SW1_Read() == 0) break;  // If SW1 pressed leave
		if(TimeOut()) break;
    }	
	// Wait for SW1 to be released then delay a bit for debouncing
	while(SW1_Read() == 0);         
	CyDelay(50);
}

/************************************************
 *                  RingOnOff()
 *
 *  A simple function to turn some of the rings
 *  off to simulate a random flash.  This works with
 *  up to 32 rings on a string.
 *
 * Params:  
 *   mode:  ONOFF_RANDOM Randomly turn off rings
 *          ONOFF_CHASE  Create a 2 on, 1 off chase pattern
 *          ONOFF_SEQ    Display only one ring at a time.
 *          ONOFF_ALLON  Leave all rings on.
 ************************************************/
void RingOnOff(uint32 mode)
{
	static uint32 seqPos = 0;
	static uint32 count = 0;
    uint32 ledMask;
	uint32 ring, loop;

    switch(mode)  // Determine the flash methos
	{
	    case ONOFF_RANDOM:
		ledMask = (uint32)rand();
		break;
		
		case ONOFF_CHASE:
		ledMask = chaseArray[count % 3];
		count++;
		break;
		
		case ONOFF_SEQ:
		ledMask = 0x00000001 << seqPos;
		seqPos++;
		if(seqPos >= RINGS) seqPos = 0;
		break;
		
		case ONOFF_ALLON:
		default:
		ledMask = 0xFFFFFFFF;
		break;
	}
	
	for(ring = 0; ring <= RINGS; ring++)
	{
	    if((ledMask & (0x00000001 << ring)) == 0)
		{
		    // Leep througha and turn off the LEDs.
			for(loop = 0; loop < RING_LEDS; loop++)
			{
				StripLights_Pixel((loop + (ring * RING_LEDS)), 0, StripLights_BLACK );
			}	
		}
	}
}





/* [] END OF FILE */
