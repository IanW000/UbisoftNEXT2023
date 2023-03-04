#pragma once

struct Timer
{
    Timer();

    float start;
    float cooldown;
    float stayAlive;
    int inventory;

    float timeElapsed(float current);
};
