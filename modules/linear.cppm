module;
export module linear;
import Common;
import Vec2;
import Vec3;
import Vec4;

export template <VectorElement T> Vec2<T> VecFromAToB(const Vec2<T>& a, const Vec2<T>& b)
{ return b - a; }

export template <VectorElement T> Vec3<T> VecFromAToB(const Vec3<T>& a, const Vec3<T>& b)
{ return b - a; }

export template <VectorElement T> Vec4<T> VecFromAToB(const Vec4<T>& a, const Vec4<T>& b)
{ return b - a; }

// TODO: add slerps to vectors
