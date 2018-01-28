#pragma once

namespace frontier {

class Vector2f {
public:
    float x;
    float y;

    Vector2f operator*(float scalar) { return {x * scalar, y * scalar}; }

    Vector2f& operator*=(float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    Vector2f operator+(float scalar) { return {x + scalar, y + scalar}; }

    Vector2f& operator+=(float scalar)
    {
        x += scalar;
        y += scalar;
        return *this;
    }

    Vector2f operator*(const Vector2f& rhs) { return {x * rhs.x, y * rhs.y}; }

    Vector2f& operator*=(const Vector2f& rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vector2f operator+(const Vector2f& rhs) { return {x + rhs.x, y + rhs.y}; }

    Vector2f& operator+=(const Vector2f& rhs)
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }
};

} // namespace frontier
