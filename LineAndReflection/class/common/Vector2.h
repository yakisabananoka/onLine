#pragma once
//template <class T> class クラステンプレート名
template <class T> class Vector2Template
{
public:
	constexpr Vector2Template() :x(0), y(0) {};
	constexpr Vector2Template(T x, T y) :x(x), y(y) {};
	//~Vector2Template();

	T x;
	T y;

	constexpr T Magnitude(void)const;							//ベクトルの大きさを取得
	constexpr T SQMagnitude(void)const;							//ベクトルの大きさの二乗を取得

	void Normalize(void);										//ベクトルの正規化

	constexpr Vector2Template Normalized(void)const;			//正規化済みベクトルを返す(内部値は変更なし)

	constexpr Vector2Template RotaVec(double radangle)const;	//引数(ラジアン値)分回転
	constexpr Vector2Template RotaVec(float digangle)const;		//引数(度数)分回転
	constexpr Vector2Template RotaVecRight90(void)const;		//右回り90度
	constexpr Vector2Template RotaVecLeft90(void)const;			//左回り90度

	constexpr T Dot(const Vector2Template& vec)const;			//内積
	constexpr T Cross(const Vector2Template& vec)const;			//外積

	constexpr T Area(void)const;

	//代入演算子
	Vector2Template& operator=(const Vector2Template& vec);

	//添字演算子
	T& operator[](int num);

	//単項演算子
	Vector2Template& operator+=(const Vector2Template& vec);
	Vector2Template& operator+=(const T& num);
	Vector2Template& operator-=(const Vector2Template& vec);
	Vector2Template& operator*=(const Vector2Template& vec);
	Vector2Template& operator/=(const Vector2Template& vec);
	Vector2Template& operator%=(const Vector2Template& vec);
	constexpr Vector2Template operator+()const;
	constexpr Vector2Template operator-()const;

	//二項演算子
	constexpr Vector2Template operator+(Vector2Template vec)const;
	constexpr Vector2Template operator-(Vector2Template vec)const;
	constexpr Vector2Template operator*(Vector2Template vec)const;
	constexpr Vector2Template operator/(Vector2Template vec)const;
	constexpr Vector2Template operator%(Vector2Template vec)const;

	//比較演算子
	constexpr bool operator==(const Vector2Template& vec)const;
	constexpr bool operator!=(const Vector2Template& vec)const;
	constexpr bool operator<(const Vector2Template& vec)const;
	constexpr bool operator<=(const Vector2Template& vec)const;
	constexpr bool operator>(const Vector2Template& vec)const;
	constexpr bool operator>=(const Vector2Template& vec)const;

	//cast演算子
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
