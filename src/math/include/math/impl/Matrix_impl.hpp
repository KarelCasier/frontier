#pragma once

#include <array>
#include <cassert>
#include <cmath>
#include <iostream>
#include <functional>

namespace {

/// The following matrix decomposition functions are taken from: https://en.wikipedia.org/wiki/LU_decomposition

/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N,
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S
 */
inline int LUPDecompose(double** A, int N, double Tol, int* P)
{
    int i, j, k, imax;
    double maxA, *ptr, absA;

    for (i = 0; i <= N; i++)
        P[i] = i; // Unit permutation matrix, P[N] initialized with N

    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;

        for (k = i; k < N; k++)
            if ((absA = fabs(A[k][i])) > maxA) {
                maxA = absA;
                imax = k;
            }

        if (maxA < Tol)
            return 0; // failure, matrix is degenerate

        if (imax != i) {
            // pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;

            // pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;

            // counting pivots starting from N (for determinant)
            P[N]++;
        }

        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];

            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }

    return 1; // decomposition done
}

/* INPUT: A,P filled in LUPDecompose; b - rhs vector; N - dimension
 * OUTPUT: x - solution vector of A*x=b
 */
inline void LUPSolve(double** A, int* P, double* b, int N, double* x)
{
    for (int i = 0; i < N; i++) {
        x[i] = b[P[i]];

        for (int k = 0; k < i; k++)
            x[i] -= A[i][k] * x[k];
    }

    for (int i = N - 1; i >= 0; i--) {
        for (int k = i + 1; k < N; k++)
            x[i] -= A[i][k] * x[k];

        x[i] = x[i] / A[i][i];
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension
 * OUTPUT: IA is the inverse of the initial matrix
 */
inline void LUPInvert(double** A, int* P, int N, double** IA)
{
    for (int j = 0; j < N; j++) {
        for (int i = 0; i < N; i++) {
            if (P[i] == j)
                IA[i][j] = 1.0;
            else
                IA[i][j] = 0.0;

            for (int k = 0; k < i; k++)
                IA[i][j] -= A[i][k] * IA[k][j];
        }

        for (int i = N - 1; i >= 0; i--) {
            for (int k = i + 1; k < N; k++)
                IA[i][j] -= A[i][k] * IA[k][j];

            IA[i][j] = IA[i][j] / A[i][i];
        }
    }
}

/* INPUT: A,P filled in LUPDecompose; N - dimension.
 * OUTPUT: Function returns the determinant of the initial matrix
 */
inline double LUPDeterminant(double** A, int* P, int N)
{
    double det = A[0][0];

    for (int i = 1; i < N; i++)
        det *= A[i][i];

    if ((P[N] - N) % 2 == 0)
        return det;
    else
        return -det;
}

using namespace frontier;

template <typename T, size_t R, size_t C>
void applyOnEach(Matrix<T, R, C>& mat, std::function<void(T&)> functor)
{
    for (auto& row : mat.matrix()) {
        for (auto& ele : row) {
            functor(ele);
        }
    }
}

template <typename T, size_t R, size_t C>
void applyOnEachPair(Matrix<T, R, C>& matA, Matrix<T, R, C>& matB, std::function<void(T&, T&)> functor)
{
    for (auto i{0u}; i < matA.rows(); ++i) {
        for (auto j{0u}; j < matA.cols(); ++j) {
            functor(matA(i, j), matB(i, j));
        }
    }
}

} // namespace

namespace frontier {

template <typename T, size_t R, size_t C>
Matrix<T, R, C>::Matrix()
{
    applyOnEach<T, R, C>(*this, [](T& ele) { ele = 0.0; });
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>::Matrix(UnderlyingType matrix)
: _matrix{std::move(matrix)}
{
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::Identity()
{
    static_assert(R == C, "Matrix must be square");
    auto mat = Matrix{};
    for (auto i{0u}; i < R; ++i) {
        mat(i, i) = 1.0;
    }
    return mat;
}

template <typename T, size_t R, size_t C>
template <size_t RO, size_t CO>
bool Matrix<T, R, C>::operator==(const Matrix<T, RO, CO>& other) const
{
    return R == RO && C == CO && _matrix == other._matrix;
}

template <typename T, size_t R, size_t C>
const T& Matrix<T, R, C>::operator()(size_t r, size_t c) const
{
    assert(r <= R);
    assert(c <= C);
    return _matrix[r][c];
}

template <typename T, size_t R, size_t C>
T& Matrix<T, R, C>::operator()(size_t r, size_t c)
{
    assert(r <= R);
    assert(c <= C);
    return _matrix[r][c];
}

/// Scalar arithmetic
template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator*(T scalar) const
{
    auto mat = Matrix{*this};
    applyOnEach<T, R, C>(mat, [&scalar](T& ele) { ele *= scalar; });
    return mat;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator/(T scalar) const
{
    assert(scalar != 0);
    auto mat = Matrix{*this};
    applyOnEach<T, R, C>(mat, [&scalar](T& ele) { ele /= scalar; });
    return mat;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(T scalar) const
{
    auto mat = Matrix{*this};
    applyOnEach<T, R, C>(mat, [&scalar](T& ele) { ele += scalar; });
    return mat;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(T scalar) const
{
    auto mat = Matrix{*this};
    applyOnEach<T, R, C>(mat, [&scalar](T& ele) { ele += scalar; });
    return mat;
}

/// Scalar compound assignment arithmetic
template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(T scalar)
{
    auto mat = *this * scalar;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator/=(T scalar)
{
    assert(scalar != 0);
    auto mat = *this / scalar;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator+=(T scalar)
{
    auto mat = *this + scalar;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator-=(T scalar)
{
    auto mat = *this - scalar;
    *this = std::move(mat);
    return *this;
}

/// Matrix arithmetic
template <typename T, size_t R, size_t C>
template <size_t RO, size_t CO>
Matrix<T, R, CO> Matrix<T, R, C>::operator*(const Matrix<T, RO, CO>& rhs) const
{
    static_assert(C == RO, "Matrix inner dimensions do not match");
    const auto& lhs = *this;
    auto res = Matrix<T, R, CO>{};
    for (auto i{0u}; i < R; ++i) {
        for (auto j{0u}; j < CO; ++j) {
            for (auto k{0u}; k < C; ++k) {
                res(i, j) += lhs(i, k) * rhs(k, j);
            }
        }
    }
    return res;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator/(const Matrix& rhs) const
{
    return *this * rhs.inverse();
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator+(const Matrix& rhs) const
{
    auto lhs = Matrix{*this};
    applyOnEachPair<T, R, C>(lhs, rhs, [](T& eleL, T& eleR) { eleL += eleR; });
    return lhs;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::operator-(const Matrix& rhs) const
{
    auto lhs = Matrix{*this};
    applyOnEachPair<T, R, C>(lhs, rhs, [](T& eleL, T& eleR) { eleL -= eleR; });
    return lhs;
}

/// Matrix compound assignment arithmetic
template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator*=(const Matrix& rhs)
{
    auto mat = *this * rhs;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator/=(const Matrix& rhs)
{
    auto mat = *this / rhs;

    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator+=(const Matrix& rhs)
{
    auto mat = *this + rhs;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
Matrix<T, R, C>& Matrix<T, R, C>::operator-=(const Matrix& rhs)
{
    auto mat = *this - rhs;
    *this = std::move(mat);
    return *this;
}

template <typename T, size_t R, size_t C>
size_t Matrix<T, R, C>::rows() const
{
    return R;
}

template <typename T, size_t R, size_t C>
size_t Matrix<T, R, C>::cols() const
{
    return C;
}

template <typename T, size_t R, size_t C>
typename Matrix<T, R, C>::UnderlyingType& Matrix<T, R, C>::matrix()
{
    return _matrix;
}

template <typename T, size_t R, size_t C>
void Matrix<T, R, C>::matrix(UnderlyingType matrix)
{
    _matrix = std::move(matrix);
}

/// TODO: replace with more efficient vesrion
template <typename T, size_t R, size_t C>
double Matrix<T, R, C>::determinant() const
{
    static_assert(R == C, "Matrix must be square");
    auto dim = R;

    // Copy data to raw 2d array converting to double
    double** A = new double*[dim];
    for (auto r{0u}; r < dim; ++r) {
        A[r] = new double[dim];
        for (auto c{0u}; c < dim; ++c) {
            A[r][c] = (*this)(r, c);
        }
    }
    auto P = new int[dim + 1];

    const auto res = LUPDecompose(A, dim, 0.0001, P);
    if (!res) {
        std::cerr << "Unable to decompose matrix" << std::endl;
        return 0;
    }
    const auto det = LUPDeterminant(A, P, dim);

    for (auto r{0u}; r < dim; ++r) {
        delete[] A[r];
    }
    delete[] A;
    delete[] P;

    return det;
}

/// TODO: replace with more efficient vesrion
template <typename T, size_t R, size_t C>
Matrix<T, R, C> Matrix<T, R, C>::inverse() const
{
    // return adj() / determinant();
    static_assert(R == C, "Matrix must be square");
    auto mat = Matrix<T, R, C>{};
    auto dim = R;

    // Copy data to raw 2d array converting to double
    double** A = new double*[dim];
    double** inv = new double*[dim];
    for (auto r{0u}; r < dim; ++r) {
        A[r] = new double[dim];
        inv[r] = new double[dim];
        for (auto c{0u}; c < dim; ++c) {
            A[r][c] = (*this)(r, c);
        }
    }
    auto P = new int[dim + 1];
    const auto res = LUPDecompose(A, dim, 0.0001, P);
    if (!res) {
        std::cerr << "Unable to decompose matrix" << std::endl;
        return {};
    }
    LUPInvert(A, P, dim, inv);
    for (auto r{0u}; r < dim; ++r) {
        for (auto c{0u}; c < dim; ++c) {
            mat(r, c) = inv[r][c];
        }
    }

    for (auto r{0u}; r < dim; ++r) {
        delete[] A[r];
        delete[] inv[r];
    }
    delete[] A;
    delete[] inv;
    delete[] P;

    return mat;
}

template <typename T, size_t R, size_t C>
Matrix<T, C, R> Matrix<T, R, C>::transpose() const
{
    auto transposedMatrix = Matrix<T, C, R>{};
    for (auto r{0u}; r < rows(); ++r) {
        for (auto c{0u}; c < cols(); ++c) {
            transposedMatrix(c, r) = (*this)(r, c);
        }
    }
    return transposedMatrix;
}

} // namespace frontier
