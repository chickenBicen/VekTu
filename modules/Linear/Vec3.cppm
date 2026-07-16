module;

#include <cmath>
#include <cstdint>

export module Vec3;

import Common;

export template <VectorElement T> struct Vec3
{
    T x, y, z;

    Vec3(T x, T y, T z) : x(x), y(y), z(z) { }
    Vec3() : x(0), y(0), z(0) { }

    [[nodiscard]] T mag() const { return std::sqrt(x * x + y * y + z * z); }
    [[nodiscard]] T len() const { return mag(); }

    [[nodiscard]] Vec3 normalizedVector() const { return *this / mag(); }
    void normalize()
    {
        auto m = mag();
        if (!nearlyEqual(m, 0)) {
            *this = *this / m;
        }
    }


    [[nodiscard]] Vec3 cross(const Vec3& other) const
    {
        return {y * other.z - z * other.y, z * other.x - x * other.z, x * other.y - y * other.x};
    }

    [[nodiscard]] T dot(const Vec3& other) const { return (x * other.x) + (y * other.y) + (z * other.z); }

    [[nodiscard]] T dist(const Vec3& other) const { return (other - *this).mag(); }


    [[nodiscard]] T sprojection(const Vec3& other) const { return dot(other) / other.mag(); }

    [[nodiscard]] Vec3 projection(const Vec3& other) const
    {
        T scalar = dot(other) / std::pow(other.mag(), 2);
        return scalar * other;
    }


    Vec3 pointReflection(const Vec3& point) const { return point * 2 - *this; }
    static Vec3 reflectOverPoint(Vec3& vector, const Vec3& point)
    {
        Vec3 v = vector;
        vector = vector.pointReflection(point);
        return v;
    }

    Vec3 reflected(const Vec3& point) const { return point * 2 - *this; }


    Vec3 operator-(const Vec3& other) const { return Vec3(x - other.x, y - other.y, z - other.z); }

    Vec3 operator-() const { return Vec3(-x, -y, -z); }

    Vec3 operator*(const T scalar) const { return {x * scalar, y * scalar, z * scalar}; }

    Vec3& operator*=(const Vec3& other)
    {
        Vec3<T> temp = cross(other);
        x = temp.x;
        y = temp.y;
        z = temp.z;
        return *this;
    }

    Vec3 operator/(const T scalar) const { return {x / scalar, y / scalar, z / scalar}; }

    Vec3& operator/=(const T scalar)
    {
        x /= scalar;
        y /= scalar;
        z /= scalar;
        return *this;
    }

    Vec3& operator+=(const Vec3& other)
    {
        *this = *this + other;
        return *this;
    }
    Vec3& operator-=(const Vec3& other)
    {
        *this = *this - other;
        return *this;
    }
    Vec3& operator+=(const T value)
    {
        x += value;
        y += value;
        z += value;
        return *this;
    }
    Vec3& operator-=(const T value)
    {
        x -= value;
        y -= value;
        z -= value;
        return *this;
    }
};

export template <VectorElement T> Vec3<T> operator+(const Vec3<T>& a, const Vec3<T>& b)
{
    return {a.x + b.x, a.y + b.y, a.z + b.z};
}

export template <VectorElement T> bool operator==(const Vec3<T>& a, const Vec3<T>& b)
{
    return nearlyEqual(a.x, b.x) && nearlyEqual(a.y, b.y) && nearlyEqual(a.z, b.z);
}

export template <VectorElement T> bool operator!=(const Vec3<T>& a, const Vec3<T>& b) { return !(a == b); }

export using Vec3i = Vec3<int>;
export using Vec3f = Vec3<float>;
export using Vec3d = Vec3<double>;
export using Vec3u = Vec3<uint32_t>;
