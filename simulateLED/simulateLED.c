//**************************** SIMULATE LED ***********************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : simulateLED.c
// Summary  : Simulates or controls LED turning ON or OFF
// Note     : Modularized for simulation and Raspberry Pi hardware
// Author   : Anoop G
// Date     : 24/06/2025
//
//*****************************************************************************

//***************************** Include Files *********************************
#include <stdio.h>
#include <stdbool.h>
#include "simulateLED.h"
#ifdef USE_RASPI
#include <gpiod.h>
#endif

//***************************** Local Variables *******************************
#ifdef USE_RASPI
static struct gpiod_chip *spChip = NULL;
static struct gpiod_line *spLine = NULL;
#endif

//******************************.RaspiGpioInit.*******************************
// Purpose  : Initialize GPIO for LED control on Raspberry Pi
// Inputs   : None
// Outputs  : None
// Notes    : Uses libgpiod to configure GPIO 17 as output
//*****************************************************************************
void RaspiGpioInit(void)
{
#ifdef USE_RASPI

    spChip = gpiod_chip_open_by_name(GPIO_CHIP_NAME);

    if (NULL == spChip)
    {
        perror("gpiod_chip_open_by_name");
        return;
    }

    spLine = gpiod_chip_get_line(spChip, GPIO_PIN);

    if (NULL == spLine)
    {
        perror("gpiod_chip_get_line");
        gpiod_chip_close(spChip);
        spChip = NULL;
        return;
    }

    if (0 > gpiod_line_request_output(spLine, CONSUMER_LABEL, 0))
    {
        perror("gpiod_line_request_output");
        gpiod_chip_close(spChip);
        spChip = NULL;
        spLine = NULL;
        return;
    }

#endif
}

//******************************.RaspiLedOn.**********************************
// Purpose  : Set the LED GPIO line HIGH (turn LED ON)
// Inputs   : None
// Outputs  : None
// Notes    : Uses libgpiod to set value
//*****************************************************************************
void RaspiLedOn(void)
{
#ifdef USE_RASPI

    if (NULL != spLine)
    {
        gpiod_line_set_value(spLine, 1);
    }

#endif
}

//******************************.RaspiLedOff.*********************************
// Purpose  : Set the LED GPIO line LOW (turn LED OFF)
// Inputs   : None
// Outputs  : None
// Notes    : Uses libgpiod to clear value
//*****************************************************************************
void RaspiLedOff(void)
{
#ifdef USE_RASPI

    if (NULL != spLine)
    {
        gpiod_line_set_value(spLine, 0);
    }

#endif
}

//******************************.DisplayLedStatus.****************************
// Purpose  : Simulates an LED turning ON and OFF by printing "LED ON"
//            and "LED OFF" alternately.
// Inputs   : None
// Outputs  : None
// Notes    : Uses a static variable to toggle the LED state.
//*****************************************************************************
void DisplayLedStatus(void)
{
    static bool sblLedOn = false;

    if (sblLedOn)
    {
        printf("LED ON\n");
    }
    else
    {
        printf("LED OFF\n");
    }

    sblLedOn = !sblLedOn;
}

// EOF
