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
    void points(std::vector<Vector2<T>> points);
    const Vector2<T>& point(unsigned int index) const;
    void point(unsigned int index, Vector2<T> point);
    const Rect<T>& boundingBox() const;
    const Vector2<T> center() const;
    bool contains(Vector2<T> pt) const;

private:
    void computeBoundingBox();

    std::vector<Vector2<T>> _points;
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
void ConvexShape<T>::points(std::vector<Vector2<T>> points)
{
    _points = toConvexHull(std::move(points));
    computeBoundingBox();
}

template <typename T>
const Vector2<T>& ConvexShape<T>::point(unsigned int index) const
{
    assert(index < _points.size());
    return _points[index];
}

template <typename T>
void ConvexShape<T>::point(unsigned int index, Vector2<T> point)
{
    assert(index < _points.size());
    _points[index] = std::move(point);
    computeBoundingBox();
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
    for( const auto& pt : _points) {
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
