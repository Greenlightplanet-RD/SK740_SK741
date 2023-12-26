//-------------------------------------------------
//Include Header
#include "CSU32P10.h"
#include "Drv_config.h"
U16 g_u16TempBuf;
S16 g_s16TempBuf1;
S16 g_S16CurrentAdcOffset;
U16  g_u16AdcRegValue[E_ADC_CHL_NB] ;
const U08  u08AdcChanel[E_ADC_CHL_NB]= {LL_ADC_CH4, LL_ADC_CH2};
static void Drc_ADC_Channel(U08 ch)
{
    switch(ch)
    {
        case LL_ADC_CH0:
            MODIFY_REG(SRADCON2, 0x70, 0x00);
            break;
        case LL_ADC_CH1:
            MODIFY_REG(SRADCON2, 0x70, 0x10);
            break;
        case LL_ADC_CH2:
            MODIFY_REG(SRADCON2, 0x70, 0x20);
            break;
        case LL_ADC_CH3:
            MODIFY_REG(SRADCON2, 0x70, 0x30);
            break;
        case LL_ADC_CH4:
            MODIFY_REG(SRADCON2, 0x70, 0x40);
            break;
        default:
            break;
    }
}
void Drv_AdcInit(void)
{
    U08 ch,i;
    MODIFY_REG(SRADCON0, 0x30, (M_SYS_ADC_CLK_DIV<<4));
    MODIFY_REG(SRADCON0, 0x03, M_SYS_ADC_AQC_CLK_CNT);
    MODIFY_REG(METCH2, 0x70, 0x40);
    // SRADCON0=0x13;
}
void delay_50us()//延时10us
{
    int j;
    for(j=0; j<5; j++)
    {
        asm("nop");
    }
}

void AdcData_Update(U08 u08PowerOn)
{
    U08 i ;
    U08 j;
    S16  s16AdcValue;
    for(i = 0; i < E_ADC_CHL_NB; i++)
    {
        if(i==E_ADC_CHL_VBAT)
        {
            SRADCON1=0X80;
            SRADCON2=0XC0;
            // Drc_ADC_Channel(u08AdcChanel[i]);
        }
        else
        {

            SRADCON1=0X82;
            SRADCON2=0XA0;

        }
        delay_50us();
        s16AdcValue=0;
        for(j = 0; j < (8+1); j++)   //8 times
        {
            SRADS=1;
            NOP();
            while(SRADS)
            {
            }
            g_u16TempBuf=SRADH;//(ADCRH << 8);
            g_u16TempBuf <<=8;
            g_u16TempBuf=g_u16TempBuf+SRADL;
            if(j!=0)
            {
                s16AdcValue +=g_u16TempBuf;
            }
        }
        C=0;
        s16AdcValue=s16AdcValue>>3;    //   /K_ADC_SAMPLE_TIMES
        if(i==E_ADC_CHL_LOAD_CURRENT)
        {
            if(u08PowerOn)
            {
                // g_u16AdcRegValue[i]=s16AdcValue;
                //  g_S16CurrentAdcOffset[i]=g_u16AdcRegValue[i];
                g_S16CurrentAdcOffset=s16AdcValue-0x800;
            }
            else
            {
                s16AdcValue -=g_S16CurrentAdcOffset;
                s16AdcValue -=0x800;
                if(s16AdcValue<0)
                {
                    s16AdcValue=0;
                }
                g_u16AdcRegValue[i]=s16AdcValue<<1;
            }
        }
        else
        {
            s16AdcValue -=0x800;
            if(s16AdcValue<0)
            {
                s16AdcValue=0;
            }
            g_u16AdcRegValue[i]=s16AdcValue<<1;
        }
    }

}
void Drv_PWM_Output(U16 u16Value)
{
    if(u16Value>K_PWM_MAX_VALUE)
    {
        u16Value=K_PWM_MAX_VALUE;
    }
    TM3RH=(U08)(u16Value>>8);
    TM3R=(U08)(u16Value);

}

void Drv_PwmInit(void)
{
    TM3CON=0x00;
#if (M_SYS_PWM2_PIN_DEF == E_PWM2_PIN_PT5_0)
    PWM3OUT=1;
#else
    PWM3OUT=0;
#endif
    //PT5EN=0x03;
    PWM3OUT=0x01;
    P3H_OEN=0;
    P3L_OEN =0;

    // PWM2PO=M_SYS_PWM2_PIN_DEF;
    TM3INH=0;
    TM3IN=K_PWM_MAX_VALUE;  //,Freq 20kHz
    PWM_Enable();
}

void Drv_GPIO_Init(void)
{
    PT1EN = K_REG_PT1EN_CONFIG;
    PT1PU = K_REG_PT1PU_CONFIG;

    PT3EN = K_REG_PT3EN_CONFIG;
    PT3PU = K_REG_PT3PU_CONFIG;
    PT3CON=K_REG_PT3CON_CONFIG;
    PT5EN = K_REG_PT5EN_CONFIG;
    PT5PU = K_REG_PT5PU_CONFIG;
    Disable_9287_Power();

}
void Drv_Interrupt_Init(void)
{
    M_TimerIntInit();
    M_KeyIntInit();

}
//1ms
void Drv_SysClkInit(void)
{
    TM0CON  = 0xD0;
    TM0IN   =   124;
    TM0CNT  =   0;
    SysTick_Timer_Enable();
}
void McuRegInit(void)
{
    asm("clrf _STATUS");
    PT1 = 0x00;
    PT3 = 0x00;
    PT5 =   0x00;
    INTE = 0x00;
    INTE2 = 0x00;
    INTF = 0x00;
    INTF2 = 0x00;
}
void Drv_WDG_Init(void)
{
#if(0 == DEBUG)
    // MCK     = 0x00;
    CST_WDT = 0;      //Enable watchdog, 1.024s overflow reset
    WDTCON  = 0x81;
    WDTIN   = 0xff;

#endif
}
void Drv_init(void)
{
    McuRegInit();
    Drv_WDG_Init();
    Drv_GPIO_Init() ;
    Drv_PwmInit();
    Drv_SysClkInit();
    Drv_AdcInit();
    Drv_Interrupt_Init();
    EnableIRQ;
    // Delay(100);
}
void Feed_WatchDog(void)
{
#if(0 == DEBUG)
    CLRWDT();
#endif
}



