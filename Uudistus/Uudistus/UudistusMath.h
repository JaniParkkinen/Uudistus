#ifndef UUDISTUS_MATH_H
#define UUDISTUS_MATH_H

#include <math.h>

namespace ud
{
    class Vec2
    {
    public:
        Vec2();
        Vec2(float x, float y);
        ~Vec2();

        float length();
        void normalize();
        Vec2 operator-(Vec2 other);

        float x, y;
    };
}

#endif