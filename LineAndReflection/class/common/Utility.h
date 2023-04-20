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

//���Ԃ�����Ƃ��ɃN���X�ɕ���
namespace utility
{
	//�l��͈͓��ɂ܂Ƃ߂�֐�
	struct Clamp
	{
		double operator()(double value, double minVal = 0.0, double maxVal = 1.0)
		{
			return std::clamp(value, minVal, maxVal);
		}
	};

	//�J�v�Z���Ɖ~�̓����蔻��
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

	//���˃x�N�g���̓��o
	struct VecReflection
	{
		Vector2Dbl operator()(Vector2Dbl vec, Vector2Dbl nVec)
		{
			nVec.Normalize();

			return vec + 2 * (-vec.Dot(nVec)) * nVec;
		}
	};

	//���W�A���l��0�`2�΂Ɏ��߂�
	struct RadIn2PI
	{
		double operator()(double rad)
		{
			rad = fmod(rad, DX_TWO_PI);
			return rad < 0.0 ? rad + DX_TWO_PI : rad;
		}
	};

	//���W�A���l�̍����𓱏o
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

	//�w�肵���b���Ɉ��true��Ԃ�
	struct Timer
	{
		bool operator()(const double& cnt, double inv)
		{
			return (static_cast<int>((cnt + lpTimeMng.GetDeltaTime()) / inv) - static_cast<int>(cnt / inv));
		}
	};

	//std::string(UTF-8)����std::string(Shift-JIS)�ɕϊ�
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

	//���W�A������x�ɕϊ�
	struct RadToDeg
	{
		double operator()(double rad)
		{
			return rad * 180.0 / DX_PI;
		}
	};

	//�x���烉�W�A���ɕϊ�
	struct DegToRad
	{
		double operator()(double deg)
		{
			return deg * DX_PI / 180.0;
		}
	};
}
