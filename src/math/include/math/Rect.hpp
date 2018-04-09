#pragma once

#include <array>

#include "Vector2.hpp"

namespace frontier {

template <typename T, typename = typename std::enable_if_t<std::is_arithmetic<T>::value>>
class Rect {
public:
    Rect(T x, T y, T w, T h)
    : _position{std::move(x), std::move(y)}
    , _dimensions{std::move(w), std::move(h)}
    {
    }
    Rect(Vector2<T> position, Vector2<T> dimensions)
    : _position{std::move(position)}
    , _dimensions{std::move(dimensions)}
    {
    }

    // Allow explicit conversion
    template <typename O>
    explicit operator Rect<O>() const
    {
        return {static_cast<O>(_position.x()), static_cast<O>(_position.y()), static_cast<O>(_dimensions.x()),
                static_cast<O>(_dimensions.y())};
    }

    /// Getters
    T x() const { return _position.x(); }
    T y() const { return _position.y(); }
    T w() const { return _dimensions.x(); }
    T h() const { return _dimensions.y(); }
    Vector2<T> position() const { return _position; }
    Vector2<T> dimensions() const { return _dimensions; }
    std::array<Vector2<T>, 4> points() const
    {
        return {{{x(), y()}, {x() + w(), y()}, {x() + w(), y() + h()}, {x(), y() + h()}}};
    }

    /// Setters
    void x(T x) { _position.x(std::move(x)); }
    void y(T y) { _position.y(std::move(y)); }
    void w(T w) { _dimensions.x(std::move(w)); }
    void h(T h) { _dimensions.y(std::move(h)); }
    void position(Vector2<T> position) { _position = std::move(position); }
    void dimensions(Vector2<T> dimensions) { _dimensions = std::move(dimensions); }

    /// Determine if a point lies within.
    bool contains(const Vector2f& point) const
    {
        return (point.x() > x() && point.x() < x() + w()) && (point.y() > y() && point.y() < y() + h());
    }

private:
    Vector2<T> _position;
    Vector2<T> _dimensions;
};

using Rectf = Rect<float>;
using Recti = Rect<int>;

} // namespace frontier
