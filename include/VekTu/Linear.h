#pragma once
#include "VekTu/Linear/Mat2.h"
#include "VekTu/Linear/Mat3.h"
#include "VekTu/Linear/Mat4.h"
#include "VekTu/Linear/Vec2.h"
#include "VekTu/Linear/Vec3.h"
#include "VekTu/Linear/Vec4.h"
template <VectorElement T> vk::Vec2<T> VecFromAToB(const vk::Vec2<T>& a, const vk::Vec2<T>& b) { return b - a; }

template <VectorElement T> vk::Vec3<T> VecFromAToB(const vk::Vec3<T>& a, const vk::Vec3<T>& b) { return b - a; }

template <VectorElement T> vk::Vec4<T> VecFromAToB(const vk::Vec4<T>& a, const vk::Vec4<T>& b) { return b - a; }

// TODO: add slerps to vectors
