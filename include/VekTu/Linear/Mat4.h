#pragma once

#include "Mat3.h"
#include "Vec4.h"
#include "VekTu/Common.h"

#include <array>
#include <cstddef>

namespace vk {

template <VectorElement T> struct Mat4
{
    std::array<std::array<T, 4>, 4> data;

    Mat4() : data{{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}} { }
    Mat4(const Vec4<T>& a, const Vec4<T> b, const Vec4<T> c, const Vec4<T> d)
    {
        (*this)(0, 0) = a.x;
        (*this)(1, 0) = a.y;
        (*this)(2, 0) = a.z;
        (*this)(3, 0) = a.w;

        (*this)(0, 1) = b.x;
        (*this)(1, 1) = b.y;
        (*this)(2, 1) = b.z;
        (*this)(3, 1) = b.w;

        (*this)(0, 2) = c.x;
        (*this)(1, 2) = c.y;
        (*this)(2, 2) = c.z;
        (*this)(3, 2) = c.w;


        (*this)(0, 3) = d.x;
        (*this)(1, 3) = d.y;
        (*this)(2, 3) = d.z;
        (*this)(3, 3) = d.w;
    }

    [[nodiscard]] T det() const
    {
        T result = 0;

        for (size_t col = 0; col < 4; col++) {
            T minor = getMinorFromPosition(0, col);

            result += (col % 2 == 0) ? (*this)(0, col) * minor : -(*this)(0, col) * minor;
        }

        return result;
    }

    [[nodiscard]] static Mat4 identity() { return {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}}; }

    T getMinorFromPosition(size_t row, size_t col) const
    {
        assert(row < 4 && col < 4);
        Mat3<T> minor{};
        size_t dstRow = 0;
        for (size_t r = 0; r < 4; r++) {
            if (r == row) continue;
            size_t dstCol = 0;
            for (size_t c = 0; c < 4; c++) {
                if (c == col) continue;

                minor(dstRow, dstCol) = (*this)(r, c);
                dstCol++;
            }
            dstRow++;
        }
        return minor.det();
    }

    Mat4<T> minorMatrix() const
    {
        Mat4<T> result;
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                result(row, col) = getMinorFromPosition(row, col);
            }
        }
        return result;
    }

    Mat4 cofactor() const
    {
        Mat4<T> result{};
        Mat4<T> minorMat = minorMatrix();
        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                result(row, col) = (row + col) % 2 == 0 ? minorMat(row, col) : -minorMat(row, col);
            }
        }
        return result;
    }

    Mat4 adjugate() const { return cofactor().transpose(); }

    [[nodiscard]] Mat4 transpose() const
    {
        Mat4 result{};

        for (size_t row = 0; row < 4; row++) {
            for (size_t col = 0; col < 4; col++) {
                result(row, col) = (*this)(col, row);
            }
        }
        return result;
    }

    [[nodiscard]] Mat4 inverse() const
    {
        assert(det() != 0);
        return (T(1) / det()) * adjugate();
    }

    Mat4 transposeInPlace()
    {
        *this = transpose();
        return *this;
    }

    Mat4 inverseInPlace()
    {
        *this = inverse();
        return *this;
    }


    T& operator()(size_t row, size_t col) { return data[col][row]; }

    const T& operator()(size_t row, size_t col) const { return data[col][row]; }
};

}; // namespace vk
