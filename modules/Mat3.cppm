module;

#include <cmath>

export module Mat3;

import Common;
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

    Mat3 getMinorMatrix() const
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

    Mat3 getCofactor() const
    {
        Mat3 minorMat = getMinorMatrix();
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

    Mat3 getAdjugate() const { return getCofactor().transpose(); }


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


    Mat3 getTranspose() const
    { return {data[0], data[3], data[6], data[1], data[4], data[7], data[2], data[5], data[8]}; }
    Mat3 transpose()
    {
        *this = getTranspose();
        return *this;
    }

    Mat3 getInverse() const { return (T(1) / det()) * getAdjugate(); }


    static Mat3<T> getAffineTranslation(T x, T y) { return {1, 0, x, 0, 1, y, 0, 0, 1}; }
    static Mat3<T> getAffineRotation(const double theta)
    { return {std::cos(theta), -std::sin(theta), 0, std::sin(theta), std::cos(theta), 0, 0, 0, 1}; }

    static Mat3<T> getAffineTransformation(double scaleX,
                                           double scaleY,
                                           double theta,
                                           double translationX,
                                           double translationY)
    {
        Mat3<T> scale{scaleX, 0, 0, scaleY};
        Mat3<T> rotation = getAffineRotation(theta);
        Mat3<T> translation = getAffineTranslation(translationX, translationY);

        return translation * rotation * scale;
    }

    T& operator[](size_t index) { return data[index]; }

    const T& operator[](size_t index) const { return data[index]; }
};
