#include "CppUTest/TestHarness.h"
#include "../Firmware/Application/heater_sm.hpp"
// #include "heater_sm.hpp"

extern "C"
{
	/*
	 * Add your c-only include files here
	 */
}


TEST_GROUP(HeaterGroup)
{
    void setup()
    {
    }
    
    void teardown()
    {
        HeaterSm_StateSet(HEATER_OFF);
        HeaterSm_Run(0);
    }
};

TEST(HeaterGroup, InitialState)
{
    CHECK_EQUAL(HeaterSm_Run(0), HEATER_OFF);
}
TEST(HeaterGroup, State_OFF_to_On)
{
    HeaterSm_StateSet(HEATER_ON);
    CHECK_EQUAL(HeaterSm_Run(0), HEATER_ON);
}
TEST(HeaterGroup, TimeOutValue)
{
    CHECK_EQUAL(HeaterSm_Init(0), 100);
    CHECK_EQUAL(HeaterSm_Init(500), 500);
    CHECK_EQUAL(HeaterSm_Init(1001), 1000);
}
TEST(HeaterGroup, State_ON_to_OFF)
{
    HeaterSm_StateSet(HEATER_ON);
    CHECK_EQUAL(HeaterSm_Run(10), HEATER_ON);
    HeaterSm_StateSet(HEATER_OFF);
    CHECK_EQUAL(HeaterSm_Run(20), HEATER_OFF);
}
TEST(HeaterGroup, Timeout)
{
    // Turn the heater on for 100 counts
    HeaterSm_Init(100);
    HeaterSm_StateSet(HEATER_ON);
    CHECK_EQUAL(HeaterSm_Run(10), HEATER_ON);
    // Check at the 99 count that the heater is still on
    CHECK_EQUAL(HeaterSm_Run(109), HEATER_ON);
    // Check at the 101 count that the heater is now off
    CHECK_EQUAL(HeaterSm_Run(110), HEATER_OFF);
}
TEST(HeaterGroup, TimeoutReset)
{
    // Turn the heater on for 100 counts
    HeaterSm_Init(100);
    HeaterSm_StateSet(HEATER_ON);
    CHECK_EQUAL(HeaterSm_Run(10), HEATER_ON);
    // Reset the counter by setting the state to HEATER_ON
    HeaterSm_StateSet(HEATER_ON);
    CHECK_EQUAL(HeaterSm_Run(50), HEATER_ON);
    // Check at the 99 count that the heater is still on
    CHECK_EQUAL(HeaterSm_Run(149), HEATER_ON);
    // Check at the 101 count that the heater is now off
    CHECK_EQUAL(HeaterSm_Run(150), HEATER_OFF);
}
