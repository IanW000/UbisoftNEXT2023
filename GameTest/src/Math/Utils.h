#pragma once
#include <App/main.h>
#include <Math/Utils.h>

struct MouseInput {
    float x, y;
};

class Utils
{
public:

    static bool Utils::RandomBool(int min, int max, int percentage);

    static int RandomInt(int min, int max);

    static float RandomFloat(float min, float max);

    static float Utils::Distance(float x1, float y1, float x2, float y2);

    static MouseInput getMousePosition();

};

