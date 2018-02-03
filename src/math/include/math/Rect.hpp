#pragma once

#include "Vector2.hpp"

namespace frontier {

template <typename T>
class Rect {
public:
    Rect(T x, T y, T w, T h)
    : _position{std::move(x), std::move(y)}
    , _dimensions{std::move(w), std::move(h)}
    {
    }

    /// Getters
    T x() const { return _position.x(); }
    T y() const { return _position.y(); }
    T w() const { return _dimensions.x(); }
    T h() const { return _dimensions.y(); }
    Vector2<T> position() const { _position; }
    Vector2<T> dimensions() const { _dimensions; }

    /// Setters
    void x(T x) { _position.x(std::move(x)); }
    void y(T y) { _position.y(std::move(y)); }
    void w(T w) { _dimensions.x(std::move(w)); }
    void h(T h) { _dimensions.y(std::move(h)); }
    void position(Vector2<T> position) const { _position = std::move(position); }
    void dimensions(Vector2<T> dimensions) const { _dimensions = std::move(dimensions); }

private:
    Vector2<T> _position;
    Vector2<T> _dimensions;
};

using Rectf = Rect<float>;

} // namespace frontier
