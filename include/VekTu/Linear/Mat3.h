#pragma once

#include "Mat2.h"
#include "Vec3.h"
#include "VekTu/Common.h"
#include "VekTu/Linear/Vec2.h"

#include <cassert>
#include <cmath>
#include <cstdint>
#include <type_traits>

namespace vk {


template <VectorElement T> struct Mat3
{
    std::array<std::array<T, 3>, 3> data;

    Mat3() : data{{0, 0, 0}, {0, 0, 0}, {0, 0, 0}} { }

    Mat3(T m00, T m01, T m02, T m10, T m11, T m12, T m20, T m21, T m22)
        : data{{m00, m10, m20}, {m01, m11, m21}, {m02, m12, m22}}
    {
    }

    Mat3(const Vec3<T>& a, const Vec3<T>& b, const Vec3<T>& c)
    {
        (*this)(0, 0) = a.x;
        (*this)(1, 0) = a.y;
        (*this)(2, 0) = a.z;

        (*this)(0, 1) = b.x;
        (*this)(1, 1) = b.y;
        (*this)(2, 1) = b.z;

        (*this)(0, 2) = c.x;
        (*this)(1, 2) = c.y;
        (*this)(2, 2) = c.z;
    }

    [[nodiscard]] static Mat3 identity() { return {1, 0, 0, 0, 1, 0, 0, 0, 1}; }


    T getMinorFromPosition(size_t x, size_t y) const
    {
        assert(x < 3 && y < 3);
        switch (y * 3 + x) {
            case 0 : return Mat2<T>{(*this)(1, 1), (*this)(1, 2), (*this)(2, 1), (*this)(2, 2)}.det();
            case 1 : return Mat2<T>{(*this)(1, 0), (*this)(1, 2), (*this)(2, 0), (*this)(2, 2)}.det();
            case 2 : return Mat2<T>{(*this)(1, 0), (*this)(1, 1), (*this)(2, 0), (*this)(2, 1)}.det();
            case 3 : return Mat2<T>{(*this)(0, 1), (*this)(0, 2), (*this)(2, 1), (*this)(2, 2)}.det();
            case 4 : return Mat2<T>{(*this)(0, 0), (*this)(0, 2), (*this)(2, 0), (*this)(2, 2)}.det();
            case 5 : return Mat2<T>{(*this)(0, 0), (*this)(0, 1), (*this)(2, 0), (*this)(2, 1)}.det();
            case 6 : return Mat2<T>{(*this)(0, 1), (*this)(0, 2), (*this)(1, 1), (*this)(1, 2)}.det();
            case 7 : return Mat2<T>{(*this)(0, 0), (*this)(0, 2), (*this)(1, 0), (*this)(1, 2)}.det();
            case 8 : return Mat2<T>{(*this)(0, 0), (*this)(0, 1), (*this)(1, 0), (*this)(1, 1)}.det();
        }
    }

    Mat3 minorMatrix() const
    {
        Mat3 mat{
            getMinorFromPosition(0, 0),
            getMinorFromPosition(1, 0),
            getMinorFromPosition(2, 0),
            getMinorFromPosition(0, 1),
            getMinorFromPosition(1, 1),
            getMinorFromPosition(2, 1),
            getMinorFromPosition(0, 2),
            getMinorFromPosition(1, 2),
            getMinorFromPosition(2, 2)
        };

        return mat;
    }

    Mat3 cofactor() const
    {
        Mat3 minorMat = minorMatrix();
        return {
            minorMat(0, 0),
            -minorMat(0, 1),
            minorMat(0, 2),
            -minorMat(1, 0),
            minorMat(1, 1),
            -minorMat(1, 2),
            minorMat(2, 0),
            -minorMat(2, 1),
            minorMat(2, 2)
        };
    }

    Mat3 adjugate() const { return cofactor().transposeInPlace(); }


    [[nodiscard]] T det() const
    {
        T term1 = (*this)(0, 0) * (*this)(1, 1) * (*this)(2, 2);
        T term2 = (*this)(0, 1) * (*this)(1, 2) * (*this)(2, 0);
        T term3 = (*this)(0, 2) * (*this)(1, 0) * (*this)(2, 1);

        T term4 = (*this)(2, 0) * (*this)(1, 1) * (*this)(0, 2);
        T term5 = (*this)(2, 1) * (*this)(1, 2) * (*this)(0, 0);
        T term6 = (*this)(2, 2) * (*this)(1, 0) * (*this)(0, 1);

        return (term1 + term2 + term3) - (term4 + term5 + term6);
    }


    Mat3 transpose() const
    {
        return {
            (*this)(0, 0),
            (*this)(0, 1),
            (*this)(0, 2),

            (*this)(1, 0),
            (*this)(1, 1),
            (*this)(1, 2),

            (*this)(2, 0),
            (*this)(2, 1),
            (*this)(2, 2)
        };
    }
    Mat3 transposeInPlace()
    {
        *this = transpose();
        return *this;
    }

    Mat3 inverse() const
    {
        assert(det() != 0);
        return (T(1) / det()) * adjugate();
    }
    Mat3 inverseInPlace()
    {
        *this = inverse();
        return *this;
    }


    static Mat3<T> getAffineTranslation(T x, T y) { return {1, 0, x, 0, 1, y, 0, 0, 1}; }
    static Mat3<T> getAffineRotation(const T theta)
    {
        return {std::cos(theta), -std::sin(theta), 0, std::sin(theta), std::cos(theta), 0, 0, 0, 1};
    }

    static Mat3<T> getAffineTransformation(T scaleX, T scaleY, T theta, T translationX, T translationY)
    {
        Mat3<T> scale{scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1};
        Mat3<T> rotation = getAffineRotation(theta);
        Mat3<T> translation = getAffineTranslation(translationX, translationY);

        return translation * rotation * scale;
    }

    template <VectorElement U> static Mat3<U> getRotationFromAxis(const Vec3<U>& axis, const U angle)
    {
        static_assert(std::is_floating_point_v<U>);

        Vec3<U> unit = axis / axis.mag();

        U cosine = std::cos(angle);
        U sine = std::sin(angle);

        U t = U(1) - cosine;

        Mat3<U> result{};

        result(0, 0) = t * unit.x * unit.x + cosine;
        result(0, 1) = t * unit.x * unit.y - sine * unit.z;
        result(0, 2) = t * unit.x * unit.z + sine * unit.y;

        result(1, 0) = t * unit.x * unit.y + sine * unit.z;
        result(1, 1) = t * unit.y * unit.y + cosine;
        result(1, 2) = t * unit.y * unit.z - sine * unit.x;

        result(2, 0) = t * unit.x * unit.z - sine * unit.y;
        result(2, 1) = t * unit.y * unit.z + sine * unit.x;
        result(2, 2) = t * unit.z * unit.z + cosine;

        return result;
    }

    template <VectorElement U> static Mat3<U> roll(const U angle) { return getRotationFromAxis({1, 0, 0}, angle); }

    template <VectorElement U> static Mat3<U> pitch(const U a) { return getRotationFromAxis({0, 1, 0}, a); }

    template <VectorElement U> static Mat3<U> yaw(const U angle) { return getRotationFromAxis({0, 0, 1}, angle); }


    T& operator()(size_t row, size_t col) { return data[col][row]; }

    const T& operator()(size_t row, size_t col) const { return data[col][row]; }

    Mat3 operator*(const Mat3<T>& other) const
    {
        Mat3 result{};
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                for (int k = 0; k < 3; k++) {
                    result(col, row) += (*this)(k, row) * other(col, k);
                }
            }
        }
        return result;
    }

    Mat3 operator*(const T scalar) const
    {
        return {
            (*this)(0, 0) * scalar,
            (*this)(0, 1) * scalar,
            (*this)(0, 2) * scalar,
            (*this)(1, 0) * scalar,
            (*this)(1, 1) * scalar,
            (*this)(1, 2) * scalar,
            (*this)(2, 0) * scalar,
            (*this)(2, 1) * scalar,
            (*this)(2, 2) * scalar
        };
    }


    Mat3 operator-(const Mat3& other) const
    {
        return {
            (*this)(0, 0) - other(0, 0),
            (*this)(0, 1) - other(0, 1),
            (*this)(0, 2) - other(0, 2),
            (*this)(1, 0) - other(1, 0),
            (*this)(1, 1) - other(1, 1),
            (*this)(1, 2) - other(1, 2),
            (*this)(2, 0) - other(2, 0),
            (*this)(2, 1) - other(2, 1),
            (*this)(2, 2) - other(2, 2)
        };
    }
};

template <VectorElement T> Mat3<T> operator+(const Mat3<T>& first, const Mat3<T>& second)
{
    return {
        first(0, 0) + second(0, 0),
        first(0, 1) + second(0, 1),
        first(0, 2) + second(0, 2),
        first(1, 0) + second(1, 0),
        first(1, 1) + second(1, 1),
        first(1, 2) + second(1, 2),
        first(2, 0) + second(2, 0),
        first(2, 1) + second(2, 1),
        first(2, 2) + second(2, 2)
    };
}

template <VectorElement T> Mat3<T> operator*(T scalar, const Mat3<T>& matrix) { return matrix * scalar; }


template <VectorElement T> Vec3<T> operator*(const Mat3<T>& matrix, const Vec3<T>& vector)
{
    Vec3<T> v = vector;
    v.x = matrix(0, 0) * vector.x + matrix(0, 1) * vector.y + matrix(0, 2) * vector.z;
    v.y = matrix(1, 0) * vector.x + matrix(1, 1) * vector.y + matrix(1, 2) * vector.z;
    v.z = matrix(2, 0) * vector.x + matrix(2, 1) * vector.y + matrix(2, 2) * vector.z;
    return v;
}

using Mat3i = Mat3<int>;
using Mat3f = Mat3<float>;
using Mat3d = Mat3<double>;
using Mat3b = Mat3<uint8_t>;

} // namespace vk
