#pragma once

#include <math/Rect.hpp>
#include <graphics/Transform.hpp>

namespace frontier {

class Window;

/// A camera class that can be the render target
class Camera {
public:
    using Vec2f = Vector2<float>;
    using Vec2i = Vector2<int>;
    using Bounds = Rect<float>;

    /// Create a camera
    /// @param bounds the bounds of the camera
    Camera(const Bounds& bounds);

    /// Create a camera
    /// @param center the center of the camera
    /// @param dimensions the dimensions of the camera
    Camera(const Vec2f& center, const Vec2f& dimensions);

    /// Move the camera
    void move(const Vec2f& displacement);
    /// Rotate the camera
    void rotate(float degrees);

    /// Set the bounds of the camera
    void bounds(const Bounds& bounds);
    /// Set the center of the camera
    void center(const Vec2f& center);
    /// Set the dimensions of the camera
    void dimensions(const Vec2f& dimensions);
    /// Set the rotation of the camera
    void rotation(float degrees);

    /// Get the bounds of the camera
    Bounds bounds() const;
    /// Get the position of the camera
    const Vec2f& center() const;
    /// Get the dimensions of the camera
    const Vec2f& dimensions() const;
    /// Get the rotation of the camera in degrees
    float rotation() const;

    /// Get the current transform
    const Transform& transform() const;
    /// Get the current inverse transform
    const Transform& inverseTransform() const;

private:
    void checkAndRecalculateTransform() const;
    void checkAndRecalculateInverseTransform() const;
    void invalidateTransform();

    Vec2f _center;
    Vec2f _dimensions;
    float _rotation{0.f};
    mutable bool _staleTransform{true};
    mutable bool _staleInverseTransform{true};
    mutable Transform _transform;
    mutable Transform _inverseTransform;
};

} // namespace frontier
