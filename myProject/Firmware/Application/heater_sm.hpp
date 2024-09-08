/******************************************************************
 * Title        : Heater State Machine
 * FIlename     : heater_sm.hpp
 * Author       : Adeola Ajala
 * Origin Date  : 07.08.2024
 * Version      : 1.0.0
*****************************************************************/
/*
 Header file for application control of the heaters
*/

#ifndef HEATER_SM_HPP
#define HEATER_SM_HPP
// includes
#include <stdbool.h>

// Potential heater states
typedef enum{
    HEATER_ON,
    HEATER_OFF,
    HEATER_END_STATE
}HeaterState_t;

// Functions
unsigned HeaterSm_Init(unsigned const TimeOnMaxValue);
HeaterState_t HeaterSm_Run(unsigned const SystemTimeNow);
void HeaterSm_StateSet(HeaterState_t const State);
#endif

/*****End of File */