#include "stdafx.h"
#include "Timer.h"


Timer::Timer() : start(0.0f), cooldown(3.0f), stayAlive(0.0f), inventory(1)
{
}

float Timer::timeElapsed(float current)
{
    return current - start;
}