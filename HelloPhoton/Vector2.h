#pragma once

#include <math.h>

class Vector2
{
public:
	float x;
	float y;

	Vector2();
	Vector2(float x, float y);
	Vector2(const Vector2 & v);
	Vector2(const Vector2 * v);
	~Vector2();

	// assigning equality operators
	inline Vector2 operator = (const Vector2 & v) { x = v.x; y = v.y; return *this; }
	inline Vector2 operator = (const float & f) { x = f; y = f; return *this; }
	inline Vector2 operator - (void) { x = -x; y = -y; return *this; }
	inline bool operator == (const Vector2 & v) { return (x == v.x) && (y == v.y); }
	inline bool operator != (const Vector2 & v) { return (x != v.x) && (y != v.y); }
	inline bool operator > (const Vector2 & v) { return (x > v.x) && (y > v.y); }
	inline bool operator < (const Vector2 & v) { return (x < v.x) && (y < v.y); }
	inline bool operator >= (const Vector2 & v) { return (x >= v.x) && (y >= v.y); }
	inline bool operator <= (const Vector2 & v) { return (x <= v.x) && (y <= v.y); }

	// vector2 to vector2 operators
	inline const Vector2 operator + (const Vector2 & v) const { return Vector2(x + v.x, y + v.y); }
	inline const Vector2 operator - (const Vector2 & v) const { return Vector2(x - v.x, y - v.y); }
	inline const Vector2 operator * (const Vector2 & v) const { return Vector2(x * v.x, y * v.y); }
	inline const Vector2 operator / (const Vector2 & v) const { return Vector2(x / v.x, y / v.y); }

	// vector2 to this operators
	inline Vector2 & operator += (const Vector2 & v) { x += v.x; y += v.y; return *this; }
	inline Vector2 & operator -= (const Vector2 & v) { x -= v.x; y -= v.y; return *this; }
	inline Vector2 & operator *= (const Vector2 & v) { x *= v.x; y *= v.y; return *this; }
	inline Vector2 & operator /= (const Vector2 & v) { x /= v.x; y /= v.y; return *this; }

	// scalar to vector2 operators
	inline const Vector2 operator + (float f) const { return Vector2(x + f, y + f); }
	inline const Vector2 operator - (float f) const { return Vector2(x - f, y - f); }
	inline const Vector2 operator * (float f) const { return Vector2(x * f, y * f); }
	inline const Vector2 operator / (float f) const { return Vector2(x / f, y / f); }

	// scalar to this operators
	inline Vector2 & operator += (float f) { x += f; y += f; return *this; }
	inline Vector2 & operator -= (float f) { x -= f; y -= f; return *this; }
	inline Vector2 & operator *= (float f) { x *= f; y *= f; return *this; }
	inline Vector2 & operator /= (float f) { x /= f; y /= f; return *this; }
};