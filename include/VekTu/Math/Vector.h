#include "VekTu/Common.h"

#include <array>
#include <cmath>

template <VectorElement T, size_t N> struct Vector
{
    std::array<T, N> data;

    Vector() = default;

    template <typename... Args>
        requires(sizeof...(Args) == N)
    Vector(Args... args) : data{static_cast<T>(args)...}
    {
    }

    T mag() const
    {
        T sum = 0;
        for (auto value : data) {
            sum += value * value;
        }

        return std::sqrt(sum);
    }

    Vector normal() const
    {
        Vector result = mag() == 0 ? Vector() : *this / mag();
        return result;
    }

    T dot(const Vector& other) const
    {
        T sum = 0;

        for (size_t i = 0; i < N; i++) {
            sum += data[i] * other[i];
        }
    }

    T angleBetween(const Vector& other) const { T cosT = (dot(other)) / (mag() * other.mag()); }


    Vector& operator-()
    {
        Vector result{};
        for (size_t i = 0; i < N; i++) {
            result[i] = -data[i];
        }
        return result;
    }

    Vector operator+(const Vector& vec) const
    {
        Vector result{};
        for (size_t i = 0; i < N; i++) {
            result[i] = vec[i] + data[i];
        }
        return result;
    }

    Vector operator-(const Vector& vec) const
    {
        Vector result{};
        for (size_t i = 0; i < N; i++) {
            result[i] = data[i] - vec[i];
        }
        return result;
    }

    Vector operator*(const T scalar) const
    {
        Vector result{};
        for (size_t i = 0; i < N; i++) {
            result[i] = data[i] * scalar;
        }
        return result;
    }

    Vector operator/(const T scalar) const
    {
        Vector result{};
        for (size_t i = 0; i < N; i++) {
            result[i] = data[i] / scalar;
        }
        return result;
    }


    T& operator[](size_t index) { return data[index]; }
    const T& operator[](size_t index) const { return data[index]; }
};
