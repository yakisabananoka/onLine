#pragma once
#include <memory>
#include <algorithm>
#include <cmath>
#include <string>
#include <DxLib.h>
#include "Vector2.h"
#include "TimeMng.h"
#include "shape/Capsule.h"
#include "shape/Circle.h"

//時間があるときにクラスに分割
namespace utility
{
	//値を範囲内にまとめる関数
	struct Clamp
	{
		double operator()(double value, double minVal = 0.0, double maxVal = 1.0)
		{
			return std::clamp(value, minVal, maxVal);
		}
	};

	//カプセルと円の当たり判定
	struct isHitCapCircle
	{
		bool operator()(const Capsule& cap, const Circle& cc)
		{
			Vector2Dbl vp = cc.pos - cap.posA;
			Vector2Dbl v = cap.posB - cap.posA;

			auto vDot = vp.Dot(v);
			auto vMag = v.Magnitude();

			v = v * Clamp()(vDot / (vMag * vMag));

			return (vp - v).Magnitude() < cap.radius + cc.radius;
		}
	};

	//反射ベクトルの導出
	struct VecReflection
	{
		Vector2Dbl operator()(Vector2Dbl vec, Vector2Dbl nVec)
		{
			nVec.Normalize();

			return vec + 2 * (-vec.Dot(nVec)) * nVec;
		}
	};

	//ラジアン値を0～2πに収める
	struct RadIn2PI
	{
		double operator()(double rad)
		{
			rad = fmod(rad, DX_TWO_PI);
			return rad < 0.0 ? rad + DX_TWO_PI : rad;
		}
	};

	//ラジアン値の差分を導出
	struct DiffRad
	{
		double operator()(double base, double target)
		{
			base = RadIn2PI()(base);
			target = RadIn2PI()(target);

			double ret = target - base;

			if (ret < 0.0)
			{
				ret = abs(ret) > DX_PI ? ret + DX_TWO_PI : ret;
			}
			else
			{
				ret = abs(ret) > DX_PI ? ret - DX_TWO_PI : ret;
			}

			return ret;
		}
	};

	//指定した秒数に一回trueを返す
	struct Timer
	{
		bool operator()(const double& cnt, double inv)
		{
			return (static_cast<int>((cnt + lpTimeMng.GetDeltaTime()) / inv) - static_cast<int>(cnt / inv));
		}
	};

	//std::string(UTF-8)からstd::string(Shift-JIS)に変換
	struct ConvertUTF8ToSJIS 
	{
		std::string operator()(std::string utf8Str)
		{
			std::wstring wstr;
			wstr.resize(MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), static_cast<int>(utf8Str.size()), NULL, 0));

			MultiByteToWideChar(CP_UTF8, 0, utf8Str.c_str(), static_cast<int>(utf8Str.size()), &wstr[0], static_cast<int>(wstr.size()));

			std::string sjisStr;
			sjisStr.resize(static_cast<size_t>(WideCharToMultiByte(CP_THREAD_ACP, 0, &wstr[0], -1, NULL, 0, NULL, NULL)) - 1);

			WideCharToMultiByte(CP_THREAD_ACP, 0, &wstr[0], static_cast<int>(wstr.size()), &sjisStr[0], static_cast<int>(sjisStr.size()), NULL, NULL);

			return sjisStr;
		}
	};

	//ラジアンから度に変換
	struct RadToDeg
	{
		double operator()(double rad)
		{
			return rad * 180.0 / DX_PI;
		}
	};

	//度からラジアンに変換
	struct DegToRad
	{
		double operator()(double deg)
		{
			return deg * DX_PI / 180.0;
		}
	};
}
