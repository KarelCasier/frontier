#include <math/Collision.hpp>

namespace frontier {

template <typename T>
bool intersects(const Vector2<T>& point, const Rect<T>& rect)
{
    return (point.x() > rect.x() && point.x() < rect.x() + rect.w()) ||
           (point.y() > rect.y() && point.y() < rect.y() + rect.h());
}

template <typename T>
bool intersects(const Rect<T>& rect1, const Rect<T>& rect2)
{
    auto left1 = rect1.x();
    auto right1 = rect1.x() + rect1.w();
    auto top1 = rect1.y();
    auto bottom1 = rect1.y() + rect1.h();

    auto left2 = rect2.x();
    auto right2 = rect2.x() + rect2.w();
    auto top2 = rect2.y();
    auto bottom2 = rect2.y() + rect2.h();

    if (bottom1 <= top2 || top1 >= bottom2 || right1 <= left2 || left1 >= right2) {
        return false;
    }

    return true;
}

/// Explicit template instantiation
template bool intersects(const Vector2<float>&, const Rect<float>&);
template bool intersects(const Vector2<double>&, const Rect<double>&);
template bool intersects(const Vector2<int>&, const Rect<int>&);

template bool intersects(const Rect<float>&, const Rect<float>&);
template bool intersects(const Rect<double>&, const Rect<double>&);
template bool intersects(const Rect<int>&, const Rect<int>&);

} // namespace frontier
