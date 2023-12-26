//==============================================
// CSU32P10 Special Register Address Definition
// Date:2017-04-22
// Version: V1.0.0 
//==============================================

#ifndef  _CSU32P10_H
#define  _CSU32P10_H 1

//Data Memory Organization 00h-08h
extern volatile unsigned char IND0                     @ 0x00;     //{ IND0[7:0] }
extern volatile unsigned char FSR0                     @ 0x02;     //{ FSR0[7:0] }
extern volatile unsigned char STATUS                   @ 0x04;     //{ LVD36, LVD24, 0, PD, TO, DC, C, Z }
extern volatile unsigned char WORK                     @ 0x05;     //{ WORK[7:0] }
extern volatile unsigned char INTF                     @ 0x06;     //{ 0, TM2IF, 0, TM0IF, SRADIF, 0, E1IF, E0IF }
extern volatile unsigned char INTE                     @ 0x07;     //{ GIE, TM2IE, 0, TM0IE, SRADIE, 0, E1IE, E0IE }

//Peripheral special registers 0Ah-3Ah
extern volatile unsigned char EADRH                    @ 0x0A;     //{ 0, 0, 0, 0, 0, PAR[9:8] }
extern volatile unsigned char EADRL                    @ 0x0B;     //{ PAR[7:0] }
extern volatile unsigned char EDATH                    @ 0x0C;     //{ 0, 0, EDATH[5:0] }
extern volatile unsigned char WDTCON                   @ 0x0D;     //{ WDTEN, 0, 0, 0, 0, WTS[2:0] }
extern volatile unsigned char WDTIN                    @ 0x0E;     //{ WDTIN[7:0] }
extern volatile unsigned char TM0CON                   @ 0x0F;     //{ T0EN, T0RATE[2:0], 0, T0RSTB, T0SEL[1:0] }
extern volatile unsigned char TM0IN                    @ 0x10;     //{ TM0IN[7:0] }
extern volatile unsigned char TM0CNT                   @ 0x11;     //{ TM0CNT[7:0] }
extern volatile unsigned char MCK                      @ 0x16;     //{ 0, 0, CST_WDT, 0, 0, 0, 0, 0 }
extern volatile unsigned char TM2CON                   @ 0x17;     //{ T2EN, T2RATE[2:0], T2CKS, T2RSTB, T2OUT, PWM2OUT }
extern volatile unsigned char TM2IN                    @ 0x18;     //{ TM2IN[7:0] }
extern volatile unsigned char TM2CNT                   @ 0x19;     //{ TM2CNT[7:0] }
extern volatile unsigned char TM2R                     @ 0x1A;     //{ TM2R[7:0] }
extern volatile unsigned char TM3CON                   @ 0x1B;     //{ T3EN, T3RATE[2:0], T3CKS, T3RSTB, T3OUT, PWM3OUT }
extern volatile unsigned char TM3IN                    @ 0x1C;     //{ TM3IN[7:0] }
extern volatile unsigned char TM3CNT                   @ 0x1D;     //{ TM3CNT[7:0] }
extern volatile unsigned char TM3R                     @ 0x1E;     //{ TM3R[7:0] }
extern volatile unsigned char TM3INH                   @ 0x1F;     //{ 0, 0, 0, 0, TM3INH[11:8] }
extern volatile unsigned char PT1                      @ 0x20;     //{ 0, 0, PT1[5:3], 0, PT1[1:0] }
extern volatile unsigned char PT1EN                    @ 0x21;     //{ 0, 0, PT1EN[5:3], 0, PT1EN[1:0] }
extern volatile unsigned char PT1PU                    @ 0x22;     //{ 0, 0, PT1PU[5:3], 0, PT1PU[1:0] }
extern volatile unsigned char PT1CON                   @ 0x23;     //{ PT11OD, PT1W[3:0], E1M, E0M[1:0] }
extern volatile unsigned char TM2INH                   @ 0x24;     //{ 0, 0, 0, 0, TM2IN[11:8] }
extern volatile unsigned char TM2CNTH                  @ 0x25;     //{ 0, 0, 0, 0, TM2CNT[11:8] }
extern volatile unsigned char TM2RH                    @ 0x26;     //{ 0, 0, 0, 0, TM2R[11:8] }
extern volatile unsigned char TM3CNTH                  @ 0x27;     //{ 0, 0, 0, 0, TM3CNT[11:8] }
extern volatile unsigned char PT3                      @ 0x28;     //{ 0, 0, 0, PT3[4:0] }
extern volatile unsigned char PT3EN                    @ 0x29;     //{ 0, 0, 0, PT3EN[4:0] }
extern volatile unsigned char PT3PU                    @ 0x2A;     //{ 0, 0, 0, PT3PU[4:0] }
extern volatile unsigned char PT3CON                   @ 0x2B;     //{ 0, 0, 0, PT3CON[4:0] }
extern volatile unsigned char TM3RH                    @ 0x2C;     //{ 0, 0, 0, 0, TM3R[11:8] }
extern volatile unsigned char TM3CON2                  @ 0x2D;     //{ DT3CK[1:0], DT3CNT[2:0], DT3_EN, P3H_OEN, P3L_OEN }
extern volatile unsigned char METCH1                   @ 0x2E;     //{ P3HINV, P3LINV, PT1W[6:4], PWM2PO, RST20_SEL, 0 }
extern volatile unsigned char METCH2                   @ 0x2F;     //{ VTHSEL, REF_SEL[2:0], PWMIS, T3RATE, T2RATE, 0 }
extern volatile unsigned char PT5                      @ 0x30;     //{ 0, 0, 0, 0, 0, 0, PT5[1:0] }
extern volatile unsigned char PT5EN                    @ 0x31;     //{ 0, 0, 0, 0, 0, 0, PT5EN[1:0] }
extern volatile unsigned char PT5PU                    @ 0x32;     //{ 0, 0, 0, 0, 0, 0, PT5PU[1:0] }
extern volatile unsigned char PT5CON                   @ 0x33;     //{ 0, 0, 0, 0, 0, 0, PT51OD, PT50OD }
extern volatile unsigned char INTF2                    @ 0x3C;     //{ 0, 0, 0, TM3IF, 0, 0, 0, 0 }
extern volatile unsigned char INTE2                    @ 0x3D;     //{ 0, 0, 0, TM3IE, 0, 0, 0, 0 }
extern volatile unsigned char SRADCON0                 @ 0x34;     //{ 0, 0, SRADACKS[1:0], 0, 0, SRADCKS[1:0] }
extern volatile unsigned char SRADCON1                 @ 0x35;     //{ SRADEN, SRADS, OFTEN, CALIF, ENOV, OFFEX, VREFS[1:0] }
extern volatile unsigned char SRADCON2                 @ 0x36;     //{ CHS[3:0], 0, 0, 0, 0 }
extern volatile unsigned char SRADL                    @ 0x37;     //{ SRAD[7:0] }
extern volatile unsigned char SRADH                    @ 0x38;     //{ 0, 0, 0, 0, SRAD[11:8] }
extern volatile unsigned char SROFTL                   @ 0x39;     //{ SROFT[7:0] }
extern volatile unsigned char SROFTH                   @ 0x3A;     //{ SROFTH[7:0] }

//-------------------------------------------------------
//  STATUS register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit Z                         @ 0x04*8+0;
extern volatile sbit C                         @ 0x04*8+1;
extern volatile sbit DC                        @ 0x04*8+2;
extern volatile sbit TO                        @ 0x04*8+3;
extern volatile sbit PD                        @ 0x04*8+4;
extern volatile sbit LVD24                     @ 0x04*8+6;
extern volatile sbit LVD36                     @ 0x04*8+7;

//-------------------------------------------------------
//  INTF register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit E0IF                      @ 0x06*8+0;
extern volatile sbit E1IF                      @ 0x06*8+1;
extern volatile sbit SRADIF                    @ 0x06*8+3;
extern volatile sbit TM0IF                     @ 0x06*8+4;
extern volatile sbit TM2IF                     @ 0x06*8+6;

//-------------------------------------------------------
//  INTE register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit E0IE                      @ 0x07*8+0;
extern volatile sbit E1IE                      @ 0x07*8+1;
extern volatile sbit SRADIE                    @ 0x07*8+3;
extern volatile sbit TM0IE                     @ 0x07*8+4;
extern volatile sbit TM2IE                     @ 0x07*8+6;
extern volatile sbit GIE                       @ 0x07*8+7;

//-------------------------------------------------------
//  EADRH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PAR_8                     @ 0x0A*8+0;
extern volatile sbit PAR_9                     @ 0x0A*8+1;
extern volatile sbit PAR_10                    @ 0x0A*8+2;

//-------------------------------------------------------
//  EDATH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit EDATH_0                   @ 0x0C*8+0;
extern volatile sbit EDATH_1                   @ 0x0C*8+1;
extern volatile sbit EDATH_2                   @ 0x0C*8+2;
extern volatile sbit EDATH_3                   @ 0x0C*8+3;
extern volatile sbit EDATH_4                   @ 0x0C*8+4;
extern volatile sbit EDATH_5                   @ 0x0C*8+5;

//-------------------------------------------------------
//  WDTCON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit WTS_0                     @ 0x0D*8+0;
extern volatile sbit WTS_1                     @ 0x0D*8+1;
extern volatile sbit WTS_2                     @ 0x0D*8+2;
extern volatile sbit WDTEN                     @ 0x0D*8+7;

//-------------------------------------------------------
//  TM0CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit T0SEL_0                   @ 0x0F*8+0;
extern volatile sbit T0SEL_1                   @ 0x0F*8+1;
extern volatile sbit T0RSTB                    @ 0x0F*8+2;
extern volatile sbit T0RATE_0                  @ 0x0F*8+4;
extern volatile sbit T0RATE_1                  @ 0x0F*8+5;
extern volatile sbit T0RATE_2                  @ 0x0F*8+6;
extern volatile sbit T0EN                      @ 0x0F*8+7;

//-------------------------------------------------------
//  MCK register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit CST_WDT                   @ 0x16*8+5;

//-------------------------------------------------------
//  TM2CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PWM2OUT                   @ 0x17*8+0;
extern volatile sbit T2OUT                     @ 0x17*8+1;
extern volatile sbit T2RSTB                    @ 0x17*8+2;
extern volatile sbit T2CKS                     @ 0x17*8+3;
extern volatile sbit T2RATE_0                  @ 0x17*8+4;
extern volatile sbit T2RATE_1                  @ 0x17*8+5;
extern volatile sbit T2RATE_2                  @ 0x17*8+6;
extern volatile sbit T2EN                      @ 0x17*8+7;

//-------------------------------------------------------
//  TM3CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PWM3OUT                   @ 0x1B*8+0;
extern volatile sbit T3OUT                     @ 0x1B*8+1;
extern volatile sbit T3RSTB                    @ 0x1B*8+2;
extern volatile sbit T3CKS                     @ 0x1B*8+3;
extern volatile sbit T3RATE_0                  @ 0x1B*8+4;
extern volatile sbit T3RATE_1                  @ 0x1B*8+5;
extern volatile sbit T3RATE_2                  @ 0x1B*8+6;
extern volatile sbit T3EN                      @ 0x1B*8+7;

//-------------------------------------------------------
//  TM3INH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM3INH_8                  @ 0x1F*8+0;
extern volatile sbit TM3INH_9                  @ 0x1F*8+1;
extern volatile sbit TM3INH_10                 @ 0x1F*8+2;
extern volatile sbit TM3INH_11                 @ 0x1F*8+3;

//-------------------------------------------------------
//  PT1 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT1_0                     @ 0x20*8+0;
extern volatile sbit PT1_1                     @ 0x20*8+1;
extern volatile sbit PT1_3                     @ 0x20*8+3;
extern volatile sbit PT1_4                     @ 0x20*8+4;
extern volatile sbit PT1_5                     @ 0x20*8+5;

//-------------------------------------------------------
//  PT1EN register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT1EN_0                   @ 0x21*8+0;
extern volatile sbit PT1EN_1                   @ 0x21*8+1;
extern volatile sbit PT1EN_3                   @ 0x21*8+3;
extern volatile sbit PT1EN_4                   @ 0x21*8+4;
extern volatile sbit PT1EN_5                   @ 0x21*8+5;

//-------------------------------------------------------
//  PT1PU register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT1PU_0                   @ 0x22*8+0;
extern volatile sbit PT1PU_1                   @ 0x22*8+1;
extern volatile sbit PT1PU_3                   @ 0x22*8+3;
extern volatile sbit PT1PU_4                   @ 0x22*8+4;
extern volatile sbit PT1PU_5                   @ 0x22*8+5;

//-------------------------------------------------------
//  PT1CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit E0M_0                     @ 0x23*8+0;
extern volatile sbit E0M_1                     @ 0x23*8+1;
extern volatile sbit E1M                       @ 0x23*8+2;
extern volatile sbit PT1W_0                    @ 0x23*8+3;
extern volatile sbit PT1W_1                    @ 0x23*8+4;
extern volatile sbit PT1W_2                    @ 0x23*8+5;
extern volatile sbit PT1W_3                    @ 0x23*8+6;
extern volatile sbit PT11OD                    @ 0x23*8+7;

//-------------------------------------------------------
//  TM2INH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM2IN_8                   @ 0x24*8+0;
extern volatile sbit TM2IN_9                   @ 0x24*8+1;
extern volatile sbit TM2IN_10                  @ 0x24*8+2;
extern volatile sbit TM2IN_11                  @ 0x24*8+3;

//-------------------------------------------------------
//  TM2CNTH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM2CNT_8                  @ 0x25*8+0;
extern volatile sbit TM2CNT_9                  @ 0x25*8+1;
extern volatile sbit TM2CNT_10                 @ 0x25*8+2;
extern volatile sbit TM2CNT_11                 @ 0x25*8+3;

//-------------------------------------------------------
//  TM2RH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM2R_8                    @ 0x26*8+0;
extern volatile sbit TM2R_9                    @ 0x26*8+1;
extern volatile sbit TM2R_10                   @ 0x26*8+2;
extern volatile sbit TM2R_11                   @ 0x26*8+3;

//-------------------------------------------------------
//  TM3CNTH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM3CNT_8                  @ 0x27*8+0;
extern volatile sbit TM3CNT_9                  @ 0x27*8+1;
extern volatile sbit TM3CNT_10                 @ 0x27*8+2;
extern volatile sbit TM3CNT_11                 @ 0x27*8+3;

//-------------------------------------------------------
//  PT3 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT3_0                     @ 0x28*8+0;
extern volatile sbit PT3_1                     @ 0x28*8+1;
extern volatile sbit PT3_2                     @ 0x28*8+2;
extern volatile sbit PT3_3                     @ 0x28*8+3;
extern volatile sbit PT3_4                     @ 0x28*8+4;

//-------------------------------------------------------
//  PT3EN register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT3EN_0                   @ 0x29*8+0;
extern volatile sbit PT3EN_1                   @ 0x29*8+1;
extern volatile sbit PT3EN_2                   @ 0x29*8+2;
extern volatile sbit PT3EN_3                   @ 0x29*8+3;
extern volatile sbit PT3EN_4                   @ 0x29*8+4;

//-------------------------------------------------------
//  PT3PU register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT3PU_0                   @ 0x2A*8+0;
extern volatile sbit PT3PU_1                   @ 0x2A*8+1;
extern volatile sbit PT3PU_2                   @ 0x2A*8+2;
extern volatile sbit PT3PU_3                   @ 0x2A*8+3;
extern volatile sbit PT3PU_4                   @ 0x2A*8+4;

//-------------------------------------------------------
//  PT3CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT3CON_0                  @ 0x2B*8+0;
extern volatile sbit PT3CON_1                  @ 0x2B*8+1;
extern volatile sbit PT3CON_2                  @ 0x2B*8+2;
extern volatile sbit PT3CON_3                  @ 0x2B*8+3;
extern volatile sbit PT3CON_4                  @ 0x2B*8+4;

//-------------------------------------------------------
//  TM3RH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM3R_8                    @ 0x2C*8+0;
extern volatile sbit TM3R_9                    @ 0x2C*8+1;
extern volatile sbit TM3R_10                   @ 0x2C*8+2;
extern volatile sbit TM3R_11                   @ 0x2C*8+3;

//-------------------------------------------------------
//  TM3CON2 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit P3L_OEN                   @ 0x2D*8+0;
extern volatile sbit P3H_OEN                   @ 0x2D*8+1;
extern volatile sbit DT3_EN                    @ 0x2D*8+2;
extern volatile sbit DT3CNT_0                  @ 0x2D*8+3;
extern volatile sbit DT3CNT_1                  @ 0x2D*8+4;
extern volatile sbit DT3CNT_2                  @ 0x2D*8+5;
extern volatile sbit DT3CK_0                   @ 0x2D*8+6;
extern volatile sbit DT3CK_1                   @ 0x2D*8+7;

//-------------------------------------------------------
//  METCH1 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit RST20_SEL                 @ 0x2E*8+1;
extern volatile sbit PWM2PO                    @ 0x2E*8+2;
extern volatile sbit PT1W_4                    @ 0x2E*8+3;
extern volatile sbit PT1W_5                    @ 0x2E*8+4;
extern volatile sbit PT1W_6                    @ 0x2E*8+5;
extern volatile sbit P3LINV                    @ 0x2E*8+6;
extern volatile sbit P3HINV                    @ 0x2E*8+7;

//-------------------------------------------------------
//  METCH2 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit T2RATE                    @ 0x2F*8+1;
extern volatile sbit T3RATE                    @ 0x2F*8+2;
extern volatile sbit PWMIS                     @ 0x2F*8+3;
extern volatile sbit REF_SEL_0                 @ 0x2F*8+4;
extern volatile sbit REF_SEL_1                 @ 0x2F*8+5;
extern volatile sbit REF_SEL_2                 @ 0x2F*8+6;
extern volatile sbit VTHSEL                    @ 0x2F*8+7;

//-------------------------------------------------------
//  PT5 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT5_0                     @ 0x30*8+0;
extern volatile sbit PT5_1                     @ 0x30*8+1;

//-------------------------------------------------------
//  PT5EN register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT5EN_0                   @ 0x31*8+0;
extern volatile sbit PT5EN_1                   @ 0x31*8+1;

//-------------------------------------------------------
//  PT5PU register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT5PU_0                   @ 0x32*8+0;
extern volatile sbit PT5PU_1                   @ 0x32*8+1;

//-------------------------------------------------------
//  PT5CON register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit PT50OD                    @ 0x33*8+0;
extern volatile sbit PT51OD                    @ 0x33*8+1;

//-------------------------------------------------------
//  INTF2 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM3IF                     @ 0x3C*8+4;

//-------------------------------------------------------
//  INTE2 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit TM3IE                     @ 0x3D*8+4;

//-------------------------------------------------------
//  SRADCON0 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit SRADCKS_0                 @ 0x34*8+0;
extern volatile sbit SRADCKS_1                 @ 0x34*8+1;
extern volatile sbit SRADACKS_0                @ 0x34*8+4;
extern volatile sbit SRADACKS_1                @ 0x34*8+5;

//-------------------------------------------------------
//  SRADCON1 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit VREFS_0                   @ 0x35*8+0;
extern volatile sbit VREFS_1                   @ 0x35*8+1;
extern volatile sbit OFFEX                     @ 0x35*8+2;
extern volatile sbit ENOV                      @ 0x35*8+3;
extern volatile sbit CALIF                     @ 0x35*8+4;
extern volatile sbit OFTEN                     @ 0x35*8+5;
extern volatile sbit SRADS                     @ 0x35*8+6;
extern volatile sbit SRADEN                    @ 0x35*8+7;

//-------------------------------------------------------
//  SRADCON2 register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit CHS_0                     @ 0x36*8+4;
extern volatile sbit CHS_1                     @ 0x36*8+5;
extern volatile sbit CHS_2                     @ 0x36*8+6;
extern volatile sbit CHS_3                     @ 0x36*8+7;

//-------------------------------------------------------
//  SRADH register extern volatile sbit map
//-------------------------------------------------------
extern volatile sbit SRAD_8                    @ 0x38*8+0;
extern volatile sbit SRAD_9                    @ 0x38*8+1;
extern volatile sbit SRAD_10                   @ 0x38*8+2;
extern volatile sbit SRAD_11                   @ 0x38*8+3;

#endif
