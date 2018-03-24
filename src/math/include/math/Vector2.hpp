#pragma once

#include <cassert>
#include <cmath>
#include <type_traits>

namespace frontier {

/// Vector2 class handles basic 2d vector math.
///
/// Templated to allow use with any numeric class as the base.
template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
class Vector2 {
public:
    Vector2()
    : _x{0}
    , _y{0}
    {
    }
    Vector2(T x, T y)
    : _x{std::move(x)}
    , _y{std::move(y)}
    {
    }
    Vector2(Vector2&& other) = default;
    Vector2(const Vector2& other) = default;
    Vector2<T>& operator=(Vector2&& other) = default;
    Vector2<T>& operator=(const Vector2& other) = default;

    // Allow explicit conversion
    template <typename O>
    explicit operator Vector2<O>()
    {
        return {static_cast<O>(_x), static_cast<O>(_y)};
    }

    bool operator==(const Vector2& other) const
    {
        const auto xEqual{std::abs(_x - other._x) <= epsilon};
        const auto yEqual{std::abs(_y - other._y) <= epsilon};
        return xEqual && yEqual;
    }

    /// Getters
    T x() const { return _x; };
    T y() const { return _y; };

    /// Setters
    void x(T x) { _x = std::move(x); };
    void y(T y) { _y = std::move(y); };

    /// Scalar arithmetic
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator*(S scalar)
    {
        return {static_cast<T>(_x * scalar), static_cast<T>(_y * scalar)};
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator/(S scalar)
    {
        assert(scalar != 0);
        return {static_cast<T>(_x / scalar), static_cast<T>(_y / scalar)};
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator+(S scalar)
    {
        return {static_cast<T>(_x + scalar), static_cast<T>(_y + scalar)};
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator-(S scalar)
    {
        return {static_cast<T>(_x - scalar), static_cast<T>(_y - scalar)};
    }

    /// Scalar compound assignment arithmetic
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator*=(S scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator/=(S scalar)
    {
        assert(scalar != 0);
        _x /= scalar;
        _y /= scalar;
        return *this;
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator+=(S scalar)
    {
        _x += scalar;
        _y += scalar;
        return *this;
    }
    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator-=(S scalar)
    {
        _x -= scalar;
        _y -= scalar;
        return *this;
    }

    /// Vector2 arithmetic
    Vector2 operator*(const Vector2& rhs) { return {_x * rhs._x, _y * rhs._y}; }
    Vector2 operator/(const Vector2& rhs)
    {
        assert(rhs._x != 0);
        assert(rhs._y != 0);
        return {_x / rhs._x, _y / rhs._y};
    }
    Vector2 operator+(const Vector2& rhs) { return {_x + rhs._x, _y + rhs._y}; }
    Vector2 operator-(const Vector2& rhs) { return {_x - rhs._x, _y - rhs._y}; }

    /// Vector2 compound assignment arithmetic
    Vector2& operator*=(const Vector2& rhs)
    {
        _x *= rhs._x;
        _y *= rhs._y;
        return *this;
    }
    Vector2& operator/=(const Vector2& rhs)
    {
        assert(rhs._x != 0);
        assert(rhs._y != 0);
        _x /= rhs._x;
        _y /= rhs._y;
        return *this;
    }
    Vector2& operator+=(const Vector2& rhs)
    {
        _x += rhs._x;
        _y += rhs._y;
        return *this;
    }
    Vector2& operator-=(const Vector2& rhs)
    {
        _x -= rhs._x;
        _y -= rhs._y;
        return *this;
    }

    /// Vector2 math
    double length() { return std::sqrt((_x * _x) + (_y * _y)); }
    double lengthSquared() { return (_x * _x) + (_y * _y); }
    Vector2& normalize()
    {
        const auto l = length();
        if (l != 0) {
            (*this) *= 1 / l;
        }
        return *this;
    }

private:
    static long double constexpr epsilon = 0.000001;
    T _x;
    T _y;
};

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;
using Vector2u = Vector2<unsigned int>;

} // namespace frontier
