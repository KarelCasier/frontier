#pragma once

#include <math/Matrix.hpp>

namespace frontier {

template <typename T, size_t R, size_t C>
void print(const Matrix<T, R, C>& mat)
{
    for (auto i{0u}; i < R; ++i) {
        for (auto j{0u}; j < C; ++j) {
            std::cout << mat(i, j) << " ";
        }
        std::cout << std::endl;
    }
}

} // namespace frontier
