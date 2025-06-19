//**************************** Timer App **************************************
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
#include <stdbool.h>
#include <time.h>
#include "appTimer.h"
#include "common.h"

//***************************** Local Functions *******************************

//*****************************.IsLeap.****************************************
//Purpose : Determines if a given year is a leap year.
//Inputs  : year - The year to check.
//Outputs : None
//Return  : Returns 1 if the year is a leap year, otherwise 0.
//Notes   : Uses standard leap year rules:
//          Divisible by 4 AND (not divisible by 100 OR divisible by 400).
//*****************************************************************************
static uint8 IsLeapYear(int16 nyear)
{
    return ((nyear % LEAP_YEAR_DIVISIBLE_BY_4 == 0) && 
            ((nyear % LEAP_YEAR_DIVISIBLE_BY_100 != 0) || 
            (nyear % LEAP_YEAR_DIVISIBLE_BY_400 == 0)));
}

//*****************************.EpochToUtc.************************************
// Purpose  : Converts epoch time (seconds since 1970-01-01 00:00:00 UTC) to
//            a structured UTC date and time.
// Inputs   : lepochSeconds - The number of seconds since Unix epoch.
//            pDateTime - Pointer to a DateTime structure to store the
//            result.
// Outputs  : None
// Return   : blResult  - 1 for success and 0 for failure
// Notes    : Uses leap year calculations to determine year and month.
//            Handles conversion of hours, minutes, and seconds from epoch 
//            time.
//*****************************************************************************
static bool EpochToUtc(time_t lepochSeconds, DATE_TIME* pDateTime)
{
    bool blResult = false; 
    int8 cMonth = 0;
    int8 cDaysInMonth = 0;

    int32 lDays = (lepochSeconds / SECONDS_PER_DAY);
    int32 lSecs = (lepochSeconds % SECONDS_PER_DAY);
    int16 nYear = EPOCH_YEAR;

    pDateTime->cHour = (int8)(lSecs / SECONDS_PER_HOUR);
    pDateTime->cMinute = (int8)((lSecs % SECONDS_PER_HOUR) /
                                 SECONDS_PER_MINUTE);
    pDateTime->cSecond = (int8)(lSecs % SECONDS_PER_MINUTE);

    if (lepochSeconds > 0 || pDateTime != NULL)
    {
        while (lDays >= (IsLeapYear(nYear) ? LEAP_YEAR : NON_LEAP_YEAR)) 
        {
            lDays -= (IsLeapYear(nYear) ? LEAP_YEAR : NON_LEAP_YEAR);
            nYear++;
        }

        pDateTime->nYear = nYear;

        for (; cMonth < 12; cMonth++)
        {
            cDaysInMonth = DAYS_IN_MONTH[cMonth];
            if (cMonth == 1 && IsLeapYear(nYear)) cDaysInMonth++;
            if (lDays < cDaysInMonth) break;
            lDays -= cDaysInMonth;
        }

        pDateTime->cMonth = cMonth + 1;
        pDateTime->cDay = lDays + 1;

        blResult = true;
    }
    
    return blResult;
}

//*****************************.print_time_and_date.***************************
// Purpose  : Displays the formatted time in "HH:MM:SS AM/PM" format and
//            the date in "DD/MM/YYYY" format.
// Inputs   : pDateTime - Pointer to a DateTime structure containing
//            the time and date to print.
// Outputs  : Prints the formatted time and date to the standard output.
// Return   : None
// Notes    : Converts 24-hour format to 12-hour format with AM/PM notation.
//            Pads hour, minute, and second values to ensure two-digit display.
//*****************************************************************************
static void PrintTimeAndDate(const DATE_TIME* pDateTime)
{
    int8 cHour12 = pDateTime->cHour % HOUR_CYCLE;
    const char* pAmPm = (pDateTime->cHour < HOUR_CYCLE) ? "AM" : "PM";

    if (0 == cHour12)
    {
        cHour12 = HOUR_CYCLE;
    }

    printf("Time : %02d:%02d:%02d %s\n", cHour12, pDateTime->cMinute, 
                                         pDateTime->cSecond, pAmPm);
    printf("Date : %02d/%02d/%04d\n", pDateTime->cDay, pDateTime->cMonth,
                                         pDateTime->nYear);
}

//*****************************.DisplayGmt.*************************************
// Purpose  : Displays the current time in UTC (Coordinated Universal Time).
// Inputs   : lNow - The current epoch time.
// Outputs  : Prints the formatted UTC time and epoch value to standard output.
// Return   : blResult  - 1 for success and 0 for failure
// Notes    : Converts epoch time to UTC using EpochToUtc().
//            Uses PrintTimeAndDate() for formatted output.
//*****************************************************************************
static bool DisplayUtc(time_t lNow)
{
    bool blResult = false; 
    DATE_TIME stUtcTime = {0};
   
    if (EpochToUtc(lNow, &stUtcTime))
    {
        printf("UTC (0:00)\n-------------------------\n");
        PrintTimeAndDate(&stUtcTime);
        printf("Epoch: %ld\n\n", (long)lNow);
        blResult = true; 
    }
    else
    {
        printf("UTC conversion failed!\n\n");
    }

    return blResult;
}

//*****************************.DisplayIst.*************************************
// Purpose  : Displays the current time in IST (Indian Standard Time, UTC+05:30).
// Inputs   : lNow - The current epoch time.
// Outputs  : Prints the formatted IST time to standard output.
// Return   : blResult  - 1 for success and 0 for failure
// Notes    : Converts epoch time to IST using IST_OFFSET.
//            Uses EpochToUtc() for UTC conversion before applying offset.
//            Calls PrintTimeAndDate() for formatted display.
//*****************************************************************************
static bool DisplayIst(time_t lNow)
{
    bool blResult = false; 
    DATE_TIME stIstTime = {0};

    if (EpochToUtc(lNow + IST_OFFSET_SECONDS, &stIstTime))
    {
        printf("IST (+05:30)\n-------------------------\n");
        PrintTimeAndDate(&stIstTime);
        printf("\n");     
        blResult = true;   
    }
    else
    {
        printf("IST conversion failed!\n\n");
    }
   
    return blResult;
}

//*****************************.DisplayPst.*************************************
// Purpose  : Displays the current time in PST (Pacific Standard Time, UTC-08:00).
// Inputs   : lNow - The current epoch time.
// Outputs  : Prints the formatted PST time to standard output.
// Return   : blResult  - 1 for success and 0 for failure
// Notes    : Converts epoch time to PST using PST_OFFSET.
//            Uses EpochToUtc() for UTC conversion before applying offset.
//            Calls PrintTimeAndDate() for formatted display.
//*****************************************************************************
static bool DisplayPst(time_t lNow)
{
    bool blResult = false; 
    DATE_TIME stPstTime = {0};

    if (EpochToUtc(lNow + PST_OFFSET_SECONDS, &stPstTime))
    {
        printf("PST (-8:00)\n-------------------------\n");
        PrintTimeAndDate(&stPstTime);
        printf("\n");
        blResult = true;   
    }
    else
    {
        printf("PST conversion failed!\n\n");
    }
    
    return blResult;
}

//*****************************.DisplayTimeAllZones.*************************
// Purpose  : Displays the current time in multiple time zones (UTC, IST, PST).
// Inputs   : None
// Outputs  : Prints the formatted time for UTC, IST, and PST.
// Return   : blResult  - 1 for success and 0 for failure
// Notes    : Retrieves the current system time using time(NULL).
//            Calls DisplayUtc(), DisplayIst(), and DisplayPst() sequentially.
//*****************************************************************************
bool DisplayTimeAllZones(void)
{ 
    bool blResult = false;
    time_t lNow = time(NULL);

    if (DisplayUtc(lNow) &&
        DisplayIst(lNow) &&
        DisplayPst(lNow))
    {
        blResult = true;
    }

    return blResult;
}

//******************************.ClearScreen.******************************
// Purpose  : Clears the console screen using ANSI escape sequences.
// Inputs   : None
// Outputs  : None
// Notes    : Requires terminal support for ANSI escape sequences.
//*****************************************************************************
void ClearScreen(void)
{
    printf("\x1b[2J\x1b[H");
}

//******************************.FUNCTION_HEADER.******************************
// Purpose  : Delays program execution for a specified number of milliseconds.
// Inputs   : ulMilliseconds - Number of milliseconds to delay.
// Outputs  : None
// Notes    : Uses busy-wait loop with clock(); may consume CPU resources.
//*****************************************************************************
void DelayMilliseconds(uint32 ulMilliseconds)
{
    clock_t ulStartTime = clock();
    clock_t ulEndTime = ulStartTime + ulMilliseconds * CLOCKS_PER_SEC / 1000;

    while (clock() < ulEndTime);

}

// EOF       