/**
 ******************************************************************************
 * @file    types.h
 * @author  GLP SW Team
 * @version 1.0.0
 * @date    Jun-2018
 * @brief   This file provides global type defines
 ******************************************************************************
 */
#ifndef __TYPE_H_
#define __TYPE_H_

#include "CSU32P10.h"


typedef unsigned char  U08;          // unsigned 8 bit integral variable
typedef signed   char  S08;       // signed 8 bit integral variable
typedef unsigned int   U16;         // unsigned 16 bit integral variable
typedef  int   S16;         // signed 16 bit integral variable
typedef unsigned long  U32;      // unsigned 32 bit integral variable
typedef signed   long  S32;      // signed 32 bit integral variable
typedef  sbit  BOOL;


#ifdef NULL
#undef NULL
#endif

#define NULL           0/* should be ((void *) 0) */
#define TRUE  1
#define FALSE  0




// return array x element size
#define M_ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

//#define _nop_() asm("nop")

#define SET_BIT(REG, BIT)     ((REG) |= (BIT))

#define CLEAR_BIT(REG, BIT)   ((REG) &= ~(BIT))

#define READ_BIT(REG, BIT)    ((REG) & (BIT))

#define CLEAR_REG(REG)        ((REG) = (0x0))

#define WRITE_REG(REG, VAL)   ((REG) = (VAL))

#define READ_REG(REG)         ((REG))

#define MODIFY_REG(REG, CLEARMASK, SETMASK)  WRITE_REG((REG), (((READ_REG(REG)) & (~(CLEARMASK))) | (SETMASK)))



#endif

