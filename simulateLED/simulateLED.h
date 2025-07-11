//**************************** SIMULATE LED HEADER ****************************
// Copyright (c) 2025 Trenser Technology Solutions
// All Rights Reserved
//*****************************************************************************
//
// File     : simulateLED.h
// Summary  : Declarations for LED simulation and Raspberry Pi GPIO control
// Note     : Modularized for simulation and Raspberry Pi hardware
// Author   : Anoop G
// Date     : 24/06/2025
//
//*****************************************************************************

#ifndef _SIMULATELED_H_
#define _SIMULATELED_H_

//***************************** Global Constants *******************************
#ifdef USE_RASPI
#define GPIO_CHIP_NAME    "gpiochip0"
#define GPIO_PIN           17
#define CONSUMER_LABEL    "TimerApp"
#endif

//***************************** Function Declarations *************************
void RaspiGpioInit(void);
void RaspiLedOn(void);
void RaspiLedOff(void);
void DisplayLedStatus(void);

#endif // _SIMULATELED_H_
// EOF
