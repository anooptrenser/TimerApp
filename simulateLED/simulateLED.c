//**************************** Simulate LED ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : simulateLED.c
// Summary  : Simulates LED turning ON or OFF
// Note     : None
// Author   : Anoop G
// Date     : 24/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include <stdbool.h>

//*****************************.DisplayLedStatus.******************************
// Purpose  : Simulates an LED turning ON and OFF by printing "LED ON"
//            and "LED OFF" alternately.
// Inputs   : None
// Outputs  : None
// Return   : None
// Notes    : Uses a static variable to toggle the LED state.
//            Intended to be called repeatedly to simulate blinking.
//*****************************************************************************
void DisplayLedStatus(void)
{
    static bool stblLedOn = false; // Static variable to maintain state

    if (stblLedOn)
    {
        printf("LED ON\n");
    }
    else
    {
        printf("LED OFF\n");
    }

    stblLedOn = !stblLedOn; // Toggle state for next call
}

// EOF