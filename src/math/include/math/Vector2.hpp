#pragma once

#include <type_traits>

namespace frontier {

/// Vector2 class handles basic 2d vector math.
///
/// Templated to allow use with any numeric class as the base.
template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
class Vector2 {
public:
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

    /// Getters
    T x() const { return _x; };
    T y() const { return _y; };

    /// Setters
    T x(T x) { _x = std::move(x); };
    T y(T y) { _y = std::move(y); };

    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator*(S scalar)
    {
        return {static_cast<T>(_x * scalar), static_cast<T>(_y * scalar)};
    }

    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator*=(S scalar)
    {
        _x *= scalar;
        _y *= scalar;
        return *this;
    }

    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2 operator+(S scalar)
    {
        return {static_cast<T>(_x + scalar), static_cast<T>(_y + scalar)};
    }

    template <typename S, typename = typename std::enable_if_t<std::is_arithmetic<S>::value>>
    Vector2& operator+=(S scalar)
    {
        _x += scalar;
        _y += scalar;
        return *this;
    }

    Vector2 operator*(const Vector2& rhs) { return {_x * rhs._x, _y * rhs._y}; }

    Vector2& operator*=(const Vector2& rhs)
    {
        _x *= rhs._x;
        _y *= rhs._y;
        return *this;
    }

    Vector2 operator+(const Vector2& rhs) { return {_x + rhs._x, _y + rhs._y}; }

    Vector2& operator+=(const Vector2& rhs)
    {
        _x += rhs._x;
        _y += rhs._y;
        return *this;
    }

    bool operator==(const Vector2& other) { return _x == other._x && _y == other._y; }

private:
    T _x;
    T _y;
};

using Vector2f = Vector2<float>;

} // namespace frontier
