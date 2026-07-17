#pragma once
#include "VekTu/Linear/Mat2.h"
#include "VekTu/Linear/Mat3.h"
#include "VekTu/Linear/Vec2.h"
#include "VekTu/Linear/Vec3.h"
#include "VekTu/Linear/Vec4.h"

template <VectorElement T> Vec2<T> VecFromAToB(const Vec2<T>& a, const Vec2<T>& b) { return b - a; }

template <VectorElement T> Vec3<T> VecFromAToB(const Vec3<T>& a, const Vec3<T>& b) { return b - a; }

template <VectorElement T> Vec4<T> VecFromAToB(const Vec4<T>& a, const Vec4<T>& b) { return b - a; }

// TODO: add slerps to vectors
