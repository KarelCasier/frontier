#pragma once

#include <iostream>
#include <math/Matrix.hpp>
#include <math/Vector2.hpp>
#include <math/Rect.hpp>

namespace frontier {

template <typename T, size_t R, size_t C>
std::ostream& operator<<(std::ostream& os, const Matrix<T, R, C>& mat)
{
    for (auto i{0u}; i < R; ++i) {
        for (auto j{0u}; j < C; ++j) {
            os << mat(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vec)
{
    os << "[" << vec.x() << ", " << vec.y() << "]";
    return os;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect)
{
    os << "[" << rect.position() << ", " << rect.dimensions() << "]";
    return os;
}

} // namespace frontier
