/* ========================================
 *
 * Strip Light Controller
 * By Mark Hastings
 *
 * 05/27/2013  v1.0  Mark Hastings   Initial working version
 *
 * ========================================
*/

#if (!defined(CY_SLIGHTS_StripLights_1_H))
#define CY_SLIGHTS_StripLights_1_H

#include "cytypes.h"
#include "cyfitter.h"

/* Function Prototypes */
void   StripLights_1_Start(void);
void   StripLights_1_Stop(void);
void   StripLights_1_WriteColor(uint32 color);
void   StripLights_1_DisplayClear(uint32 color);
void   StripLights_1_MemClear(uint32 color);
void   StripLights_1_Trigger(uint32 rst);
uint32 StripLights_1_Ready(void);

void   StripLights_1_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, uint32 color);
void   StripLights_1_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, uint32 color);
void   StripLights_1_DrawCircle (int32 x0, int32 y0, int32 radius, uint32 color);
void   StripLights_1_Pixel(int32 x, int32 y, uint32 color);
uint32 StripLights_1_GetPixel(int32 x, int32 y);
uint32 StripLights_1_ColorInc(uint32 incValue);
void   StripLights_1_Dim(uint32 dimLevel); 

#define StripLights_1_DimLevel_0   0
#define StripLights_1_DimLevel_1   1
#define StripLights_1_DimLevel_2   2
#define StripLights_1_DimLevel_3   3
#define StripLights_1_DimLevel_4   4




#define StripLights_1_CIRQ_Enable() CyIntEnable(StripLights_1_CIRQ__INTC_NUMBER ); 
#define StripLights_1_CIRQ_Disable() CyIntDisable(StripLights_1_CIRQ__INTC_NUMBER );
CY_ISR_PROTO(StripLights_1_CISR);

#define StripLights_1_FIRQ_Enable() CyIntEnable(StripLights_1_FIRQ__INTC_NUMBER ); 
#define StripLights_1_FIRQ_Disable() CyIntDisable(StripLights_1_FIRQ__INTC_NUMBER );
CY_ISR_PROTO(StripLights_1_FISR);

/* Register Definitions */
#define StripLights_1_DATA         (*(reg8 *) StripLights_1_B_WS2811_dshifter_u0__F0_REG)
#define StripLights_1_DATA_PTR     ((reg8 *)  StripLights_1_B_WS2811_dshifter_u0__F0_REG)

#define StripLights_1_CONTROL      (*(reg8 *) StripLights_1_B_WS2811_ctrl__CONTROL_REG)
#define StripLights_1_STATUS       (*(reg8 *) StripLights_1_B_WS2811_StatusReg__STATUS_REG)

#define StripLights_1_Period       (*(reg8 *) StripLights_1_B_WS2811_pwm8_u0__F0_REG)
#define StripLights_1_Period_PTR   ((reg8 *)  StripLights_1_B_WS2811_pwm8_u0__F0_REG)

#define StripLights_1_Compare0     (*(reg8 *) StripLights_1_B_WS2811_pwm8_u0__D0_REG)
#define StripLights_1_Compare1     (*(reg8 *) StripLights_1_B_WS2811_pwm8_u0__D1_REG)

#define StripLights_1_Period2      (*(reg8 *) StripLights_1_B_WS2811_pwm8_u0__F1_REG)
#define StripLights_1_Period2_PTR  ((reg8 *)  StripLights_1_B_WS2811_pwm8_u0__F1_REG)

#define StripLights_1_ACTL0_REG    (*(reg8 *) StripLights_1_B_WS2811_pwm8_u0__DP_AUX_CTL_REG)
#define StripLights_1_DISABLE_FIFO  0x03


#define StripLights_1_Channel      (*(reg8 *) StripLights_1_StringSel_Sync_ctrl_reg__CONTROL_REG)
#define StripLights_1_Channel_PTR  ((reg8 *)  StripLights_1_StringSel_Sync_ctrl_reg__CONTROL_REG)



/* Status Register Constants  */
#define StripLights_1_FIFO_EMPTY       0x01
#define StripLights_1_FIFO_NOT_FULL    0x02
#define StripLights_1_STATUS_ENABLE    0x80
#define StripLights_1_STATUS_XFER_CMPT 0x40

/* Control Register Constants */
#define StripLights_1_ENABLE         0x01
#define StripLights_1_DISABLE        0x00
#define StripLights_1_RESTART        0x02
#define StripLights_1_CNTL           0x04
#define StripLights_1_FIFO_IRQ_EN    0x08
#define StripLights_1_XFRCMPT_IRQ_EN 0x10
#define StripLights_1_ALL_IRQ_EN     0x18
#define StripLights_1_NEXT_ROW       0x20

#define StripLights_1_TRANSFER           0
#define StripLights_1_TRANSFER_FIRMWARE  0
#define StripLights_1_TRANSFER_ISR       1
#define StripLights_1_TRANSFER_DMA       2

#define StripLights_1_SPEED        
#define StripLights_1_SPEED_400KHZ 0
#define StripLights_1_SPEED_800KHZ 1

#define StripLights_1_MEMORY_TYPE  0
#define StripLights_1_MEMORY_RGB   0
#define StripLights_1_MEMORY_LUT   1

#if (CY_PSOC3 || CY_PSOC5LP)
    #define  StripLights_1_PERIOD     ((BCLK__BUS_CLK__KHZ)/800)
#elif (CY_PSOC4)
    #define  StripLights_1_PERIOD     ((CYDEV_BCLK__HFCLK__KHZ)/800)
#endif /* CY_PSOC5A */
        

#define  StripLights_1_DATA_ZERO  ((StripLights_1_PERIOD * 20)/25) 
#define  StripLights_1_DATA_ONE   ((StripLights_1_PERIOD * 12)/25) 


#if (StripLights_1_SPEED_800KHZ)
    #define StripLights_1_BYTE_TIME_US 10u
    #define StripLights_1_WORD_TIME_US 30u
#else
    #define StripLights_1_BYTE_TIME_US 20u
    #define StripLights_1_WORD_TIME_US 60u
#endif

#define StripLights_1_COLUMNS     3
#define StripLights_1_ROWS        1
#define StripLights_1_TOTAL_LEDS   (StripLights_1_COLUMNS*StripLights_1_ROWS)

#define StripLights_1_ARRAY_COLS  (int32)(3)
#define StripLights_1_ARRAY_ROWS  (int32)(1)
#define StripLights_1_CHIP        (2)
#define StripLights_1_CHIP_WS2811 1
#define StripLights_1_CHIP_WS2812 2

#define StripLights_1_MIN_X        (int32)0u
#define StripLights_1_MAX_X        (int32)(StripLights_1_COLUMNS - 1)
#define StripLights_1_MIN_Y        (int32)0u
#define StripLights_1_MAX_Y        (int32)(StripLights_1_ROWS - 1)

//#define StripLights_1_RBCOLORS     48
#define StripLights_1_COLOR_WHEEL_SIZE  24

#if(StripLights_1_CHIP == StripLights_1_CHIP_WS2812)
#define StripLights_1_RED_MASK   0x0000FF00
#define StripLights_1_GREEN_MASK 0x000000FF
#define StripLights_1_BLUE_MASK  0x00FF0000
#else
#define StripLights_1_RED_MASK   0x000000FF
#define StripLights_1_GREEN_MASK 0x0000FF00
#define StripLights_1_BLUE_MASK  0x00FF0000	
#endif

#if(StripLights_1_MEMORY_TYPE == StripLights_1_MEMORY_RGB)
   #define StripLights_1_getColor( a ) StripLights_1_CLUT[a]
#else  /* Else use lookup table */
   #define StripLights_1_getColor( a ) a
#endif


#define StripLights_1_CWHEEL_SIZE 24
#define StripLights_1_YELLOW      StripLights_1_getColor(1)
#define StripLights_1_GREEN       StripLights_1_getColor((70 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_ORANGE      StripLights_1_getColor(20)
#define StripLights_1_BLACK       StripLights_1_getColor((0 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_OFF         StripLights_1_getColor((0 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_LTBLUE      StripLights_1_getColor((1 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_MBLUE       StripLights_1_getColor((2 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_BLUE        StripLights_1_getColor((3 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_LTGREEN     StripLights_1_getColor((4 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_MGREEN      StripLights_1_getColor((8 + StripLights_1_CWHEEL_SIZE))
//#define StripLights_1_GREEN       (12 + StripLights_1_CWHEEL_SIZE) 
#define StripLights_1_LTRED       StripLights_1_getColor((16 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_LTYELLOW    StripLights_1_getColor((20 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_MGRED       StripLights_1_getColor((32 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_RED         StripLights_1_getColor((48 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_MAGENTA     StripLights_1_getColor((51 + StripLights_1_CWHEEL_SIZE))
#define StripLights_1_WHITE       StripLights_1_getColor((63 + StripLights_1_CWHEEL_SIZE)) 

#define StripLights_1_SPRING_GREEN StripLights_1_getColor((64 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_TURQUOSE    StripLights_1_getColor((65 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_CYAN        StripLights_1_getColor((66 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_OCEAN       StripLights_1_getColor((67 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_VIOLET      StripLights_1_getColor((68 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_RASPBERRY   StripLights_1_getColor((69 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_DIM_WHITE   StripLights_1_getColor((71 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_DIM_BLUE    StripLights_1_getColor((72 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_INVISIBLE   StripLights_1_getColor((73 + StripLights_1_CWHEEL_SIZE))

#define StripLights_1_COLD_TEMP   StripLights_1_getColor((80 + StripLights_1_CWHEEL_SIZE)) 
#define StripLights_1_HOT_TEMP    StripLights_1_getColor((95 + StripLights_1_CWHEEL_SIZE)) 

#define StripLights_1_CLUT_SIZE  (96 + StripLights_1_CWHEEL_SIZE)

#define StripLights_1_RESET_DELAY_US  55

#endif  /* CY_SLIGHTS_StripLights_1_H */

//[] END OF FILE
