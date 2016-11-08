#include "UudistusMath.h"

using namespace ud;

inline
Vec2::Vec2()
    :Vec2(0, 0)
{
}

inline
Vec2::Vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

inline
Vec2::~Vec2() {}

inline
float Vec2::length()
{
    return (float)sqrt(x*x + y*y);
}

inline
void Vec2::normalize()
{
    float d = length();
    x /= d;
    y /= d;
}

inline
Vec2 Vec2::operator-(Vec2 other)
{
    return Vec2(x - other.x, y - other.y);
}