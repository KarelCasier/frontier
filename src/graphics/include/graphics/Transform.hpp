#pragma once

#include <math/Matrix.hpp>
#include <math/Vector2.hpp>

namespace frontier {

class Transform {
public:
    Transform();
    Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);

    /// Apply a scaling factor
    Transform& scale(float factor);
    /// Apply a scaling factor at a point
    Transform& scale(float factor, const Vector2f& center);
    /// Apply a translation
    Transform& translate(const Vector2f& displacement);
    /// Apply a rotation
    Transform& rotate(float degrees);
    /// Apply a rotation around a point
    Transform& rotate(float degrees, const Vector2f& center);

    /// Combine with another transform
    Transform& combine(const Transform& transform);

    /// Transform a point
    Vector2f transformPoint(const Vector2f& point);

private:
    Transform& row1(float a00, float a01, float a02);
    Transform& row2(float a10, float a11, float a12);
    Transform& row3(float a20, float a21, float a22);

    Transform& col1(float a00, float a10, float a20);
    Transform& col2(float a01, float a11, float a21);
    Transform& col3(float a02, float a12, float a22);

    Matrix<float, 3, 3> _matrix;
};

} // namespace frontier
