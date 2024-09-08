/***************************************************************************************
 * Title    : Heater State Machine
 * Filename : heater_sm.cpp
 * Author   : Adeola Ajala
****************************************************************************************/
/**************************************************************************************** 
 * Includes
*****************************************************************************************/ 
#include <stdint.h>
#include <stdbool.h>
#include "heater_sm.hpp"
/*****************************************************************************************
 * Virable definations
******************************************************************************************/
static HeaterState_t HeaterState = HEATER_OFF; //holds current state of the heater.
static HeaterState_t HeaterStateRequested = HEATER_OFF; //holds requested heater state.
static unsigned TimeOnMax = 0; //holds duration heater has been turned on.
static unsigned EndTime = 0; //holds time to end heater control.
static bool UpdateTimer = false; //used to indicate if heater off time needs to be updated.
/******************************************************************************************
 * Functions definitions
******************************************************************************************/
/*****************************************************************************************
 * Funtion : HeaterSM_Init(parameter)
 * @section Description
 * This function is used to initialize the heater state machine parameters with
 * system level parameters.
 * 
 * Pre-Condition : None
 * 
 * Post-Condition: The heater state machine parameters will be initialised.
 * 
 * @param unsigned TimeOnMaxValue
 * 
 * @return unsigned TimeOnMax - Maximum time the heater will remain on
 * @see Heater_On
 * @see Heater_Off
*****************************************************************************************/
unsigned HeaterSm_Init(unsigned const TimeOnMaxValue)
{
    if(TimeOnMaxValue < 100)
    {
        TimeOnMax = 100;
    }
    else if(TimeOnMaxValue >= 1000)
    {
        TimeOnMax = 1000;
    }
    else
    {
        TimeOnMax = TimeOnMaxValue;
    }
    return TimeOnMax;
}
/*****************************************************************************************
 * Funtion : HeaterSM_Run(parameter)
 * 
 * @section Description:
 * This function is used to progresss and run the state machine. It should be called
 * periodically
 * 
 * Pre-Condition : Heater_Sm_Init has been executed
 * 
 * Post-Condition: The heater state machine will be executed leaving heater enabled or
 * disabled.
 * 
 * @param   unsigned SystemTimeNow - current system time
 * 
 * @return  HeaterState
*****************************************************************************************/
HeaterState_t HeaterSm_Run(unsigned const SystemTimeNow)
{
    // static HeaterState_t HeaterStateTemp = HEATER_OFF;
    // Mange state transition behavious
    if((HeaterState != HeaterStateRequested)||(UpdateTimer == true))
    {
        HeaterState = HeaterStateRequested;
        if(HeaterState == HEATER_ON)
        {
            EndTime = SystemTimeNow + TimeOnMax;
            UpdateTimer = false;
        }
        else
        {
            EndTime = SystemTimeNow;
        }
    }
    if(SystemTimeNow >= EndTime)
    {
        HeaterState = HEATER_OFF;
        HeaterStateRequested = HEATER_OFF;
    }
    return HeaterState;
}
/*****************************************************************************************
 * Funtion : HeaterSM_StateSet(parameter)
 * @section Description
 * This function is used to request a state change to the heater state machine.
 * 
 * Pre-Condition : None
 * 
 * Post-Condition: The HeaterStateRequest variable will be updated with the desired state
 * 
 * @param HeaterState_t - The desired heater state
 * 
 * @return None
 * @see Heater_StateSet
*****************************************************************************************/
void HeaterSm_StateSet(HeaterState_t const State)
{
    HeaterStateRequested = State;
    // If heater is already enabled, update timer
    if (State == HEATER_ON)
    {
        UpdateTimer = true;
    }
}
/******************************End of File********************************************* */