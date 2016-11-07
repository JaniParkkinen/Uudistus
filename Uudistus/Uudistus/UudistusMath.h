#pragma once

//#include <SFML\Main.hpp>
#include <math.h>

namespace ud
{
    class Vec2
    {
    public:
        Vec2();
        Vec2(float x, float y);
        ~Vec2();

        float length()
        {
            return sqrt(x*x + y*y);
        }
        void normalize()
        {
            float d = length();
            x /= d;
            y /= d;
        }

        Vec2 operator-(Vec2 other)
        {
            return Vec2(x - other.x, y - other.y);
        }

        float x, y;
    };

    Vec2::Vec2()
        :Vec2(0, 0)
    {
    }
    Vec2::Vec2(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
    Vec2::~Vec2(){}
}