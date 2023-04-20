#include "..\Vector2.h"
#pragma once
#include <cmath>
constexpr double Vector2_PI = 3.14159265358979;

template<class T> constexpr
T Vector2Template<T>::Magnitude(void) const
{
	return static_cast<T>(hypot(x, y));
}

template<class T> constexpr
T Vector2Template<T>::SQMagnitude(void) const
{
	return x * x + y * y;
}

template<class T>
void Vector2Template<T>::Normalize(void)
{
	T mag = Magnitude();
	x /= mag;
	y /= mag;
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::Normalized(void)const
{
	T mag = Magnitude();
	return Vector2Template<T>(x / mag, y / mag);
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::RotaVec(double radangle)const
{
	return Vector2Template<T>(static_cast<T>(x * cos(radangle) - y * sin(radangle)), static_cast<T>(x * sin(radangle) + y * cos(radangle)));
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::RotaVec(float digangle)const
{
	double angle = digangle * Vector2_PI / 180;
	return Vector2Template<T>(static_cast<T>(x * cos(angle) - y * sin(angle)), static_cast<T>(x * sin(angle) + y * cos(angle)));
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::RotaVecRight90(void)const 
{
	return Vector2Template<T>(-this->y, this->x);
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::RotaVecLeft90(void)const
{
	return Vector2Template<T>(this->y, -this->x);
}

template<class T> constexpr
T Vector2Template<T>::Dot(const Vector2Template& vec)const
{
	return x * vec.x + y * vec.y;
}

template<class T> constexpr
T Vector2Template<T>::Cross(const Vector2Template& vec)const
{
	return x * vec.y - vec.x * y;
}

template<class T> constexpr 
T Vector2Template<T>::Area(void) const
{
	return x * y;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator=(const Vector2Template<T>& vec)
{
	x = vec.x;
	y = vec.y;
	return *this;
}

template<class T>
T& Vector2Template<T>::operator[](int num)
{
	switch (num)
	{
	case 0:
		return x;
		break;
	case 1:
		return y;
		break;
	default:
		return x;
		break;
	}
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const Vector2Template<T>& vec)
{
	x += vec.x;
	y += vec.y;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator+=(const T& num)
{
	x += num;
	y += num;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator-=(const Vector2Template<T>& vec)
{
	x -= vec.x;
	y -= vec.y;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator*=(const Vector2Template<T>& vec)
{
	x *= vec.x;
	y *= vec.y;
	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator/=(const Vector2Template<T>& vec)
{
	if (vec.x && vec.y)
	{
		x /= vec.x;
		y /= vec.y;
	}
	else if (!vec.x && !vec.y)
	{
		x = 0;
		y = 0;
	}
	else if (!vec.x)
	{
		x = 0;
		y /= vec.y;
	}
	else if (!vec.y)
	{
		x /= vec.x;
		y = 0;
	}

	return *this;
}

template<class T>
Vector2Template<T>& Vector2Template<T>::operator%=(const Vector2Template<T>& vec)
{
	if (vec.x && vec.y)
	{
		x %= vec.x;
		y %= vec.y;
	}
	else if (!vec.x && !vec.y)
	{
		x = 0;
		y = 0;
	}
	else if (!vec.x)
	{
		x = 0;
		y %= vec.y;
	}
	else if (!vec.y)
	{
		x %= vec.x;
		y = 0;
	}

	return *this;
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator+() const
{
	return *this;
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator-() const
{
	return { -x,-y };
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator+(Vector2Template<T> vec)const
{
	return Vector2Template<T>{ x + vec.x,y + vec.y };
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator-(Vector2Template<T> vec)const
{
	return Vector2Template<T>{ x - vec.x,y - vec.y };
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator*(Vector2Template<T> vec)const
{
	return Vector2Template<T>{ x * vec.x,y * vec.y };
}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator/(Vector2Template<T> vec)const
{
	if (vec.x && vec.y)
	{
		return Vector2Template<T>{ x / vec.x,y / vec.y };
	}
	else if (!vec.x && !vec.y)
	{
		return { 0,0 };
	}
	else if (!vec.x)
	{
		return { 0,y / vec.y };
	}
	else
	{
		return{ x / vec.x,0 };
	}

}

template<class T> constexpr
Vector2Template<T> Vector2Template<T>::operator%(Vector2Template<T> vec)const
{
	if (vec.x && vec.y)
	{
		return Vector2Template<T>{ x % vec.x,y % vec.y };
	}
	else if (!vec.x && !vec.y)
	{
		return { 0,0 };
	}
	else if (!vec.x)
	{
		return { 0,y % vec.y };
	}
	else
	{
		return{ x % vec.x,0 };
	}
}

template<class T> constexpr
bool Vector2Template<T>::operator==(const Vector2Template<T>& vec)const
{
	return ((x == vec.x) && (y == vec.y));
}

template<class T> constexpr
bool Vector2Template<T>::operator!=(const Vector2Template<T>& vec)const
{
	return !((x == vec.x) && (y == vec.y));
}

template<class T> constexpr
bool Vector2Template<T>::operator<(const Vector2Template<T>& vec)const
{
	return ((x < vec.x) && (y < vec.y));
}

template<class T> constexpr
bool Vector2Template<T>::operator<=(const Vector2Template<T>& vec)const
{
	return ((x <= vec.x) && (y <= vec.y));
}

template<class T> constexpr
bool Vector2Template<T>::operator>(const Vector2Template<T>& vec)const
{
	return ((x > vec.x) && (y > vec.y));
}

template<class T> constexpr
bool Vector2Template<T>::operator>=(const Vector2Template<T>& vec)const
{
	return ((x >= vec.x) && (y >= vec.y));
}

template<class T> constexpr
Vector2Template<T> operator+(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>(vec.x + num, vec.y + num);
}

template<class T> constexpr
Vector2Template<T> operator+(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>(vec.x + num, vec.y + num);
}

template<class T> constexpr
Vector2Template<T> operator-(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>(vec.x - num, vec.y - num);
}

template<class T> constexpr
Vector2Template<T> operator-(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>(vec.x - num, vec.y - num);
}

template<class T> constexpr
Vector2Template<T> operator*(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>{ vec.x * num,vec.y * num };
}

template<class T> constexpr
Vector2Template<T> operator*(T num, Vector2Template<T> vec)
{
	return Vector2Template<T>{ vec.x * num,vec.y * num };
}

template<class T> constexpr
Vector2Template<T> operator/(Vector2Template<T> vec, T num)
{
	return Vector2Template<T>{ vec.x/ num, vec.y/ num };
}

template<class T> constexpr
Vector2Template<T> operator%(const Vector2Template<T>& vec, T num)
{
	return Vector2Template<T>{ vec.x % num, vec.y % num };
}

template<class T> constexpr
Vector2Template<T> RotaDig(const Vector2Template<T>& center, const Vector2Template<T>& pos, double dig)
{
	Vector2Template<T> ret;
	auto dir = pos - center;
	auto rad = dig * Vector2_PI/ 180;
	ret.x = dir.x * cos(rad) - dir.y * sin(rad);
	ret.y = dir.y * cos(rad) + dir.x * sin(rad);
	ret = ret + center;
	return ret;
}

template<class T> constexpr
Vector2Template<T> RotaRad(const Vector2Template<T>& center, const Vector2Template<T>& pos, double rad)
{
	Vector2Template<T> ret;
	auto dir = pos - center;
	ret.x = dir.x * cos(rad) - dir.y * sin(rad);
	ret.y = dir.y * cos(rad) + dir.x * sin(rad);
	ret = ret + center;
	return ret;
}
