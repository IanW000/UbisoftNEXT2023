#include "stdafx.h"
#include "Utils.h"
#include <random>


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
