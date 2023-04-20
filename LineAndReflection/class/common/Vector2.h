#pragma once
//template <class T> class �N���X�e���v���[�g��
template <class T> class Vector2Template
{
public:
	constexpr Vector2Template() :x(0), y(0) {};
	constexpr Vector2Template(T x, T y) :x(x), y(y) {};
	//~Vector2Template();

	T x;
	T y;

	constexpr T Magnitude(void)const;							//�x�N�g���̑傫�����擾
	constexpr T SQMagnitude(void)const;							//�x�N�g���̑傫���̓����擾

	void Normalize(void);										//�x�N�g���̐��K��

	constexpr Vector2Template Normalized(void)const;			//���K���ς݃x�N�g����Ԃ�(�����l�͕ύX�Ȃ�)

	constexpr Vector2Template RotaVec(double radangle)const;	//����(���W�A���l)����]
	constexpr Vector2Template RotaVec(float digangle)const;		//����(�x��)����]
	constexpr Vector2Template RotaVecRight90(void)const;		//�E���90�x
	constexpr Vector2Template RotaVecLeft90(void)const;			//�����90�x

	constexpr T Dot(const Vector2Template& vec)const;			//����
	constexpr T Cross(const Vector2Template& vec)const;			//�O��

	constexpr T Area(void)const;

	//������Z�q
	Vector2Template& operator=(const Vector2Template& vec);

	//�Y�����Z�q
	T& operator[](int num);

	//�P�����Z�q
	Vector2Template& operator+=(const Vector2Template& vec);
	Vector2Template& operator+=(const T& num);
	Vector2Template& operator-=(const Vector2Template& vec);
	Vector2Template& operator*=(const Vector2Template& vec);
	Vector2Template& operator/=(const Vector2Template& vec);
	Vector2Template& operator%=(const Vector2Template& vec);
	constexpr Vector2Template operator+()const;
	constexpr Vector2Template operator-()const;

	//�񍀉��Z�q
	constexpr Vector2Template operator+(Vector2Template vec)const;
	constexpr Vector2Template operator-(Vector2Template vec)const;
	constexpr Vector2Template operator*(Vector2Template vec)const;
	constexpr Vector2Template operator/(Vector2Template vec)const;
	constexpr Vector2Template operator%(Vector2Template vec)const;

	//��r���Z�q
	constexpr bool operator==(const Vector2Template& vec)const;
	constexpr bool operator!=(const Vector2Template& vec)const;
	constexpr bool operator<(const Vector2Template& vec)const;
	constexpr bool operator<=(const Vector2Template& vec)const;
	constexpr bool operator>(const Vector2Template& vec)const;
	constexpr bool operator>=(const Vector2Template& vec)const;

	//cast���Z�q
	constexpr operator Vector2Template<int>()const { return { static_cast<int>(this->x),static_cast<int>(this->y) }; };
	constexpr operator Vector2Template<float>()const { return { static_cast<float>(this->x),static_cast<float>(this->y) }; };
	constexpr operator Vector2Template<double>()const { return { static_cast<double>(this->x),static_cast<double>(this->y) }; };

};
template<class T> constexpr
Vector2Template<T> operator+(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator+(T num, Vector2Template<T> vec);

template<class T> constexpr
Vector2Template<T> operator-(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator-(T num, Vector2Template<T> vec);

template<class T> constexpr
Vector2Template<T> operator*(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator*(T num, Vector2Template<T> vec);

template<class T> constexpr
Vector2Template<T> operator/(Vector2Template<T> vec, T num);

template<class T> constexpr
Vector2Template<T> operator%(const Vector2Template<T>& vec, T num);

template<class T> constexpr
Vector2Template<T> RotaDig(const Vector2Template<T>& center,const Vector2Template<T>& pos, double dig);

template<class T> constexpr
Vector2Template<T> RotaRad(const Vector2Template<T>& center, const Vector2Template<T>& pos, double rad);

using Vector2 = Vector2Template<int>;
using Vector2Dbl = Vector2Template<double>;
using Vector2Flt = Vector2Template<float>;

using Position2 = Vector2Flt;
using Position2Dbl = Vector2Dbl;
#include "details/Vector2.h"
