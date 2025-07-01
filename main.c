//**************************** Timer Application Program **********************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : main.c
// Summary  : Displays real time of different zones
// Note     : None
// Author   : Anoop G
// Date     : 17/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include "appTimer.h"
#include "simulateLED.h"

//***************************** Local Types ***********************************

//***************************** Local Constants *******************************

//***************************** Local Variables *******************************

//***************************** Local Functions *******************************

//*****************************.main.******************************************
// Purpose   : Display time of all zones
// Inputs    : None 
// Outputs   : None
// Return    : 0
// Notes     : None
//*****************************************************************************
int main(void)
{
    while (1)
    {
        ClearScreen();
        DisplayTimeAllZones();
        printf("-------------------------\n"); // Separator for clarity
        DisplayLedStatus(); // Simulate LED ON/OFF
        fflush(stdout);
        DelayMilliseconds(1000);
    }

    return 0;
}

// EOF