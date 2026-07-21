#pragma once

#include "VekTu/Common.h"

#include <cmath>
#include <cstdint>

namespace vk {


template <VectorElement T> struct Vec4
{
    T x, y, z, w;

    Vec4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) { }
    Vec4() : x(0), y(0), z(0), w(0) { }

    [[nodiscard]] T mag() const { return std::sqrt(x * x + y * y + z * z + w * w); }
    [[nodiscard]] T len() const { return mag(); }

    [[nodiscard]] const Vec4 normalizedVector() const { return this / mag(); }
    void normalize()
    {
        auto m = mag();
        if (!nearlyEqual(m, 0)) {
            *this = *this / m;
        }
    }


    [[nodiscard]] T dot(const Vec4& other) const
    {
        return (x * other.x) + (y * other.y) + (z * other.z) + (w * other.w);
    }

    [[nodiscard]] T distance(const Vec4& other) const { return (other - *this).mag(); }


    [[nodiscard]] T sprojection(const Vec4& other) const { return dot(other) / other.mag(); }

    [[nodiscard]] Vec4 projection(const Vec4& other) const
    {
        T scalar = dot(other) / std::pow(other.mag(), 2);
        return scalar * other;
    }


    Vec4 pointReflection(const Vec4& point) const { return point * 2 - *this; }
    static Vec4 reflectOverPoint(Vec4& vector, const Vec4& point)
    {
        Vec4 v = vector;
        vector = vector.pointReflection(point);
        return v;
    }


    Vec4 operator-(const Vec4 other) const { return {x - other.x, y - other.y, z - other.z, w - other.w}; }

    Vec4 operator*(const T scalar) const { return {x * scalar, y * scalar, z * scalar, w * scalar}; }

    Vec4 operator/(const T scalar) const { return {x / scalar, y / scalar, z / scalar, w / scalar}; }


    Vec4& operator-=(const T value)
    {
        x -= value;
        y -= value;
        z -= value;
        w -= value;
        return *this;
    }

    Vec4& operator+=(const T value)
    {
        x += value;
        y += value;
        z += value;
        w += value;
        return *this;
    }

    Vec4 operator*=(const T scalar)
    {
        *this = *this * scalar;
        return *this;
    }

    Vec4 operator/=(const T scalar)
    {
        *this /= scalar;
        return *this;
    }

    Vec4& operator*=(const Vec4& other)
    {
        *this = *this * other;
        return *this;
    }
};

template <VectorElement T> bool operator==(const Vec4<T>& a, const Vec4<T>& b)
{
    return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y) && nearlyEqual(a.z, b.z) && nearlyEqual(a.w, b.w);
}

template <VectorElement T> bool operator!=(const Vec4<T>& a, const Vec4<T>& b) { return !(a == b); }

template <VectorElement T> Vec4<T> operator+(const Vec4<T>& a, const Vec4<T> b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.y, a.z + b.z, a.w + b.w};
}

using Vec4i = Vec4<int>;
using Vec4f = Vec4<float>;
using Vec4d = Vec4<double>;
using Vec4u = Vec4<uint32_t>;

} // namespace vk
