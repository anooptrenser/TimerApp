//**************************** Timer Application Program **********************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : main.c
// Summary  : Displays real time of different zones or blinks LED on RPi
// Note     : None
// Author   : Anoop G
// Date     : 17/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include "appTimer.h"
#include "simulateLED.h"

//*****************************.main.******************************************
// Purpose   : Display time of all zones or blink LED on RPi
// Inputs    : None 
// Outputs   : None
// Return    : 0
// Notes     : None
//*****************************************************************************
int main(void)
{
#ifdef USE_RASPI

    RaspiGpioInit();
    
    while (1)
    {
        RaspiLedOn();
        DelayMilliseconds(840);
        RaspiLedOff();
        DelayMilliseconds(532);
    }
   
#else
    while (1)
    {
        ClearScreen();
        DisplayTimeAllZones();
        printf("-------------------------\n"); // Separator for clarity
        DisplayLedStatus(); // Simulate LED ON/OFF
        fflush(stdout);
        DelayMilliseconds(1000);
    }
#endif

    return 0;
}

// EOF
