#pragma once
#include "VekTu/Common.h"
#include "VekTu/Linear/Vec2.h"

#include <cmath>
#include <cstdint>
#include <numbers>
template <VectorElement T> struct Rectangle;
template <VectorElement T> struct Circle;

using namespace std::numbers;

namespace vk {


template <VectorElement T> struct Shape
{
    Shape() = default;
    virtual T getArea() const = 0;
    virtual Rectangle<T> getBounds() const = 0;
    virtual bool contains(T x, T y) const = 0;
    virtual bool contains(const Vec2<T>& point) const { return contains(point.x, point.y); }
    virtual bool intersects(const Rectangle<T>& rect) const = 0;
    virtual bool intersects(const Circle<T>& cirlce) const = 0;
};

template <VectorElement T> struct Rectangle : public Shape<T>
{
    Vec2<T> topLeft;
    T width, height;

    Rectangle(const Vec2<T>& topLeft, T width, T height) : topLeft(topLeft), width(width), height(height) { }

    Rectangle(T x, T y, T width, T height) : topLeft(x, y), width(width), height(height) { }


    Vec2<T> getSize() const { return {width, height}; }

    Rectangle<T> getBounds() const override { return *this; }

    T getArea() const { return width * height; }

    Vec2<T> getCenter() const { return {topLeft.x + (width / 2), topLeft.y + (height / 2)}; }

    void setPosition(T x, T y) { topLeft = {x, y}; }

    void setPosition(const Vec2<T>& vec) { topLeft = vec; }

    T left() const { return topLeft.x; }
    T right() const { return topLeft.x + width; }
    T top() const { return topLeft.y; }
    T bottom() const { return topLeft.y + height; }

    bool contains(T x, T y) const override
    {
        return x >= topLeft.x && x <= topLeft.x + width && y >= topLeft.y && y <= topLeft.y + height;
    }

    bool intersects(const Rectangle<T>& rect) const override
    {
        return contains(rect.topLeft) || contains(rect.topLeft.x + width, rect.topLeft.y + height);
    }

    bool intersects(const Circle<T>& circle) const override
    {
        T closestX = clamp(circle.x, left(), right());
        T closestY = clamp(circle.y, top(), bottom());

        T distanceSquared = std::pow(circle.x - closestX, 2) + std::pow(circle.y - closestY, 2);

        return distanceSquared <= circle.radius * circle.radius;
    }
};


template <VectorElement T> struct Circle : public Shape<T>
{
    Vec2<T> center;
    T radius;

    Circle(T x, T y, T radius) : center(x, y), radius(radius) { }
    Circle(Vec2<T> center, T radius) : center(center), radius(radius) { }

    T getArea() const override { return std::numbers::pi * radius * radius; }
    Rectangle<T> getBounds() const override
    {
        return {{center.x - radius, center.y - radius}, radius * 2, radius * 2};
    }

    bool contains(T x, T y) { return center.dist({x, y}) <= radius; }
    bool intersects(const Rectangle<T>& rect) { return rect.intersects(*this); }
    bool intersects(const Circle<T>& other) { return center.dist(other.center) <= radius + other.radius; }
};

template <VectorElement T> bool operator==(const Rectangle<T>& left, const Rectangle<T>& right)
{
    return left.topLeft == right.topLeft && left.getSize() == right.getSize();
}

template <VectorElement T> bool operator!=(const Rectangle<T>& left, const Rectangle<T>& right)
{
    return !(left == right);
}

using Rect = Rectangle<int>;
using Rectf = Rectangle<float>;
using Rectd = Rectangle<double>;
using Rect_u = Rectangle<uint8_t>;


using iCircle = Circle<int>;
using fCircle = Circle<float>;
using dCircle = Circle<double>;
using uCircle = Circle<uint8_t>;

} // namespace vk
