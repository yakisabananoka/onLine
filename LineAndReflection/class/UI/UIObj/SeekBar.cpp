#include <algorithm>
#include <DxLib.h>
#include "../../scene/SceneMng.h"
#include "SeekBar.h"
#include "../../common/shape/Circle.h"
#include "../../common/shape/Capsule.h"

namespace seekBar_const
{
	constexpr double thick = 18.0;
	constexpr double edgeThick = thick + 4.0;
	
	constexpr double smallRadius = thick / 2.0;
	constexpr double radius = smallRadius * 2.0;

	constexpr unsigned int color = 0x797979;
	constexpr unsigned int fillColor = 0xffffff;
	constexpr unsigned int edgeColor = 0xc0c0c0;
	constexpr unsigned int circleColor = 0x4169e1;

	constexpr int posNum = 16;

}

using namespace seekBar_const;

SeekBar::SeekBar(Vector2Dbl firstPos, Vector2Dbl endPos) :
	BaseUI(Rect()), firstPos_(firstPos), endPos_(endPos)
{

	Init();
}

SeekBar::~SeekBar()
{
}

void SeekBar::Init(void)
{
	controller_ = lpSceneMng.GetController();
	flg_ = false;
}

void SeekBar::Update(double delta)
{
	if (controller_->NowOff(InputID::BTN1))
	{
		flg_ = false;
	}
	
	if (flg_)
	{
		ChangeValue(controller_->GetPos());
	}
	
	for (auto& callback : callbacks_)
	{
		callback(value_);
	}
}

void SeekBar::SpotUpdate(std::shared_ptr<Controller> controller)
{
	if (controller->JustOn(InputID::BTN1))
	{
		flg_ = true;
	}
}

void SeekBar::Draw(void)
{
	Vector2Dbl pos = firstPos_ + (endPos_ - firstPos_) * value_;

	DrawLineAA(
		static_cast<float>(firstPos_.x), static_cast<float>(firstPos_.y),
		static_cast<float>(endPos_.x), static_cast<float>(endPos_.y),
		edgeColor, static_cast<float>(edgeThick)
	);
	DrawLineAA(
		static_cast<float>(firstPos_.x), static_cast<float>(firstPos_.y),
		static_cast<float>(endPos_.x), static_cast<float>(endPos_.y),
		color, static_cast<float>(thick)
	);

	DrawLineAA(
		static_cast<float>(firstPos_.x), static_cast<float>(firstPos_.y),
		static_cast<float>(pos.x), static_cast<float>(pos.y),
		fillColor, static_cast<float>(thick)
	);

	DrawCircleAA(
		static_cast<float>(pos.x), static_cast<float>(pos.y),
		static_cast<float>(radius), posNum, circleColor, true
	);
	DrawCircleAA(
		static_cast<float>(pos.x), static_cast<float>(pos.y),
		static_cast<float>(smallRadius), posNum, fillColor, true
	);
}

bool SeekBar::IsIntoMousePos(const Vector2Dbl& mousePos)
{
	Vector2Dbl pos = firstPos_ + (endPos_ - firstPos_) * value_;

	bool flg = false;

	flg |= Circle(pos, radius).InShape(mousePos);
	flg |= Capsule(firstPos_, endPos_, thick).InShape(mousePos);

	return flg;
}

void SeekBar::SetUpdateCallback(SeekBarCallback func)
{
	callbacks_.emplace_back(func);
}

const double& SeekBar::GetValue(void) const
{
	return value_;
}

void SeekBar::SetValue(double value)
{
	value_ = value;
}

void SeekBar::ChangeValue(const Vector2Dbl& pos)
{
	auto vec = endPos_ - firstPos_;
	value_ = std::clamp((pos - firstPos_).Dot(vec) / vec.SQMagnitude(), 0.0, 1.0);
}
