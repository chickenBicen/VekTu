#pragma once

#include "Vec2.h"
#include "VekTu/Common.h"

#include <cmath>
#include <cstddef>
#include <cstdint>

template <VectorElement T> struct Mat2
{
    std::array<T, 4> data;
    Mat2() : data{0, 0, 0, 0} { }
    Mat2(T a, T b, T c, T d) : data{a, b, c, d} { }


    [[nodiscard]] static Mat2 identity() { return {1, 0, 0, 1}; }


    [[nodiscard]] T det() const { return data[0] * data[3] - data[1] * data[3]; }

    Mat2 getTranspose() const { return {data[0], data[2], data[1], data[3]}; }
    Mat2 transpose()
    {
        *this = getTranspose();
        return *this;
    }


    Mat2 getInverse() const { return (T(1) / det()) * Mat2{data[3], -data[1], -data[2], data[0]}; }

    Mat2 inverse()
    {
        *this = getInverse();
        return *this;
    }


    static Mat2 rotation(const T theta)
    {
        return {std::cos(theta), -std::sin(theta), std::sin(theta), std::cos(theta)};
    }

    Mat2 rotate(const T theta)
    {
        *this *= rotation(theta);
        return *this;
    }

    T& operator[](size_t index) { return data[index]; }

    const T& operator[](size_t index) const { return data[index]; }

    Mat2 operator*(const Mat2& m) const
    {
        return {
            (data[0] * m[0] + data[1] * m[2]), // m00
            (data[0] * m[1] + data[1] * m[3]), // m01
            (data[2] * m[0] + data[3] * m[2]), // m10
            (data[2] * m[1] + data[3] * m[3])  // m11
        };
    }

    Mat2 operator*(const T scalar) const
    {
        return {data[0] * scalar, data[1] * scalar, data[2] * scalar, data[3] * scalar};
    }


    Mat2& operator*=(const Mat2& m)
    {
        *this = *this * m;
        return *this;
    }


    Mat2 operator/(const T scalar) const
    {
        return {data[0] / scalar, data[1] / scalar, data[2] / scalar, data[3] / scalar};
    }

    Mat2 operator-(const Mat2& other) const
    {
        return {data[0] - other[0], data[1] - other[1], data[2] - other[2], data[3] - other[3]};
    }
};

template <VectorElement T> Mat2<T> operator+(const Mat2<T>& a, const Mat2<T> b)
{
    return {a[0] + b[0], a[1] + b[1], a[2] + b[2], a[3] + b[3]};
}

template <VectorElement T> Vec2<T> operator*(const Mat2<T>& matrix, const Vec2<T>& vector)
{
    return {(matrix[0] * vector.x) + (matrix[1] * vector.y), (matrix[2] * vector.x) + (matrix[3] * vector.y)};
}

template <VectorElement T> Mat2<T> operator*(T scalar, const Mat2<T>& matrix)
{
    return {matrix[0] * scalar, matrix[1] * scalar, matrix[2] * scalar, matrix[3] * scalar};
}

using Mat2i = Mat2<int>;
using Mat2f = Mat2<float>;
using Mat2d = Mat2<double>;
using Mat2Byte = Mat2<std::uint8_t>;
