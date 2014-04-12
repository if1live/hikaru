// Ŭnicode please
#pragma once

#include <cmath>
#include "custom_CCGeometry.h"

namespace qb {;
//vector
template<typename T>  struct Vector2;
template<typename T>  struct Vector3;
template<typename T>  struct Vector4;
typedef Vector2<float> vec2;
typedef Vector2<int> ivec2;
typedef Vector3<float> vec3;
typedef Vector3<int> ivec3;
typedef Vector4<float> vec4;
typedef Vector4<int> ivec4;

template<typename T>
struct Vector2 {
	typedef T ElemType;
	enum {
		Dimension = 2,
	};
	union {
		struct {
			T x;
			T y;
		};
		T value[Dimension];
	};
	Vector2(T x, T y) : x(x), y(y) {}
	Vector2(const qb::Point &p) : x(p.x), y(p.y) {}
	Vector2() : x(0), y(0) {}
	Vector2(const T(&data)[2]) : x(data[0]), y(data[1]) {}

	bool operator==(const Vector2 &b) const { return VectorEqual(*this, b); }
	bool operator!=(const Vector2 &b) const { return VectorNotEqual(*this, b); }
	Vector2 &operator+=(const Vector2 &b) { return VectorAddThis(*this, b); }
	Vector2 operator+(const Vector2 &b) const { return VectorAdd(*this, b); }
	Vector2 &operator-=(const Vector2 &b) { return VectorSubtractThis(*this, b); }
	Vector2 operator-(const Vector2 &b) const { return VectorSubtract(*this, b); }
	Vector2 &operator*=(const ElemType t) { return VectorMultiplyThis(*this, t); }
	Vector2 operator*(const ElemType t) const { return VectorMultiply(*this, t); }
	Vector2 &operator/=(const ElemType t) { return VectorDivideThis(*this, t); }
	Vector2 operator/(const ElemType t) const { return VectorDivide(*this, t); }
	bool operator<=(const Vector2 &b) const { return VectorLessEqual(*this, b); }
	bool operator<(const Vector2 &b) const { return VectorLess(*this, b); }
	bool operator>=(const Vector2 &b) const { return VectorGreaterEqual(*this, b); }
	bool operator>(const Vector2 &b) const { return VectorGreater(*this, b); }

	ElemType LengthSquare() const { return VectorLengthSquare(*this); }
	ElemType Length() const { return VectorLength(*this); }
	ElemType Dot(const Vector2 &b) const { return VectorDot(*this, b); }
	Vector2 &Normalized() { return VectorNormalized(*this); }
	Vector2 Normalize() const { return VectorNormalize(*this); }
	bool IsZero(float error_range=0.0001) const { return VectorIsZero(*this, error_range); }
	void SetZero() { VectorSetZero(*this); }
};

template<typename T>
struct Vector3 {
	typedef T ElemType;
	enum {
		Dimension = 3,
	};
	union {
		struct {
			T x;
			T y;
			T z;
		};
		T value[Dimension];
	};
	Vector3(T x, T y, T z) : x(x), y(y), z(z) {}
	Vector3() : x(0), y(0), z(0) {}

	template<typename T2>
	Vector3(const Vector2<T2> &o) : x(o.x), y(o.y), z(0) {}
	Vector3(const T(&data)[3]) : x(data[0]), y(data[1]), z(data[2]) {}

	bool operator==(const Vector3 &b) const { return VectorEqual(*this, b); }
	bool operator!=(const Vector3 &b) const { return VectorNotEqual(*this, b); }
	Vector3 &operator+=(const Vector3 &b) { return VectorAddThis(*this, b); }
	Vector3 operator+(const Vector3 &b) const { return VectorAdd(*this, b); }
	Vector3 &operator-=(const Vector3 &b) { return VectorSubtractThis(*this, b); }
	Vector3 operator-(const Vector3 &b) const { return VectorSubtract(*this, b); }
	Vector3 &operator*=(const ElemType t) { return VectorMultiplyThis(*this, t); }
	Vector3 operator*(const ElemType t) const { return VectorMultiply(*this, t); }
	Vector3 &operator/=(const ElemType t) { return VectorDivideThis(*this, t); }
	Vector3 operator/(const ElemType t) const { return VectorDivide(*this, t); }
	ElemType LengthSquare() const { return VectorLengthSquare(*this); }
	ElemType Length() const { return VectorLength(*this); }
	ElemType Dot(const Vector3 &b) const { return VectorDot(*this, b); }
	Vector3 &Normalized() { return VectorNormalized(*this); }
	Vector3 Normalize() const { return VectorNormalize(*this); }
	bool IsZero(float error_range=0.0001) const { return VectorIsZero(*this, error_range); }
	void SetZero() { VectorSetZero(*this); }
};

template<typename T>
struct Vector4 {
	typedef T ElemType;
	enum {
		Dimension = 4,
	};
	union {
		struct {
			T x;
			T y;
			T z;
			T w;
		};
		T value[Dimension];
	};
	Vector4(T x, T y, T z, T w) : x(x), y(y), z(z), w(w) {}
	Vector4() : x(0), y(0), z(0), w(0) {}
	Vector4(const T(&data)[4]) : x(data[0]), y(data[1]), z(data[2]), w(data[3]) {}
};


//vector 다루는 전역 함수는 연산자오버로딩관련된것이 많지만
//템플릿과 연결될 경우, 의도하지 않는 결과를 만들어낼수 있어서(벡터가 아닌 다른 클래스의 연산자 오버로딩까지 지원하려고 해버려서)
//연산자오버로딩은 전역함수가 아니라 클래스 멤버함수로 하기로 했다
//대신에 로직은 공통으로 유지하기 위해서 전역함수를 만들었다
//전역함수앞에는 Vector를 prefix로 붙여서 최악의 사태에서 이름충돌을 방지했다
template<typename VecType>
bool VectorEqual(const VecType &a, const VecType &b) {
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		if (a.value[i] != b.value[i]) {
			return false;
		}
	}
	return true;
}

template<typename VecType>
bool VectorLessEqual(const VecType &a, const VecType &b) {
	for(int i = 0 ; i < VecType::Dimension ; i++) {
		if (a.value[i] <= b.value[i]) {
			return true;
		}
	}
	return false;
}
template<typename VecType>
bool VectorGreaterEqual(const VecType &a, const VecType &b) {
	for(int i = 0 ; i < VecType::Dimension ; i++) {
		if (a.value[i] >= b.value[i]) {
			return true;
		}
	}
	return false;
}
template<typename VecType>
bool VectorLess(const VecType &a, const VecType &b) {
	for(int i = 0 ; i < VecType::Dimension ; i++) {
		if (a.value[i] < b.value[i]) {
			return true;
		}
	}
	return false;
}
template<typename VecType>
bool VectorGreater(const VecType &a, const VecType &b) {
	for(int i = 0 ; i < VecType::Dimension ; i++) {
		if (a.value[i] > b.value[i]) {
			return true;
		}
	}
	return false;
}

template<typename VecType>
bool VectorNotEqual(const VecType &a, const VecType &b) {
	return !VectorEqual(a, b);
}

template<typename VecType>
VecType& VectorAddThis(VecType &a, const VecType &b) {
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		a.value[i] += b.value[i];
	}
	return a;
}

template<typename VecType>
VecType VectorAdd(const VecType &a, const VecType &b) {
	VecType tmp = a;
	VectorAddThis(tmp, b);
	return tmp;
}
template<typename VecType>
VecType& VectorSubtractThis(VecType &a, const VecType &b) {
	for (int i = 0 ; i < VecType::Dimension; i++) {
		a.value[i] -= b.value[i];
	}
	return a;
}
template<typename VecType>
VecType VectorSubtract(const VecType &a, const VecType &b) {
	VecType tmp = a;
	VectorSubtractThis(tmp, b);
	return tmp;
}
template<typename VecType>
VecType& VectorMultiplyThis(VecType &a, typename VecType::ElemType t) {
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		a.value[i] *= t;
	}
	return a;
}
template<typename VecType>
VecType VectorMultiply(const VecType &a, typename VecType::ElemType t) {
	VecType tmp = a;
	VectorMultiplyThis(tmp, t);
	return tmp;
}
template<typename VecType>
VecType& VectorDivideThis(VecType &a, typename VecType::ElemType t) {
	if (t == 0) {
		t = 1;
	}
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		a.value[i] /= t;
	}
	return a;
}
template<typename VecType>
VecType VectorDivide(const VecType &a, typename VecType::ElemType t) {
	VecType tmp = a;
	VectorDivideThis(tmp, t);
	return tmp;
}
template<typename VecType>
typename VecType::ElemType VectorLengthSquare(const VecType &a) {
	typename VecType::ElemType retval = 0;
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		retval += a.value[i] * a.value[i];
	}
	return retval;
}
template<typename VecType>
typename VecType::ElemType VectorLength(const VecType &a) {
	typename VecType::ElemType length_square = VectorLengthSquare(a);
	return sqrt(length_square);
}
template<typename VecType>
typename VecType::ElemType VectorDot(const VecType &a, const VecType &b) {
	typename VecType::ElemType retval = 0;
	for (int i = 0 ; i < VecType::Dimension ; i++) {
		retval += a.value[i] * b.value[i];
	}
	return retval;
}
template<typename VecType>
VecType &VectorNormalized(VecType &a) {
	typename VecType::ElemType length = VectorLength(a);
	return a /= length;
}
template<typename VecType>
VecType VectorNormalize(const VecType &a) {
	VecType tmp = a;
	VectorNormalized(tmp);
	return tmp;
}

template<typename T>
Vector3<T> VectorCross(const Vector3<T> &a, const Vector3<T> &b) {
	T x = a.y * b.z - a.z * b.y;
	T y = a.z * b.x - a.x * b.z;
	T z = a.x * b.y - a.y * b.x;
	return Vector3<T>(x, y, z);
}
template<typename VecType>
bool VectorIsZero(const VecType &v, typename VecType::ElemType error_range = 0.001) {
	return (error_range > VectorLengthSquare(v));
}

template<typename VecType>
void VectorSetZero(VecType &v) {
	for(int i = 0 ; i < VecType::Dimension ; i++) {
		v.value[i] = 0;
	}
}
}