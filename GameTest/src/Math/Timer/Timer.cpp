#include "stdafx.h"
#include "Timer.h"


Timer::Timer() : start(0.0f), cooldown(0.5f), stayAlive(0.0f), inventory(1)
{
}

float Timer::timeElapsed(float current)
{
    return current - start;
}