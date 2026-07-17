#pragma once
#include "VekTu/Common.h"

#include <cmath>
#include <cstdint>

/**
 * @brief 2d vector implementation for graphics and positioning. Only accepts "Vector elements"
 * which are types that can do basic arithmetic operations
 */
template <VectorElement T> struct Vec2
{
    T x, y;

    Vec2() : x(0), y(0) { }
    Vec2(const T x, const T y) : x(x), y(y) { }

    [[nodiscard]] T mag() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] T len() const { return std::sqrt(x * x + y * y); }

    [[nodiscard]] T dot(const Vec2& v) const { return x * v.x + y * v.y; }
    [[nodiscard]] T cross(const Vec2& v) const { return x * v.y - y * v.x; }
    [[nodiscard]] T dist(const Vec2& v) const { return (v - *this).mag(); }


    [[nodiscard]] Vec2 normalizedVector() const { return *this / mag(); }
    void normalize()
    {
        auto m = mag();
        if (!nearlyEqual(m, 0)) {
            *this = *this / m;
        }
    }

    [[nodiscard]] T sprojection(const Vec2& other) const { return dot(other) / other.mag(); }

    [[nodiscard]] Vec2 projection(const Vec2& other) const
    {
        T scalar = dot(other) / std::pow(other.mag(), 2);
        return scalar * other;
    }


    Vec2 pointReflection(const Vec2& point) const { return point * 2 - *this; }
    static Vec2 reflectOverPoint(Vec2& vector, const Vec2& point)
    {
        Vec2 v = vector;
        vector = vector.pointReflection(point);
        return v;
    }

    Vec2 operator-(const Vec2& other) const { return Vec2(x - other.x, y - other.y); }
    Vec2 operator-() const { return Vec2(-x, -y); }

    template <typename U> Vec2 operator*(const U scalar) const { return {T(x * scalar), T(y * scalar)}; }
    template <typename U> Vec2 operator/(const U scalar) const { return {T(x / scalar), T(y / scalar)}; }

    Vec2& operator+=(const Vec2& other)
    {
        *this = *this + other;
        return *this + other;
    }
    Vec2& operator-=(const Vec2& other)
    {
        *this = *this - other;
        return *this - other;
    }
    Vec2& operator+=(const T value)
    {
        x += value;
        y += value;
        return *this;
    }
    Vec2& operator-=(const T value)
    {
        x -= value;
        y -= value;
        return *this;
    }

    // TODO: add operators for matrices and transformations.
    static Vec2<T> lerp(const Vec2<T>& start, const Vec2<T> end, const double percent)
    {
        return start * (1 - percent) + end * percent;
    }
};

template <VectorElement T> Vec2<T> operator*(const T scalar, const Vec2<T>& v)
{
    return {v.x * scalar, v.y * scalar};
}

template <VectorElement T> Vec2<T> operator+(const Vec2<T>& a, const Vec2<T>& b) { return {a.x + b.x, a.y + b.y}; }

template <VectorElement T, typename U> Vec2<T> operator+(const Vec2<T>& a, const U scalar)
{
    return {a.x + scalar, a.y + scalar};
}

template <VectorElement T> bool operator==(const Vec2<T>& a, const Vec2<T>& b)
{
    if constexpr (std::floating_point<T>) {
        return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y);

    } else {
        return a.x == b.x && a.y == b.y;
    }
}

template <VectorElement T> bool operator!=(const Vec2<T>& a, const Vec2<T>& b) { return !(a == b); }

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;
using Vec2d = Vec2<double>;
using Vec2u = Vec2<uint32_t>;
