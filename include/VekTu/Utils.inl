#include "Common.h"
#include "VekTu/Linear.h"
namespace vk {

template <VectorElement T> Mat4<T> homogeneousFromLinearMatrix(const Mat3<T>& linear) { return {}; }
template <VectorElement T> Mat3<T> homogeneousFromLinearMatrix(const Mat2<T>& linear) { return {}; }


template <VectorElement T> Mat3<T> homogeneousFromLinearMatrix(const Mat2<T>& linear, const T x, const T y)
{
    return {};
}
template <VectorElement T> Mat4<T> homogeneousFromLinearMatrix(const Mat3<T>& linear, const T x, const T y, const T z)
{
    return {};
}
template <VectorElement T> void translateMatrix(Mat2<T>& matrix, const T x, const T y) { }
template <VectorElement T> void translateMatrix(Mat3<T>& matrix, const T x, const T y, const T z) { }
template <VectorElement T> void translateMatrix(Mat4<T>& matrix, const T x, const T y, const T z, const T w) { }

template <VectorElement T> void rotateMatrix(Mat2<T>& matrix, const T angle) { }
template <VectorElement T> void rotateMatrix(Mat3<T>& matrix, const T angle) { }
template <VectorElement T> void rotateMatrix(Mat4<T>& matrix, const T angle) { }

} // namespace vk
