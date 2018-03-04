#include <graphics/Camera.hpp>

#include <stdexcept>

namespace frontier {

Camera::Camera(const Bounds& bounds)
{
    Camera::bounds(bounds);
}

Camera::Camera(const Vec2f& center, const Vec2f& dimensions)
: _center{center}
, _dimensions{dimensions}
{
}

void Camera::move(const Vec2f& displacement)
{
    _center += displacement;
}

void Camera::bounds(const Bounds& bounds)
{
    _center.x(bounds.x() + bounds.w() / 2);
    _center.y(bounds.y() + bounds.h() / 2);
    _dimensions.x(bounds.w());
    _dimensions.y(bounds.h());
}

void Camera::center(const Vec2f& center)
{
    _center = center;
}

void Camera::dimensions(const Vec2f& dimensions)
{
    _dimensions = dimensions;
}

Camera::Bounds Camera::bounds() const
{
    return {_center.x() - _dimensions.x() / 2.f, _center.y() - _dimensions.y() / 2.f, _dimensions.x(), _dimensions.y()};
}

const Camera::Vec2f& Camera::center() const
{
    return _center;
}

const Camera::Vec2f& Camera::dimensions() const
{
    return _dimensions;
}

Camera::Vec2f Camera::screenToCamera(const Vec2f& /*screenPoint*/)
{
    throw std::logic_error{"Unimplemented"};
}

Camera::Vec2f Camera::cameraToScreen(const Vec2f& /*cameraPoint*/)
{
    throw std::logic_error{"Unimplemented"};
}

} // namespace frontier
