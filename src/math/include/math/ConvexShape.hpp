#pragma once

#include <numeric>
#include <vector>

#include "ConvexHelpers.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"
#include "Printers.hpp"

#include <log/log.hpp>

namespace frontier {

template <typename T>
class ConvexShape {
public:
    ConvexShape(std::vector<Vector2<T>> points);

    const std::vector<Vector2<T>>& points() const;
    const Vector2<T>& point(unsigned int index) const;
    void points(std::vector<Vector2<T>> points);
    void point(unsigned int index, Vector2<T> point);
    const std::vector<Vector2<T>>& normals() const;
    const Vector2<T>& normal(unsigned int index) const;
    const Rect<T>& boundingBox() const;
    const Vector2<T> center() const;
    bool contains(Vector2<T> pt) const;

private:
    void computeBoundingBox();
    void computeNormals();

    std::vector<Vector2<T>> _points;
    std::vector<Vector2<T>> _normals;
    Rect<T> _boundingBox;
};

template <typename T>
ConvexShape<T>::ConvexShape(std::vector<Vector2<T>> points)
: _points{}
, _boundingBox{0, 0, 0, 0}
{
    this->points(std::move(points));
}

template <typename T>
const std::vector<Vector2<T>>& ConvexShape<T>::points() const
{
    return _points;
}

template <typename T>
const Vector2<T>& ConvexShape<T>::point(unsigned int index) const
{
    assert(index < _points.size());
    return _points[index];
}

template <typename T>
void ConvexShape<T>::points(std::vector<Vector2<T>> points)
{
    _points = toConvexHull(std::move(points));
    computeBoundingBox();
    computeNormals();
}

template <typename T>
const std::vector<Vector2<T>>& ConvexShape<T>::normals() const
{
    return _normals;
}

template <typename T>
const Vector2<T>& ConvexShape<T>::normal(unsigned int index) const
{
    assert(index < _normals.size());
    return _normals[index];
}

template <typename T>
void ConvexShape<T>::point(unsigned int index, Vector2<T> point)
{
    assert(index < _points.size());
    _points[index] = std::move(point);
    computeBoundingBox();
    computeNormals();
}

template <typename T>
const Rect<T>& ConvexShape<T>::boundingBox() const
{
    return _boundingBox;
}

template <typename T>
const Vector2<T> ConvexShape<T>::center() const
{
    auto total = Vector2f{};
    for (const auto& pt : _points) {
        total += pt;
    }
    return total / static_cast<T>(_points.size());
}

template <typename T>
void ConvexShape<T>::computeBoundingBox()
{
    const auto [xMin, xMax] =
        std::minmax_element(begin(_points), end(_points), [](const auto& a, const auto& b) { return a.x() < b.x(); });
    const auto [yMin, yMax] =
        std::minmax_element(begin(_points), end(_points), [](const auto& a, const auto& b) { return a.y() < b.y(); });
    _boundingBox.position({xMin->x(), yMin->y()});
    _boundingBox.dimensions({xMax->x() - xMin->x(), yMax->y() - yMin->y()});
}

template <typename T>
void ConvexShape<T>::computeNormals()
{
    // First and last point are the same - one less normal
    _normals.resize(_points.size() - 1);
    for (auto i{0u}; i < _normals.size(); ++i) {
        const auto face = point(i+1) - point(i);
        _normals[i] = face.normal();
    }
}

/// Algorythm by: http://www.ecse.rpi.edu/Homepages/wrf/Research/Short_Notes/pnpoly.html
template <typename T>
bool ConvexShape<T>::contains(Vector2<T> pt) const
{
    int nvert = points().size();
    auto isContatined = false;
    for (auto i = 0, j = nvert - 1; i < nvert; j = i++) {
        if (((point(i).y() > pt.y()) != (point(j).y() > pt.y())) &&
            (pt.x() <
             (point(j).x() - point(i).x()) * (pt.y() - point(i).y()) / (point(j).y() - point(i).y()) + point(i).x())) {
            isContatined = !isContatined;
        }
    }
    return isContatined;
}

} // namespace frontier
