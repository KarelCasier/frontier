#pragma once

#include <math/Rect.hpp>

namespace frontier {

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
    /// @param displacement The distance to move the camera by
    void move(const Vec2f& displacement);

    /// Set the bounds of the camera
    void bounds(const Bounds& bounds);
    /// Set the center of the camera
    void center(const Vec2f& center);
    /// Set the dimensions of the camera
    void dimensions(const Vec2f& dimensions);

    /// Get the bounds of the camera
    Bounds bounds() const;
    /// Get the position of the camera
    const Vec2f& center() const;
    /// Get the dimensions of the camera
    const Vec2f& dimensions() const;

    /// Map a screen point to a camera point
    /// @param screenPoint The point on the screen to convert
    /// @returns The transformed point
    Vec2f screenToCamera(const Vec2f& screenPoint);

    /// Map a camera point to a screen point
    /// @param cameraPoint The point on the screen to convert
    /// @returns The transformed point
    Vec2f cameraToScreen(const Vec2f& cameraPoint);

private:
    Vec2f _center;
    Vec2f _dimensions;
};

} // namespace frontier
