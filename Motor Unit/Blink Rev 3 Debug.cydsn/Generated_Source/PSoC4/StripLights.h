/* ========================================
 *
 * Strip Light Controller
 * By Mark Hastings
 *
 * 05/27/2013  v1.0  Mark Hastings   Initial working version
 *
 * ========================================
*/

#if (!defined(CY_SLIGHTS_StripLights_H))
#define CY_SLIGHTS_StripLights_H

#include "cytypes.h"
#include "cyfitter.h"

/* Function Prototypes */
void   StripLights_Start(void);
void   StripLights_Stop(void);
void   StripLights_WriteColor(uint32 color);
void   StripLights_DisplayClear(uint32 color);
void   StripLights_MemClear(uint32 color);
void   StripLights_Trigger(uint32 rst);
uint32 StripLights_Ready(void);

void   StripLights_DrawRect(int32 x0, int32 y0, int32 x1, int32 y1, int32 fill, uint32 color);
void   StripLights_DrawLine(int32 x0, int32 y0, int32 x1, int32 y1, uint32 color);
void   StripLights_DrawCircle (int32 x0, int32 y0, int32 radius, uint32 color);
void   StripLights_Pixel(int32 x, int32 y, uint32 color);
uint32 StripLights_GetPixel(int32 x, int32 y);
uint32 StripLights_ColorInc(uint32 incValue);
void   StripLights_Dim(uint32 dimLevel); 

#define StripLights_DimLevel_0   0
#define StripLights_DimLevel_1   1
#define StripLights_DimLevel_2   2
#define StripLights_DimLevel_3   3
#define StripLights_DimLevel_4   4




#define StripLights_CIRQ_Enable() CyIntEnable(StripLights_CIRQ__INTC_NUMBER ); 
#define StripLights_CIRQ_Disable() CyIntDisable(StripLights_CIRQ__INTC_NUMBER );
CY_ISR_PROTO(StripLights_CISR);

#define StripLights_FIRQ_Enable() CyIntEnable(StripLights_FIRQ__INTC_NUMBER ); 
#define StripLights_FIRQ_Disable() CyIntDisable(StripLights_FIRQ__INTC_NUMBER );
CY_ISR_PROTO(StripLights_FISR);

/* Register Definitions */
#define StripLights_DATA         (*(reg8 *) StripLights_B_WS2811_dshifter_u0__F0_REG)
#define StripLights_DATA_PTR     ((reg8 *)  StripLights_B_WS2811_dshifter_u0__F0_REG)

#define StripLights_CONTROL      (*(reg8 *) StripLights_B_WS2811_ctrl__CONTROL_REG)
#define StripLights_STATUS       (*(reg8 *) StripLights_B_WS2811_StatusReg__STATUS_REG)

#define StripLights_Period       (*(reg8 *) StripLights_B_WS2811_pwm8_u0__F0_REG)
#define StripLights_Period_PTR   ((reg8 *)  StripLights_B_WS2811_pwm8_u0__F0_REG)

#define StripLights_Compare0     (*(reg8 *) StripLights_B_WS2811_pwm8_u0__D0_REG)
#define StripLights_Compare1     (*(reg8 *) StripLights_B_WS2811_pwm8_u0__D1_REG)

#define StripLights_Period2      (*(reg8 *) StripLights_B_WS2811_pwm8_u0__F1_REG)
#define StripLights_Period2_PTR  ((reg8 *)  StripLights_B_WS2811_pwm8_u0__F1_REG)

#define StripLights_ACTL0_REG    (*(reg8 *) StripLights_B_WS2811_pwm8_u0__DP_AUX_CTL_REG)
#define StripLights_DISABLE_FIFO  0x03


#define StripLights_Channel      (*(reg8 *) StripLights_StringSel_Sync_ctrl_reg__CONTROL_REG)
#define StripLights_Channel_PTR  ((reg8 *)  StripLights_StringSel_Sync_ctrl_reg__CONTROL_REG)



/* Status Register Constants  */
#define StripLights_FIFO_EMPTY       0x01
#define StripLights_FIFO_NOT_FULL    0x02
#define StripLights_STATUS_ENABLE    0x80
#define StripLights_STATUS_XFER_CMPT 0x40

/* Control Register Constants */
#define StripLights_ENABLE         0x01
#define StripLights_DISABLE        0x00
#define StripLights_RESTART        0x02
#define StripLights_CNTL           0x04
#define StripLights_FIFO_IRQ_EN    0x08
#define StripLights_XFRCMPT_IRQ_EN 0x10
#define StripLights_ALL_IRQ_EN     0x18
#define StripLights_NEXT_ROW       0x20

#define StripLights_TRANSFER           1
#define StripLights_TRANSFER_FIRMWARE  0
#define StripLights_TRANSFER_ISR       1
#define StripLights_TRANSFER_DMA       2

#define StripLights_SPEED        
#define StripLights_SPEED_400KHZ 0
#define StripLights_SPEED_800KHZ 1

#define StripLights_MEMORY_TYPE  0
#define StripLights_MEMORY_RGB   0
#define StripLights_MEMORY_LUT   1

#if (CY_PSOC3 || CY_PSOC5LP)
    #define  StripLights_PERIOD     ((BCLK__BUS_CLK__KHZ)/800)
#elif (CY_PSOC4)
    #define  StripLights_PERIOD     ((CYDEV_BCLK__HFCLK__KHZ)/800)
#endif /* CY_PSOC5A */
        

#define  StripLights_DATA_ZERO  ((StripLights_PERIOD * 20)/25) 
#define  StripLights_DATA_ONE   ((StripLights_PERIOD * 12)/25) 


#if (StripLights_SPEED_800KHZ)
    #define StripLights_BYTE_TIME_US 10u
    #define StripLights_WORD_TIME_US 30u
#else
    #define StripLights_BYTE_TIME_US 20u
    #define StripLights_WORD_TIME_US 60u
#endif

#define StripLights_COLUMNS     3
#define StripLights_ROWS        1
#define StripLights_TOTAL_LEDS   (StripLights_COLUMNS*StripLights_ROWS)

#define StripLights_ARRAY_COLS  (int32)(3)
#define StripLights_ARRAY_ROWS  (int32)(1)
#define StripLights_CHIP        (2)
#define StripLights_CHIP_WS2811 1
#define StripLights_CHIP_WS2812 2

#define StripLights_MIN_X        (int32)0u
#define StripLights_MAX_X        (int32)(StripLights_COLUMNS - 1)
#define StripLights_MIN_Y        (int32)0u
#define StripLights_MAX_Y        (int32)(StripLights_ROWS - 1)

//#define StripLights_RBCOLORS     48
#define StripLights_COLOR_WHEEL_SIZE  24

#if(StripLights_CHIP == StripLights_CHIP_WS2812)
#define StripLights_RED_MASK   0x0000FF00
#define StripLights_GREEN_MASK 0x000000FF
#define StripLights_BLUE_MASK  0x00FF0000
#else
#define StripLights_RED_MASK   0x000000FF
#define StripLights_GREEN_MASK 0x0000FF00
#define StripLights_BLUE_MASK  0x00FF0000	
#endif

#if(StripLights_MEMORY_TYPE == StripLights_MEMORY_RGB)
   #define StripLights_getColor( a ) StripLights_CLUT[a]
#else  /* Else use lookup table */
   #define StripLights_getColor( a ) a
#endif


#define StripLights_CWHEEL_SIZE 24
#define StripLights_YELLOW      StripLights_getColor(1)
#define StripLights_GREEN       StripLights_getColor((70 + StripLights_CWHEEL_SIZE))
#define StripLights_ORANGE      StripLights_getColor(20)
#define StripLights_BLACK       StripLights_getColor((0 + StripLights_CWHEEL_SIZE))
#define StripLights_OFF         StripLights_getColor((0 + StripLights_CWHEEL_SIZE))
#define StripLights_LTBLUE      StripLights_getColor((1 + StripLights_CWHEEL_SIZE))
#define StripLights_MBLUE       StripLights_getColor((2 + StripLights_CWHEEL_SIZE))
#define StripLights_BLUE        StripLights_getColor((3 + StripLights_CWHEEL_SIZE))
#define StripLights_LTGREEN     StripLights_getColor((4 + StripLights_CWHEEL_SIZE))
#define StripLights_MGREEN      StripLights_getColor((8 + StripLights_CWHEEL_SIZE))
//#define StripLights_GREEN       (12 + StripLights_CWHEEL_SIZE) 
#define StripLights_LTRED       StripLights_getColor((16 + StripLights_CWHEEL_SIZE)) 
#define StripLights_LTYELLOW    StripLights_getColor((20 + StripLights_CWHEEL_SIZE))
#define StripLights_MGRED       StripLights_getColor((32 + StripLights_CWHEEL_SIZE)) 
#define StripLights_RED         StripLights_getColor((48 + StripLights_CWHEEL_SIZE)) 
#define StripLights_MAGENTA     StripLights_getColor((51 + StripLights_CWHEEL_SIZE))
#define StripLights_WHITE       StripLights_getColor((63 + StripLights_CWHEEL_SIZE)) 

#define StripLights_SPRING_GREEN StripLights_getColor((64 + StripLights_CWHEEL_SIZE)) 
#define StripLights_TURQUOSE    StripLights_getColor((65 + StripLights_CWHEEL_SIZE)) 
#define StripLights_CYAN        StripLights_getColor((66 + StripLights_CWHEEL_SIZE)) 
#define StripLights_OCEAN       StripLights_getColor((67 + StripLights_CWHEEL_SIZE)) 
#define StripLights_VIOLET      StripLights_getColor((68 + StripLights_CWHEEL_SIZE)) 
#define StripLights_RASPBERRY   StripLights_getColor((69 + StripLights_CWHEEL_SIZE)) 
#define StripLights_DIM_WHITE   StripLights_getColor((71 + StripLights_CWHEEL_SIZE)) 
#define StripLights_DIM_BLUE    StripLights_getColor((72 + StripLights_CWHEEL_SIZE)) 
#define StripLights_INVISIBLE   StripLights_getColor((73 + StripLights_CWHEEL_SIZE))

#define StripLights_COLD_TEMP   StripLights_getColor((80 + StripLights_CWHEEL_SIZE)) 
#define StripLights_HOT_TEMP    StripLights_getColor((95 + StripLights_CWHEEL_SIZE)) 

#define StripLights_CLUT_SIZE  (96 + StripLights_CWHEEL_SIZE)

#define StripLights_RESET_DELAY_US  55

#endif  /* CY_SLIGHTS_StripLights_H */

//[] END OF FILE
