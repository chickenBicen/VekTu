module;

#include <cassert>
#include <cmath>
#include <cstdint>

export module Mat3;

import Common;
import Vec2;
import Vec3;
import Mat2;

export template <VectorElement T> struct Mat3
{
    std::array<T, 9> data;

    Mat3() : data{0, 0, 0, 0, 0, 0, 0, 0, 0} { }

    Mat3(T a, T b, T c, T d, T e, T f, T g, T h, T i) : data{a, b, c, d, e, f, g, h, i} { }

    [[nodiscard]] static Mat3 identity() { return {1, 0, 0, 0, 1, 0, 0, 0, 1}; }


    T getMinorFromPosition(size_t x, size_t y) const
    {
        assert(x < 3 && y < 3);
        switch (y * 3 + x) {
            case 0 : return Mat2<T>{data[4], data[5], data[7], data[8]}.det();
            case 1 : return Mat2<T>{data[3], data[5], data[6], data[8]}.det();
            case 2 : return Mat2<T>{data[3], data[4], data[6], data[7]}.det();
            case 3 : return Mat2<T>{data[1], data[2], data[7], data[8]}.det();
            case 4 : return Mat2<T>{data[0], data[2], data[6], data[8]}.det();
            case 5 : return Mat2<T>{data[0], data[1], data[6], data[7]}.det();
            case 6 : return Mat2<T>{data[1], data[2], data[4], data[5]}.det();
            case 7 : return Mat2<T>{data[0], data[2], data[3], data[5]}.det();
            case 8 : return Mat2<T>{data[0], data[1], data[3], data[4]}.det();
        }
    }

    Mat3 minorMatrix() const
    {
        Mat3 mat{
            getMinorFromPosition(0, 0),
            getMinorFromPosition(0, 1),
            getMinorFromPosition(0, 2),
            getMinorFromPosition(1, 0),
            getMinorFromPosition(1, 1),
            getMinorFromPosition(1, 2),
            getMinorFromPosition(2, 0),
            getMinorFromPosition(2, 1),
            getMinorFromPosition(2, 2)
        };

        return mat;
    }

    Mat3 cofactor() const
    {
        Mat3 minorMat = minorMatrix();
        return {
            minorMat[0],
            -minorMat[1],
            minorMat[2],
            -minorMat[3],
            minorMat[4],
            -minorMat[5],
            minorMat[6],
            -minorMat[7],
            minorMat[8]
        };
    }

    Mat3 adjugate() const { return cofactor().transposeInPlace(); }


    [[nodiscard]] T det() const
    {
        T term1 = data[0] * data[4] * data[8];
        T term2 = data[1] * data[5] * data[6];
        T term3 = data[2] * data[3] * data[7];

        T term4 = data[6] * data[4] * data[2];
        T term5 = data[7] * data[5] * data[0];
        T term6 = data[8] * data[3] * data[1];

        return (term1 + term2 + term3) - (term4 + term5 + term6);
    }


    Mat3 transpose() const
    { return {data[0], data[3], data[6], data[1], data[4], data[7], data[2], data[5], data[8]}; }
    void transposeInPlace()
    {
        *this = transpose();
        return *this;
    }

    Mat3 inverse() const
    {
        assert(det() != 0);
        return (T(1) / det()) * adjugate();
    }
    void inverseInPlace()
    {
        *this = inverse();
        return *this;
    }


    static Mat3<T> getAffineTranslation(T x, T y) { return {1, 0, x, 0, 1, y, 0, 0, 1}; }
    static Mat3<T> getAffineRotation(const T theta)
    { return {std::cos(theta), -std::sin(theta), 0, std::sin(theta), std::cos(theta), 0, 0, 0, 1}; }

    static Mat3<T>
        getAffineTransformation(T scaleX, T scaleY, T theta, T translationX, T translationY)
    {
        Mat3<T> scale{scaleX, 0, 0, 0, scaleY, 0, 0, 0, 1};
        Mat3<T> rotation = getAffineRotation(theta);
        Mat3<T> translation = getAffineTranslation(translationX, translationY);

        return translation * rotation * scale;
    }
    T& at(size_t index)
    {
        assert(index < 9);
        return data[index];
    }

    T& operator[](size_t index) { return at(index); }

    const T& operator[](size_t index) const { return at(index); }

    Mat3 operator*(const Mat3<T>& other) const
    {
        Mat3 result{};
        for (int row = 0; row < 3; row++) {
            for (int col = 0; col < 3; col++) {
                for (int k = 0; k < 3; k++) {
                    result[row * 3 + col] += data[row * 3 + k] * other[k * 3 + col];
                }
            }
        }
        return result;
    }

    Mat3 operator*(const T scalar) const
    {
        return {
            data[0] * scalar,
            data[1] * scalar,
            data[2] * scalar,
            data[3] * scalar,
            data[4] * scalar,
            data[5] * scalar,
            data[6] * scalar,
            data[7] * scalar,
            data[8] * scalar
        };
    }


    Mat3 operator-(const Mat3& other) const
    {
        return {
            data[0] - other[0],
            data[1] - other[1],
            data[2] - other[2],
            data[3] - other[3],
            data[4] - other[4],
            data[5] - other[5],
            data[6] - other[6],
            data[7] - other[7],
            data[8] - other[8]
        };
    }
};

export template <VectorElement T> Mat3<T> operator+(const Mat3<T>& first, const Mat3<T>& second)
{
    return {
        first[0] + second[0],
        first[1] + second[1],
        first[2] + second[2],
        first[3] + second[3],
        first[4] + second[4],
        first[5] + second[5],
        first[6] + second[6],
        first[7] + second[7],
        first[8] + second[8]
    };
}

export template <VectorElement T> Mat3<T> operator*(T scalar, const Mat3<T>& matrix)
{ return matrix * scalar; }


export template <VectorElement T> Vec3<T> operator*(const Mat3<T>& matrix, const Vec3<T>& vector)
{
    Vec3<T> v = vector;
    v.x = matrix[0] * vector.x + matrix[1] * vector.y + matrix[2] * vector.z;
    v.y = matrix[3] * vector.x + matrix[4] * vector.y + matrix[5] * vector.z;
    v.z = matrix[6] * vector.x + matrix[7] * vector.y + matrix[8] * vector.z;
    return v;
}

export using Mat3i = Mat3<int>;
export using Mat3f = Mat3<float>;
export using Mat3d = Mat3<double>;
export using Mat3b = Mat3<uint8_t>;
