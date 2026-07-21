#pragma once

#include "Vec2.h"
#include "VekTu/Common.h"

#include <array>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <cstdint>

namespace vk {

template <VectorElement T> struct Mat2
{
    // Column-major storage:
    // data[column][row]
    std::array<std::array<T, 2>, 2> data;

    Mat2() : data{{0, 0}, {0, 0}} { }

    Mat2(T m00, T m01, T m10, T m11) : data{{m00, m10}, {m01, m11}} { }

    // a and b are columns
    Mat2(Vec2<T> a, Vec2<T> b) : data{{a.x, a.y}, {b.x, b.y}} { }


    [[nodiscard]] static Mat2 identity() { return {1, 0, 0, 1}; }


    T& operator()(size_t row, size_t col)
    {
        assert(row < 2 && col < 2);
        return data[col][row];
    }

    const T& operator()(size_t row, size_t col) const
    {
        assert(row < 2 && col < 2);
        return data[col][row];
    }


    [[nodiscard]] T det() const { return (*this)(0, 0) * (*this)(1, 1) - (*this)(0, 1) * (*this)(1, 0); }


    Mat2 transpose() const { return {(*this)(0, 0), (*this)(0, 1), (*this)(1, 0), (*this)(1, 1)}; }

    Mat2& transposeInPlace()
    {
        *this = transpose();
        return *this;
    }


    Mat2 inverse() const
    {
        assert(det() != 0);

        return (T(1) / det()) * Mat2{(*this)(1, 1), -(*this)(0, 1), -(*this)(1, 0), (*this)(0, 0)};
    }

    Mat2& inverseInPlace()
    {
        *this = inverse();
        return *this;
    }


    static Mat2 rotation(T theta) { return {std::cos(theta), -std::sin(theta), std::sin(theta), std::cos(theta)}; }


    Mat2& rotate(T theta)
    {
        *this *= rotation(theta);
        return *this;
    }


    Mat2 operator*(const Mat2& other) const
    {
        Mat2 result{};

        for (size_t row = 0; row < 2; row++) {
            for (size_t col = 0; col < 2; col++) {
                for (size_t k = 0; k < 2; k++) {
                    result(row, col) += (*this)(row, k) * other(k, col);
                }
            }
        }

        return result;
    }


    Mat2& operator*=(const Mat2& other)
    {
        *this = *this * other;
        return *this;
    }


    Mat2 operator*(T scalar) const
    {
        return {(*this)(0, 0) * scalar, (*this)(0, 1) * scalar, (*this)(1, 0) * scalar, (*this)(1, 1) * scalar};
    }


    Mat2 operator/(T scalar) const
    {
        return {(*this)(0, 0) / scalar, (*this)(0, 1) / scalar, (*this)(1, 0) / scalar, (*this)(1, 1) / scalar};
    }


    Mat2 operator-(const Mat2& other) const
    {
        return {
            (*this)(0, 0) - other(0, 0),
            (*this)(0, 1) - other(0, 1),
            (*this)(1, 0) - other(1, 0),
            (*this)(1, 1) - other(1, 1)
        };
    }
};


template <VectorElement T> Mat2<T> operator+(const Mat2<T>& a, const Mat2<T>& b)
{
    return {a(0, 0) + b(0, 0), a(0, 1) + b(0, 1), a(1, 0) + b(1, 0), a(1, 1) + b(1, 1)};
}


template <VectorElement T> Mat2<T> operator*(T scalar, const Mat2<T>& matrix) { return matrix * scalar; }


template <VectorElement T> Vec2<T> operator*(const Mat2<T>& matrix, const Vec2<T>& vector)
{
    return {matrix(0, 0) * vector.x + matrix(0, 1) * vector.y, matrix(1, 0) * vector.x + matrix(1, 1) * vector.y};
}


using Mat2i = Mat2<int>;
using Mat2f = Mat2<float>;
using Mat2d = Mat2<double>;
using Mat2Byte = Mat2<std::uint8_t>;

} // namespace vk
