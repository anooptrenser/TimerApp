//**************************** Sample program *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : appTimer.h
// Summary  : appTimer Header file
// Note     : None
// Author   : Anoop G
// Date     : 17/06/2025
//
//*****************************************************************************
#ifndef _APPTIMER_H_
#define _APPTIMER_H_

//***************************** Include Files *********************************
#include <time.h>
#include <stdbool.h>
#include "common.h"

//****************************** Constants ************************************
#define SECONDS_PER_DAY               86400
#define SECONDS_PER_HOUR              3600
#define SECONDS_PER_MINUTE            60

#define IST_OFFSET_SECONDS            19800   // +5:30 in seconds
#define PST_OFFSET_SECONDS           -28800   // -8:00 in seconds
#define HOUR_CYCLE                    12
#define LEAP_YEAR_DIVISIBLE_BY_4      4
#define LEAP_YEAR_DIVISIBLE_BY_100    100
#define LEAP_YEAR_DIVISIBLE_BY_400    400
#define EPOCH_YEAR                    1970
#define LEAP_YEAR                     366
#define NON_LEAP_YEAR                 365
#define MONTHS                        12

//******************************* Global Types ******************************** 
typedef struct _DATE_TIME_
{
    int16 nYear;
    int8  cMonth;
    int8  cDay;
    int8  cHour;
    int8  cMinute;
    int8  cSecond;
} DATE_TIME;

static const int8 DAYS_IN_MONTH[MONTHS] = {31, 28, 31, 30, 31, 30,
                                            31, 31, 30, 31, 30, 31};

//***************************** Function Declarations **************************
bool DisplayTimeAllZones(void);
void ClearScreen(void);
void DelayMilliseconds(uint32 ulMilliseconds);

#endif //_APPTIMER_H_
// EOF
