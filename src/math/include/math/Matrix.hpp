#pragma once

#include <array>

namespace frontier {

template <typename T, size_t R, size_t C>
class Matrix {
public:
    using UnderlyingType = std::array<std::array<T, C>, R>;

    Matrix();
    Matrix(UnderlyingType matrix);

    /// Contruct an identity matrix
    static Matrix Identity();

    const T& operator()(size_t r, size_t c) const;
    T& operator()(size_t r, size_t c);

    /// Scalar arithmetic
    Matrix operator*(T scalar) const;
    Matrix operator/(T scalar) const;
    Matrix operator+(T scalar) const;
    Matrix operator-(T scalar) const;

    /// Scalar compound assignment arithmetic
    Matrix& operator*=(T scalar);
    Matrix& operator/=(T scalar);
    Matrix& operator+=(T scalar);
    Matrix& operator-=(T scalar);

    /// Matrix arithmetic
    template <size_t RO, size_t CO>
    Matrix<T, R, CO> operator*(const Matrix<T, RO, CO>& rhs) const;
    Matrix operator/(const Matrix& rhs) const;
    Matrix operator+(const Matrix& rhs) const;
    Matrix operator-(const Matrix& rhs) const;

    /// Matrix compound assignment arithmetic
    Matrix& operator*=(const Matrix& rhs);
    Matrix& operator/=(const Matrix& rhs);
    Matrix& operator+=(const Matrix& rhs);
    Matrix& operator-=(const Matrix& rhs);

    /// Compute the determinant of the matrix
    double determinant() const;

    /// Compute the inverse matrix
    Matrix inverse() const;

    /// Compute the transpose matrix
    Matrix<T, C, R> transpose() const;

    size_t rows() const;
    size_t cols() const;

    /// Get the underlying data structure
    UnderlyingType& matrix();
    /// Set the underlying data structure
    void matrix(UnderlyingType matrix);

private:
    UnderlyingType _matrix;
};

} // namespace frontier

#include "impl/Matrix_impl.hpp"
