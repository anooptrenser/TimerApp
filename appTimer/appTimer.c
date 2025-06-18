//**************************** Sample program *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : appTimer.c
// Summary  : Gets the time of different zones
// Note     : None
// Author   : Anoop G
// Date     : 17/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include "appTimer.h"
#include<stdbool.h>

//***************************** Local Functions *******************************
//*****************************.IsLeap.****************************************
//Purpose : Determines if a given year is a leap year.
//Inputs  : int year - The year to check.
//Outputs : None
//Return  : int - Returns 1 if the year is a leap year, otherwise 0.
//Notes   : Uses standard leap year rules:
//          Divisible by 4 AND (not divisible by 100 OR divisible by 400).
//*****************************************************************************
static uint8 IsLeapYear(int16 year)
{
    return ((year % LEAP_YEAR_DIVISIBLE_BY_4 == 0) && 
            ((year % LEAP_YEAR_DIVISIBLE_BY_100 != 0) || 
            (year % LEAP_YEAR_DIVISIBLE_BY_400 == 0)));
}

//*****************************.EpochToUtc.************************************
// Purpose  : Converts epoch time (seconds since 1970-01-01 00:00:00 UTC) to
//            a structured UTC date and time.
// Inputs   : time_t epoch - The number of seconds since Unix epoch.
//            DateTime *dt - Pointer to a DateTime structure to store the
//            result.
// Outputs  : None
// Return   : None
// Notes    : Uses leap year calculations to determine year and month.
//            Handles conversion of hours, minutes, and seconds from epoch 
//            time.
//*****************************************************************************
static bool EpochToUtc(time_t epochSeconds, DATE_TIME* pDateTime)
{
    if (epochSeconds < 0 || pDateTime == NULL) 
    {
        return false; 
    }

    int32 lDays = (int32)(epochSeconds / SECONDS_PER_DAY);
    int32 lSecs = (int32)(epochSeconds % SECONDS_PER_DAY);
    int16 nYear = EPOCH_YEAR;
    int8  cMonth = 0;

    pDateTime->cHour = (int8)(lSecs / SECONDS_PER_HOUR);
    pDateTime->cMinute = (int8)((lSecs % SECONDS_PER_HOUR) / SECONDS_PER_MINUTE);
    pDateTime->cSecond = (int8)(lSecs % SECONDS_PER_MINUTE);

    while (1)
    {
        int32 lDaysThisYear = IsLeapYear(nYear) ? LEAP_YEAR : NON_LEAP_YEAR;
        if (lDays >= lDaysThisYear)
        {
            lDays -= lDaysThisYear;
            nYear++;
        }
        else
        {
            break;
        }
    }

    pDateTime->nYear = nYear;

    while (1)
    {
        int8 cDim = DAYS_IN_MONTH[cMonth];
        
        if ((cMonth == 1) && IsLeapYear(nYear))
        {
            cDim++;
        }
        else if (lDays >= cDim)
        {
            lDays -= cDim;
            cMonth++;
        }
        else
        {
            break;
        }
    }

    pDateTime->cMonth = cMonth + 1;
    pDateTime->cDay = lDays + 1;

    return true; 
}

//*****************************.print_time_and_date.***************************
// Purpose  : Displays the formatted time in "HH:MM:SS AM/PM" format and
//            the date in "DD/MM/YYYY" format.
// Inputs   : const DateTime *dt - Pointer to a DateTime structure containing
//            the time and date to print.
// Outputs  : Prints the formatted time and date to the standard output.
// Return   : None
// Notes    : Converts 24-hour format to 12-hour format with AM/PM notation.
//            Pads hour, minute, and second values to ensure two-digit display.
//*****************************************************************************
static void PrintTimeAndDate(const DATE_TIME* pDateTime)
{
    int8 cHour12 = pDateTime->cHour % HOUR_CYCLE;
    if (0 == cHour12)
    {
        cHour12 = HOUR_CYCLE;
    }
    const char* pAmPm = (pDateTime->cHour < HOUR_CYCLE) ? "AM" : "PM";

    printf("Time : %02d:%02d:%02d %s\n", cHour12, pDateTime->cMinute, 
                                         pDateTime->cSecond, pAmPm);
    printf("Date : %02d/%02d/%04d\n", pDateTime->cDay, pDateTime->cMonth,
                                         pDateTime->nYear);
}

//*****************************.DisplayGmt.*************************************
// Purpose  : Displays the current time in UTC (Coordinated Universal Time).
// Inputs   : time_t now - The current epoch time.
// Outputs  : Prints the formatted UTC time and epoch value to standard output.
// Return   : None
// Notes    : Converts epoch time to UTC using EpochToUtc().
//            Uses PrintTimeAndDate() for formatted output.
//*****************************************************************************
static bool DisplayUtc(time_t now)
{
    DATE_TIME utcTime;
   
    if (!EpochToUtc(now, &utcTime))
    {
        printf("UTC conversion failed!\n\n");
        return false;
    }

    printf("UTC (0:00)\n-------------------------\n");
    PrintTimeAndDate(&utcTime);
    printf("Epoch: %ld\n\n", (long)now);

    return true;
}

//*****************************.DisplayIst.*************************************
// Purpose  : Displays the current time in IST (Indian Standard Time, UTC+05:30).
// Inputs   : time_t now - The current epoch time.
// Outputs  : Prints the formatted IST time to standard output.
// Return   : None
// Notes    : Converts epoch time to IST using IST_OFFSET.
//            Uses EpochToUtc() for UTC conversion before applying offset.
//            Calls PrintTimeAndDate() for formatted display.
//*****************************************************************************
static bool DisplayIst(time_t now)
{
    DATE_TIME istTime;
    if (!EpochToUtc(now + IST_OFFSET_SECONDS, &istTime))
    {
        printf("IST conversion failed!\n\n");
        return false;
    }
    
    printf("IST (+05:30)\n-------------------------\n");
    PrintTimeAndDate(&istTime);
    printf("\n");

    return true;
}

//*****************************.DisplayPst.*************************************
// Purpose  : Displays the current time in PST (Pacific Standard Time, UTC-08:00).
// Inputs   : time_t now - The current epoch time.
// Outputs  : Prints the formatted PST time to standard output.
// Return   : None
// Notes    : Converts epoch time to PST using PST_OFFSET.
//            Uses EpochToUtc() for UTC conversion before applying offset.
//            Calls PrintTimeAndDate() for formatted display.
//*****************************************************************************
static bool DisplayPst(time_t now)
{
    DATE_TIME pstTime;

    if (!EpochToUtc(now + PST_OFFSET_SECONDS, &pstTime))
    {
        printf("PST conversion failed!\n\n");
        return false;
    }
    
    printf("PST (-8:00)\n-------------------------\n");
    PrintTimeAndDate(&pstTime);
    printf("\n");

    return true;
}

//*****************************.DisplayTimeAllZones.*************************
// Purpose  : Displays the current time in multiple time zones (UTC, IST, PST).
// Inputs   : None
// Outputs  : Prints the formatted time for UTC, IST, and PST.
// Return   : None
// Notes    : Retrieves the current system time using time(NULL).
//            Calls DisplayUtc(), DisplayIst(), and DisplayPst() sequentially.
//*****************************************************************************
void DisplayTimeAllZones(void)
{
    time_t now = time(NULL);

    if (!DisplayUtc(now))
        return;
    if (!DisplayIst(now))
        return;
    if (!DisplayPst(now))
        return;
}

// EOF       