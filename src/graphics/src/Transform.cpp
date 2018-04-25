#include <graphics/Transform.hpp>

#include <math/Misc.hpp>

namespace frontier {

Transform::Transform()
{
    row1(1, 0, 0);
    row2(0, 1, 0);
    row3(0, 0, 1);
}

Transform::Transform(Matrix<float, 3, 3> matrix)
: _matrix{matrix}
{
}

Transform::Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22)
{
    row1(a00, a01, a02);
    row2(a10, a11, a12);
    row3(a20, a21, a22);
}

Transform& Transform::scale(float factor)
{
    auto transform = Transform{};
    transform.row1(factor, 0, 0);
    transform.row2(0, factor, 0);
    return combine(transform);
}

Transform& Transform::scale(float factor, const Vector2f& center)
{
    auto transform = Transform{};
    transform.row1(factor, 0, center.x() * (1 - factor));
    transform.row2(0, factor, center.y() * (1 - factor));
    return combine(transform);
}

Transform& Transform::translate(const Vector2f& displacement)
{
    auto transform = Transform{};
    transform.col3(displacement.x(), displacement.y(), 1);
    return combine(transform);
}

Transform& Transform::rotate(float degrees)
{
    const auto rad = toRadians(degrees);
    const auto cos = std::cos(rad);
    const auto sin = std::sin(rad);
    auto transform = Transform{};
    transform.row1(cos, -sin, 0);
    transform.row2(sin, cos, 0);
    return combine(transform);
}

Transform& Transform::rotate(float degrees, const Vector2f& center)
{
    const auto rad = toRadians(degrees);
    const auto cos = std::cos(rad);
    const auto sin = std::sin(rad);
    auto transform = Transform{};
    transform.row1(cos, -sin, center.x() * (1 - cos) + center.y() * sin);
    transform.row2(sin, cos, center.y() * (1 - cos) - center.x() * sin);
    return combine(transform);
}

Transform& Transform::combine(const Transform& transform)
{
    _matrix *= transform._matrix;
    return *this;
}

Vector2f Transform::transformPoint(const Vector2f& point) const
{
    const auto matPoint = Matrix<float, 3, 1>{{{{{point.x()}}, {{point.y()}}, {{1}}}}};
    const auto transMatPoint = _matrix * matPoint;
    return {transMatPoint(0, 0), transMatPoint(0, 1)};
}

Transform Transform::inverse() const
{
    return {_matrix.inverse()};
}

Transform& Transform::row1(float a00, float a01, float a02)
{
    _matrix(0, 0) = a00;
    _matrix(0, 1) = a01;
    _matrix(0, 2) = a02;
    return *this;
}
Transform& Transform::row2(float a10, float a11, float a12)
{
    _matrix(1, 0) = a10;
    _matrix(1, 1) = a11;
    _matrix(1, 2) = a12;
    return *this;
}
Transform& Transform::row3(float a20, float a21, float a22)
{
    _matrix(2, 0) = a20;
    _matrix(2, 1) = a21;
    _matrix(2, 2) = a22;
    return *this;
}

Transform& Transform::col1(float a00, float a10, float a20)
{
    _matrix(0, 0) = a00;
    _matrix(1, 0) = a10;
    _matrix(2, 0) = a20;
    return *this;
}
Transform& Transform::col2(float a01, float a11, float a21)
{
    _matrix(0, 1) = a01;
    _matrix(1, 1) = a11;
    _matrix(2, 1) = a21;
    return *this;
}
Transform& Transform::col3(float a02, float a12, float a22)
{
    _matrix(0, 2) = a02;
    _matrix(1, 2) = a12;
    _matrix(2, 2) = a22;
    return *this;
}

} // namespace frontier
