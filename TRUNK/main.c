
//============================================
#include "CSU32P10.h"
#include "Drv_config.h"

// used task ID
typedef enum
{
    //  E_TASK_NULL = 0,
    E_TASK_HMI= 0,
    E_TASK_ADC_DATA,
    E_TASK_CHARG_MNG,
    E_TASK_NB,// Don't over 15
} TE_TaskID;
U08 volatile g_u08SystemMsTick ;  //base 1ms
static U08  s_u08TaskElapsedTime[E_TASK_NB] ;
const U08 TaskPeriod[E_TASK_NB]= {K_HMI_TASK_PERIOD,K_ADC_DATA_TASK_PERIOD,K_CHARGE_TASK_PERIOD};
sbit g_bModel;  //0:SK704, 1:SK705
sbit g_bLightModel;//0:200LM  1:400LM

static U08  s_u08TaskMessage;
U08 g_u08SleepDelay;
U08 g_u8PWMDuty;
U08 g_u08Mode_1_PWM;
U08 g_u08Mode_2_PWM;
U08 g_u08Mode_3_PWM;
U08 g_u8modeAdjStep;
U08 g_u8FilterAdjStep;

U08 g_u8Mode1L;
U08 g_u8Mode1H;
// key filter counter
U08 g_u8keydowncounter;
U08 g_u8keyReleasecounter;

TE_PowerState g_ePowerState;
TE_LED_Mode g_eLEDmode;
void delay()
{
    U16 i;
    for(i=0; i<5000; i++)
    {
        asm("nop");
    }
}
void IdentfyModel(void)
{
    U08 g_u08IdentfyCnt = 0;
    U08 g_u08IdentfyCnt1 = 0;
    U08 i;
    for(i = 0; i < 100; i++)
    {
        if(K_MODEL_IDENTFY_PIN_2 == 1)
        {
            g_u08IdentfyCnt++;
        }
        if(K_MODEL_IDENTFY_PIN_3 == 1)
        {
            g_u08IdentfyCnt1++;
        }
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
        NOP();
    }
    if((g_u08IdentfyCnt1 >= 80)
       &&(g_u08IdentfyCnt >= 80))   //NA
    {
        g_bModel=0;
        g_bLightModel=0;
    }
    else if(g_u08IdentfyCnt1 >= 80)  //PIN2 PIN3: 0 1   SK740 200LM   R14 ON  R15 NC
    {
        g_bModel=1;
        g_bLightModel=0;
    }
    else if(g_u08IdentfyCnt >= 80)  //PIN2 PIN3: 1 0   SK741 400LM   R14 NC  R15 ON
    {
        g_bModel=1;
        g_bLightModel=1;

    }
    else                           //NA
    {
        g_bModel=0;
        g_bLightModel=1;
    }
    /* if(g_u08IdentfyCnt1 >= 80)
     {
         g_bModel=0;      //High Level SK705
     }
     else
     {
         g_bModel=0;     //Low Level SK705

     }*/
    // indentfy model
    if(g_bLightModel)
    {
    //SK741
        g_u8Mode1L = K_SK741_MODE1_220LM_ADC_L;
        g_u8Mode1H = K_SK741_MODE1_220LM_ADC_H;
        g_u08Mode_1_PWM = K_SK741_LED_MODE_1_PWM_DUTY;
        g_u08Mode_2_PWM = K_SK741_LED_MODE_2_PWM_DUTY;
        g_u08Mode_3_PWM = K_SK741_LED_MODE_3_PWM_DUTY;
        //K_MODEL_OUTPUT_PIN = 1;
    }
    else
    {
        //740
        g_u8Mode1L = K_SK740_MODE1_120LM_ADC_L;
        g_u8Mode1H = K_SK740_MODE1_120LM_ADC_H;
        g_u08Mode_1_PWM = K_SK740_LED_MODE_1_PWM_DUTY;
        g_u08Mode_2_PWM = K_SK740_LED_MODE_2_PWM_DUTY;
        g_u08Mode_3_PWM = K_SK740_LED_MODE_3_PWM_DUTY;

        // K_MODEL_OUTPUT_PIN = 0;
    }
    g_u08Mode_1_PWM <<= 1;
    g_u08Mode_2_PWM <<= 1;
    g_u08Mode_3_PWM <<= 1;

}

void HMI_KeypadProcess(void)
{
    static U16  s_u16ButtonPressCounter ;
    static BOOL ShortPressHandled;
    if(K_KEY_INPUT_PIN)//release
    {
        if(g_u8keyReleasecounter < 2)
        {
            g_u8keyReleasecounter++;
            if(g_u8keyReleasecounter == 2)
            {
                g_u8keydowncounter = 0;
            }
        }
    }
    else//press down
    {
        g_u8keyReleasecounter = 0;
        if(g_u8keydowncounter < K_HMI_SHORT_PRESS_COUNT)
        {
            g_u8keydowncounter++;
            if(g_u8keydowncounter == K_HMI_SHORT_PRESS_COUNT)
            {
                if(g_ePowerState == E_POWER_LOWER)
                {
                    if(g_eLEDmode==E_LED_OFF)
                    {
                        g_eLEDmode=E_LED_MODE1;

                    }
                    else
                    {
                        g_eLEDmode=E_LED_OFF;

                    }

                }
                else
                {
                    if(g_eLEDmode >= E_LED_MODE3)
                    {
                        g_eLEDmode = E_LED_OFF;
                    }
                    else
                    {
                        g_eLEDmode++;
                    }
                }


            }
        }
        g_u08SleepDelay=K_LED_ON_DELAY_TIMES;
    }

    // check power first
    if(g_ePowerState == E_POWER_UNDERLOW||g_ePowerState == E_POWER_OVERHIGH)
    {
        g_eLEDmode = E_LED_OFF;
    }
    else if((g_ePowerState == E_POWER_LOWER)
            &&(E_LED_MODE2==g_eLEDmode||E_LED_MODE3==g_eLEDmode))
    {
        g_eLEDmode = E_LED_MODE1;
        g_u8modeAdjStep=0;

    }

    // LED on, delay sleep
    if(g_eLEDmode != E_LED_OFF)
    {
        EnableVin();
        Enable_9287_Power();
    }
    else
    {
        Disable_9287_Power();
        DisableVin();
    }

}
void LEDMode1Auto(void)
{
    if(g_u8modeAdjStep < 10)
    {
        g_u8PWMDuty = g_u08Mode_1_PWM ;
        g_u8modeAdjStep++;
        g_u8FilterAdjStep=0;
    }
    else if(g_u8modeAdjStep < 12)
    {
        if(g_u16AdcRegValue[E_ADC_CHL_LOAD_CURRENT] <= g_u8Mode1L)
        {
            g_u8PWMDuty++;
            g_u8FilterAdjStep=0;
        }
        else if(g_u16AdcRegValue[E_ADC_CHL_LOAD_CURRENT] > g_u8Mode1H)
        {
            if(g_u8PWMDuty > 5)
            {
                g_u8PWMDuty--;
            }
            g_u8FilterAdjStep=0;
        }
        else
        {
            if(g_u8FilterAdjStep>=2)
            {
                g_u8modeAdjStep = 100;
                g_u8FilterAdjStep=0;

            }
            else
            {
                g_u8FilterAdjStep++;
            }

        }
    }
    else
    {

    }
}

void LedAdjust(void)
{
    // PWM control
    switch(g_eLEDmode)
    {
        case E_LED_MODE1:
            LEDMode1Auto();
            //  g_u8PWMDuty=0X10;
            break;

        case E_LED_MODE2:
            g_u8PWMDuty = g_u08Mode_2_PWM;
            break;


        case E_LED_MODE3:
            g_u8PWMDuty = g_u08Mode_3_PWM;
            break;

        case E_LED_OFF:
        default:
            g_u8modeAdjStep = 0;
            g_u8PWMDuty = 0;
            break;
    }
    // g_u8PWMDuty=100;

    Drv_PWM_Output(g_u8PWMDuty);

}

void TaskDataInit(void)
{
    g_u08SleepDelay=K_LED_ON_DELAY_TIMES;
    g_eLEDmode=E_LED_OFF;
    g_ePowerState=E_POWER_UNDERLOW;
    g_u8keydowncounter=0;
    g_u8keyReleasecounter=0;

}
void InputVoltageLevel(void)
{
    static U16 u16Filter;
    TE_PowerState eState=g_ePowerState;
    switch(eState)
    {
        case E_POWER_UNDERLOW:
            if(g_u16AdcRegValue[E_ADC_CHL_VBAT] > ADC14V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_OVERHIGH;
                }
                else
                {
                    u16Filter++;
                }

            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]>ADC9DOT5V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_NORMAL;
                }
                else
                {
                    u16Filter++;
                }
            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]>ADC7DOT5V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_LOWER;
                }
                else
                {
                    u16Filter++;
                }
            }
            else
            {
                u16Filter=0;

            }

            break;
        case E_POWER_LOWER:

            if(g_u16AdcRegValue[E_ADC_CHL_VBAT] > ADC14V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_OVERHIGH;
                }
                else
                {
                    u16Filter++;
                }

            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]>ADC9DOT5V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_NORMAL;
                }
                else
                {
                    u16Filter++;
                }
            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]<ADC7V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_UNDERLOW;
                }
                else
                {
                    u16Filter++;
                }
            }
            else
            {
                u16Filter=0;
            }

            break;
        case E_POWER_NORMAL:
            if(g_u16AdcRegValue[E_ADC_CHL_VBAT] > ADC14V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_OVERHIGH;
                }
                else
                {
                    u16Filter++;
                }

            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]<ADC7V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_UNDERLOW;
                }
                else
                {
                    u16Filter++;
                }
            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]<ADC9V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_LOWER;
                }
                else
                {
                    u16Filter++;
                }
            }
            else
            {
                u16Filter=0;
            }

            break;
        case E_POWER_OVERHIGH:
            if(g_u16AdcRegValue[E_ADC_CHL_VBAT] < ADC7V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_UNDERLOW;
                }
                else
                {
                    u16Filter++;
                }

            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]<ADC9V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_LOWER;
                }
                else
                {
                    u16Filter++;
                }
            }
            else if(g_u16AdcRegValue[E_ADC_CHL_VBAT]<ADC13DOT5V)
            {
                if(u16Filter>=K_VOLT_DECTECT_FILTER)
                {
                    u16Filter=0;
                    eState=E_POWER_NORMAL;
                }
                else
                {
                    u16Filter++;
                }
            }
            else
            {
                u16Filter=0;
            }
            break;
        defalut:
            break;

    }

    if(eState!=g_ePowerState)
    {
        g_ePowerState=eState;

    }

}





void TaskRun(TE_TaskID eTaskID)
{
    // U08 eTaskID;
    switch(eTaskID)
    {
        case E_TASK_HMI:
            if(g_u08SleepDelay !=0)      // Delay to sleep
            {
                --g_u08SleepDelay;
            }
            HMI_KeypadProcess();
            break;
        case E_TASK_ADC_DATA:
            AdcData_Update(0);
            InputVoltageLevel();
            LedAdjust();

            break;
        case E_TASK_CHARG_MNG:

            break;
        case E_TASK_NB:
            break;
        defalut:
            break;

    }
}


/* Brief:   Stop all tasks scheduling
 * Input:   None
 * Output:  None
 * Return:  None
 */
void Task_GiveMessage(TE_TaskID eTaskID)
{
    if((eTaskID >= E_TASK_NB))
    {
        return;
    }
    s_u08TaskMessage |= (1 << eTaskID);
}


/* Brief:   Tasks scheduling function
 * Input:   None
 * Output:  None
 * Return:  None
 */
void TaskScheduling(void)
{
    U08 TaskIndex = 0;
    U08 u08Tmp;
    // Task message process
    for( TaskIndex = 0; TaskIndex < E_TASK_NB; TaskIndex++)
    {
        if(s_u08TaskMessage & (1 << TaskIndex))
        {
            s_u08TaskMessage &= (U16)(~(1 << TaskIndex));
            TaskRun(TaskIndex);
        }
    }

    // Task periodic calls
    for(TaskIndex = 0; TaskIndex < E_TASK_NB; TaskIndex++)
    {
        //  if(TaskPeriod[TaskIndex] != 0)
        {
            u08Tmp=( g_u08SystemMsTick- s_u08TaskElapsedTime[TaskIndex]);
            if( u08Tmp>=TaskPeriod[TaskIndex] )
            {
                s_u08TaskElapsedTime[TaskIndex] = g_u08SystemMsTick;

                TaskRun(TaskIndex);
                //s_stTaskList[TaskIndex].FunTask();
            }
        }

    }

}
void PowerManager(void)
{
    if(g_eLEDmode == E_LED_OFF)
    {

        if(g_u08SleepDelay == 0)
        {
            DisableUnusedPeripherals();
            Sleep();
            NOP();
            NOP();
            NOP();
            NOP();
            NOP();
            ExitSleepModeConfig();

            g_u08SleepDelay=K_LED_ON_DELAY_TIMES;

        }
    }
    else
    {
        g_u08SleepDelay=K_LED_ON_DELAY_TIMES;

    }

}

//============================================
// program start
//============================================
void main()
{
    asm("clrwdt");
    delay();
    Drv_init();
    IdentfyModel();
    TaskDataInit();
    AdcData_Update(1);


    while(1)
    {
        Feed_WatchDog();
        TaskScheduling();
        PowerManager();
    }

}


void INT_FUNCTION(void) interrupt
{
    if(E0IF)
    {
        E0IF=0;
    }

    else if(E1IF)
    {
        E1IF=0;
    }

    else if(TM0IF)
    {
        TM0IF=0;
        g_u08SystemMsTick++;

    }

    else if(TM2IF)
    {
        TM2IF=0;
    }

    else if(TM3IF)
    {
        TM3IF=0;
    }

}



