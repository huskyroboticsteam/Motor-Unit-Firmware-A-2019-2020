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
#pragma once
#include <stdint.h>

void colorShift(uint32_t color1, uint32_t color2,
                uint32_t transition, uint32_t increment);

void set_all_LED_Colors(uint32_t color);
uint32_t get_color_packet(uint8_t r, uint8_t g, uint8_t b);
void initalize_LEDs(uint8_t brightness);

#define LOW_LED_POWER       4
#define MED_LOW_LED_POWER   3
#define MEDIUM_LED_POWER    2
#define MED_HIGH_LED_POWER  1
#define HIGH_LED_POWER      0
/* [] END OF FILE */
