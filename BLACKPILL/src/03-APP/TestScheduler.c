
#ifdef APP1
#include "../../include/02-HAL/LED/LED.h"
#include "../../include/4-Service/SCHED.h"
#include "../../include/03-APP/TestScheduler.h"

void Runnable1f(void)
{
    LED_SetStatus(TestLed,LED_ON);
}

void Runnable2f(void)
{
    LED_SetStatus(TestLed,LED_OFF);
}

RunnableTask_t R1=
{
    .PeriodicityMS=2000,
    .InitialDelayMS=0,
    .CallBack=Runnable1f,
    .TaskName="LED on",
    .Priority=0
};
RunnableTask_t R2=
{
    .PeriodicityMS=2000,
    .InitialDelayMS=1000,
    .CallBack=Runnable2f,
    .TaskName="LED off",
    .Priority=1
};
void TestSched_Init(){
LED_INIT();
SCHED_RegisterTask(&R1);
SCHED_RegisterTask(&R2);
}
#endif