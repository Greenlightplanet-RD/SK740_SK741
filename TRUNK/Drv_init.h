//======================= Micro define ========================
#ifndef DRV_INIT_H
#define DRV_INIT_H

#include "types.h"

typedef  enum
{
    E_INT_16MHZ_CLK,
    E_EXT_32KHZ_CLK,
} TE_Sys_ClockSrc;
typedef  enum
{
    E_INT_FOC_32KHZ_CLK,
    E_INT_FOC_125KHZ_CLK,
    E_INT_FOC_500KHZ_CLK,
    E_INT_FOC_1MHZ_CLK,
    E_INT_FOC_2MHZ_CLK,
    E_INT_FOC_4MHZ_CLK,
    E_INT_FOC_8MHZ_CLK,
    E_INT_FOC_16MHZ_CLK,
} TE_Sys_ClockFreq;
#define M_SYS_CLK_FREQ                  (E_INT_FOC_4MHZ_CLK)
#if (M_SYS_CLK_FREQ == E_INT_FOC_32KHZ_CLK)
#define K_SYS_CLK_FREQ 32000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_125KHZ_CLK)
#define K_SYS_CLK_FREQ  125000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_500KHZ_CLK)
#define K_SYS_CLK_FREQ  500000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_1MHZ_CLK)
#define K_SYS_CLK_FREQ  1000000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_2MHZ_CLK)
#define K_SYS_CLK_FREQ  2000000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_4MHZ_CLK)
#define K_SYS_CLK_FREQ  4000000
#elif(M_SYS_CLK_FREQ == E_INT_FOC_8MHZ_CLK)
#define K_SYS_CLK_FREQ  8000000
#else
#define K_SYS_CLK_FREQ  16000000
#endif
/*typedef  enum
{
    E_PWM_8BIT,
    E_PWM_9BIT,
    E_PWM_11BIT,
} TE_PWM_BIT;*/
#define E_PWM_8BIT 0
#define E_PWM_9BIT 1
#define E_PWM_11BIT 2





typedef  enum
{
    E_PRE_CLK_DIV1=1,
    E_PRE_CLK_DIV4=4,
    E_PRE_CLK_DIV16=16,
} TE_TIMER_ClockPreDiv;
typedef  enum
{
    E_PWM_PIN_PA1,
    E_PWM_PIN_PA2,
    E_PWM_PIN_PA6,
    E_PWM_PIN_PB0,
    E_PWM_PIN_PB1,
    E_PWM_PIN_PB2,
    E_PWM_PIN_PB3,
} TE_Sys_Pwm_Pin;

/*
typedef  enum
{
    E_ADC_CLK_1DIV,
    E_ADC_CLK_2DIV,
    E_ADC_CLK_4DIV,
    E_ADC_CLK_8DIV,
    E_ADC_CLK_16DIV,
    E_ADC_CLK_32DIV,
    E_ADC_CLK_64DIV,
} TE_Adc_CLK_DIV;*/
#define E_ADC_CLK_1DIV 0x0
#define E_ADC_CLK_2DIV 0x1
#define E_ADC_CLK_4DIV 0x2
#define E_ADC_CLK_8DIV 0x3

#define E_ADC_ACQ_16CLK 0x0
#define E_ADC_ACQ_8CLK 0x1
#define E_ADC_ACQ_4CLK 0x2
#define E_ADC_ACQ_2CLK 0x3

#define E_PWM2_PIN_PT5_0 0x0
#define E_PWM2_PIN_PT3_1 0x1



typedef  enum
{
    E_ADC_REF_VDD,
    E_ADC_REF_V4V,
    E_ADC_REF_V3V,
    E_ADC_REF_V2V1,
    E_ADC_REF_EXT,
} TE_Adc_Ref_Type;
typedef enum
{
    LL_ADC_CH0 = 0,
    LL_ADC_CH1,
    LL_ADC_CH2,
    LL_ADC_CH3,
    LL_ADC_CH4,
    LL_ADC_8VDD,
    LL_ADC_CH_REF,
    LL_ADC_CH_GND,
    LL_ADC_CH_NULL,
} TE_ADC_CHANNEL;
typedef enum
{
    E_ADC_CHL_VBAT,
    E_ADC_CHL_LOAD_CURRENT,
    E_ADC_CHL_NB,
} TE_AdcChanneltype;
typedef enum
{
    E_POWER_UNDERLOW=0,
    E_POWER_LOWER,
    E_POWER_NORMAL,
    E_POWER_OVERHIGH,


} TE_PowerState;

typedef enum
{
    E_LED_OFF=0,
    E_LED_MODE1,
    E_LED_MODE2,
    E_LED_MODE3,
} TE_LED_Mode;



//#define E_ADC_CHL_VBAT 0
//#define E_ADC_CHL_LOAD_CURRENT 1
//#define E_ADC_CHL_NB 2
//const TE_AdcChanneltype  yyr;





// task periodic calls elapsed time, unit: ms

extern S16 g_S16CurrentAdcOffset;

extern U16 g_u16TempBuf;
extern S16 g_s16TempBuf1;
//extern U08 g_u08TempBuf;
extern U16  g_u16AdcRegValue[E_ADC_CHL_NB];
extern TE_LED_Mode g_eLEDmode;
extern U08 g_u08SleepDelay;
extern TE_PowerState g_ePowerState;
void Drv_GPIO_Init(void);
void Drv_SystemClockInit(void);
void Drv_PwmInit(void);
void Drv_PWM_Output(U16 u16Value);
void Drv_AdcInit(void);
static void Drc_ADC_Channel(U08 ch);
void AdcData_Update(U08 u08PowerOn);

void HMI_KeypadProcess(void);
void Drv_init(void);

void Feed_WatchDog(void);
void Drv_WDG_Init(void);
void Drv_Interrupt_Init(void) ;
void Drv_SysClkInit(void);





#endif
