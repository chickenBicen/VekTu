module;

#include <cmath>
#include <concepts>

export module Common;

template <typename T> struct Epsilon
{
    static constexpr T value = T(1e-6);
};

template <> struct Epsilon<double>
{
    static constexpr double value = 1e-12;
};

template <> struct Epsilon<int>
{
    static constexpr int value = 0;
};

export template <typename T> bool nearlyEqual(const T a, const T b) { return std::abs(a - b) < Epsilon<T>::value; }

export template <typename T>
concept VectorElement = requires(T a, T b) {
    { a + b } -> std::convertible_to<T>;
    { a - b } -> std::convertible_to<T>;
    { a * b } -> std::convertible_to<T>;
    { a / b } -> std::convertible_to<T>;

    { a == b } -> std::convertible_to<bool>;
    { a != b } -> std::convertible_to<bool>;
};

export template <VectorElement T> T clamp(T toBeClamped, T min, T max)
{
    if (toBeClamped < min) {
        return min;
    } else if (toBeClamped > max) {
        return max;
    }
    return toBeClamped;
}
