//**************************** Sample program *********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : main.c
// Summary  : Calculate time
// Note     : None
// Author   : Anoop G
// Date     : 17/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include <windows.h> 
#include "appTimer/appTimer.h"

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
    while (1) {
        system("cls"); 
        DisplayTimeAllZones();
        fflush(stdout);
        Sleep(1000); 
    }
    return 0;
}


// EOF