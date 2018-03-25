#include <graphics/Camera.hpp>

#include <stdexcept>
#include <math/Misc.hpp>

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
    invalidateTransform();
}

void Camera::rotate(float degrees)
{
    rotation(_rotation + degrees);
    invalidateTransform();
}

void Camera::bounds(const Bounds& bounds)
{
    _center.x(bounds.x() + bounds.w() / 2.f);
    _center.y(bounds.y() + bounds.h() / 2.f);
    _dimensions.x(bounds.w());
    _dimensions.y(bounds.h());
    invalidateTransform();
}

void Camera::center(const Vec2f& center)
{
    _center = center;
    invalidateTransform();
}

void Camera::dimensions(const Vec2f& dimensions)
{
    _dimensions = dimensions;
    invalidateTransform();
}

void Camera::rotation(float degrees)
{
    _rotation = static_cast<float>(fmod(degrees, 360));
    if (_rotation < 0) {
        _rotation += 360.f;
    }
    invalidateTransform();
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

float Camera::rotation() const
{
    return _rotation;
}

const Transform& Camera::transform() const
{
    checkAndRecalculateTransform();
    return _transform;
}

const Transform& Camera::inverseTransform() const
{
    checkAndRecalculateInverseTransform();
    return _inverseTransform;
}

void Camera::invalidateTransform()
{
    _staleTransform = true;
    _staleInverseTransform = true;
}

void Camera::checkAndRecalculateTransform() const
{
    if (_staleTransform) {
        _staleTransform = false;

        // Rotation components
        const auto rad = toRadians(_rotation);
        const auto cosine = static_cast<float>(std::cos(rad));
        const auto sine = static_cast<float>(std::sin(rad));
        const auto tx = -_center.x() * cosine - _center.y() * sine + _center.x();
        const auto ty = _center.x() * sine - _center.y() * cosine + _center.y();

        // Projection components
        const auto a = 2.f / _dimensions.x();
        const auto b = -2.f / _dimensions.y();
        const auto c = -a * _center.x();
        const auto d = -b * _center.y();

        // Rebuild the projection matrix
        _transform = Transform{a * cosine, a * sine, a * tx + c, -b * sine, b * cosine, b * ty + d, 0.f, 0.f, 1.f};
    }
}

void Camera::checkAndRecalculateInverseTransform() const
{
    if (_staleInverseTransform) {
        _staleInverseTransform = false;

        checkAndRecalculateTransform();
        _inverseTransform = _transform.inverse();
    }
}

} // namespace frontier
