#ifndef     _Drv_config_h
#define     _Drv_config_h 1

#include "CSU32P10.h"
#include "types.h"
#include "Drv_init.h"

#define DEBUG 0
#define  PwmLedpin   PT5_0
#define  VinEn   PT3_3

#define EnableVin()                     VinEn = 1
#define DisableVin()                    VinEn = 0

#define Enable_9287_Power()             PT1_1 = 1 //__Asm NOP
#define Disable_9287_Power()            PT1_1 = 0 //__Asm NOP
#define K_MODEL_IDENTFY_PIN_2             PT1_5
#define K_MODEL_IDENTFY_PIN_3             PT1_4


#define CLRWDT() asm("clrwdt")         // Clear Watch dog count 
#define NOP()    asm("nop")         // Nop instruct 
#define Sleep()   asm("sleep")        // Sleep instruct 

#define M_SYS_ADC_CLK_DIV    (E_ADC_CLK_4DIV)
#define M_SYS_ADC_AQC_CLK_CNT    (E_ADC_ACQ_4CLK)
#define M_SYS_PWM2_PIN_DEF    (E_PWM2_PIN_PT5_0)



//#define K_SK705_ADC_INPUT_VOLTAGE_HYSTERESIS  101   // 0.5*4096*(0.39/(2+0.39))/3.3 = x *202.5

#define K_SK740_MODE1_120LM_ADC_L             87      // Mode-1 current adjust current range Lowest  3R
#define K_SK740_MODE1_120LM_ADC_H             90      // Mode-1 current adjust current range Highest
#define K_SK740_LED_MODE_1_PWM_DUTY       18      // Mode-1 default PWM duty
#define K_SK740_LED_MODE_2_PWM_DUTY       32      // Mode-2 default PWM duty
#define K_SK740_LED_MODE_3_PWM_DUTY       64      // Mode-3 default PWM duty

#define K_SK741_MODE1_220LM_ADC_L             68      // Mode-1 current adjust current range Lowest    1.6R
#define K_SK741_MODE1_220LM_ADC_H             71      // Mode-1 current adjust current range Highest
#define K_SK741_LED_MODE_1_PWM_DUTY       16      // Mode-1 default PWM duty
#define K_SK741_LED_MODE_2_PWM_DUTY       34      // Mode-2 default PWM duty
#define K_SK741_LED_MODE_3_PWM_DUTY       68      // Mode-3 default PWM d
//#define K_SK704_ADC_INPUT_VOLTAGE_HIGH        2835  // 14*4096*(0.39/(2+0.39))/3.3 = x *202.5     
//#define K_SK704_ADC_INPUT_VOLTAGE_LOW         1012  // 5*4096*(0.39/(2+0.39))/3.3 = x *202.5


#define K_SK705_MODE1_400LM_CURRENT_THD_ADC             1097   //250mA
#define ADC14V          2835         // 14*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value 
#define ADC13DOT5V      2734         // 13.5*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value 
#define ADC9V           1822         // 9*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value 
#define ADC9DOT5V       1924         // 9.5*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value 
#define ADC7V           1417         // 7*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value
#define ADC7DOT5V       1519         // 7.5*4096*(0.39/(2+0.39))/3.3 count 14V ADC Value





#define K_ADC_SAMPLE_TIMES                   (8)

#define K_PWM_MAX_VALUE                   (199)

#define SysTick_Timer_Enable()    T0EN=1
#define SysTick_Timer_Disable()    T0EN=0

#define ADC_Enable()    SRADEN=1
#define ADC_Disable()    SRADEN=0


#define PWM_Enable()    T3EN=1
#define PWM_Disable()    T3EN=0
#define EnableWatchdogClock()           CST_WDT=0    // Enable Watchdog 
#define DisableWatchdogClock()          CST_WDT = 1    // Disable Watchdog on low power mode 


#define K_KEY_INPUT_PIN                 PT1_3

#define M_PWR_PIN_PRESSED                   (K_KEY_INPUT_PIN == 0)
#define DisableUnusedPeripherals()  {SysTick_Timer_Disable();PwmLedpin=0;ADC_Disable() ;DisableWatchdogClock();Disable_9287_Power();PWM_Disable();}
#define ExitSleepModeConfig()  {EnableWatchdogClock();SysTick_Timer_Enable();ADC_Enable();PWM_Enable();}
#define  EnableIRQ  {GIE =1;}
#define  DisableIRQ  {GIE =0;}
#define M_TimerIntInit()    {TM0IE=1;}
#define M_KeyIntInit()    {E1IE = 1;PT1CON=0x14;}

#define K_REG_PT1EN_CONFIG                0x02     //PT1_1 Output   Enable_9287_PIN        
#define K_REG_PT1PU_CONFIG              0x39

#define K_REG_PT3EN_CONFIG                0x08
#define K_REG_PT3PU_CONFIG              0x01
#define K_REG_PT3CON_CONFIG              0x16

#if (M_SYS_PWM2_PIN_DEF == E_PWM2_PIN_PT5_0)
#define K_REG_PT5EN_CONFIG                0x03
#define K_REG_PT5PU_CONFIG              0x01

#else
#define K_REG_PT5EN_CONFIG                0x00
#define K_REG_PT5PU_CONFIG              0x00
#endif


#define K_HMI_TASK_PERIOD                   (10)   //MS
#define K_ADC_DATA_TASK_PERIOD                   (3)   //MS
#define K_CHARGE_TASK_PERIOD                   (40)   //MS


#define K_VOLT_DECTECT_LOW_POWER_FILTER            (1000/K_ADC_DATA_TASK_PERIOD)
#define K_VOLT_DECTECT_UNDER_POWER_FILTER            (2500/K_ADC_DATA_TASK_PERIOD)
#define K_VOLT_DECTECT_FILTER            (100/K_ADC_DATA_TASK_PERIOD)

#define K_BUTTON_SHORT_PRESS_TIME           (60)
#define K_HMI_SHORT_PRESS_COUNT             (K_BUTTON_SHORT_PRESS_TIME/K_HMI_TASK_PERIOD)
#define K_LED_ON_DELAY_TIMES                   (100/K_HMI_TASK_PERIOD)



#endif
