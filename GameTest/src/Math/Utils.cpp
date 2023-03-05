#include "stdafx.h"
#include "Utils.h"
#include <random>

bool Utils::RandomBool(int min, int max, int percentage)
{
    int p = percentage;
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return (distribution(generator) < p);
}

//return a random integer
int Utils::RandomInt(int min, int max)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_int_distribution<int> distribution(min, max);
    return distribution(generator);
}

//return a random float
float Utils::RandomFloat(float min, float max)
{
    static std::mt19937 generator(std::random_device{}());
    std::uniform_real_distribution<float> distribution(min, max);
    return distribution(generator);
}

float Utils::Distance(float x1 , float y1, float x2, float y2)
{
    return sqrtf(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

MouseInput Utils::getMousePosition()
{
    MouseInput newMousePos;
    POINT mousePos;
    GetCursorPos(&mousePos);	// Get the mouse cursor 2D x,y position			
    ScreenToClient(MAIN_WINDOW_HANDLE, &mousePos);
    newMousePos.x = (float)mousePos.x;
    newMousePos.y = (float)mousePos.y;
    newMousePos.x = ((float)mousePos.x * (2.0f / WINDOW_WIDTH) - 1.0f);
    newMousePos.y = ((float)mousePos.y * (2.0f / WINDOW_HEIGHT) - 1.0f);;
    return newMousePos;
};