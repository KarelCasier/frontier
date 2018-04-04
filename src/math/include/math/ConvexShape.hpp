#pragma once

#include <vector>

#include "ConvexHelpers.hpp"
#include "Rect.hpp"
#include "Vector2.hpp"

namespace frontier {

template <typename T>
class ConvexShape {
public:
    ConvexShape(std::vector<Vector2<T>> points)
    : _points{}
    , _boundingBox{0, 0, 0, 0}
    {
        this->points(std::move(points));
    }

    const std::vector<Vector2<T>>& points() const { return _points; }
    void points(std::vector<Vector2<T>> points)
    {
        _points = toConvexHull(std::move(points));
        computeBoundingBox();
    }

    const Vector2<T>& point(unsigned int index) const
    {
        assert(index < _points.size());
        return _points[index];
    }
    void point(unsigned int index, Vector2<T> point)
    {
        assert(index < _points.size());
        _points[index] = std::move(point);
        computeBoundingBox();
    }

    const Rect<T>& boundingBox() const { return _boundingBox; }

private:
    void computeBoundingBox()
    {
        const auto [xMin, xMax] = std::minmax_element(begin(_points), end(_points),
                                                      [](const auto& a, const auto& b) { return a.x() < b.x(); });
        const auto [yMin, yMax] = std::minmax_element(begin(_points), end(_points),
                                                      [](const auto& a, const auto& b) { return a.y() < b.y(); });
        _boundingBox.position({xMin->x(), yMin->y()});
        _boundingBox.dimensions({xMax->x() - xMin->x(), yMax->y() - yMin->y()});
    }

    std::vector<Vector2<T>> _points;
    Rect<T> _boundingBox;
};

} // namespace frontier
