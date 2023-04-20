#include <algorithm>
#include <DxLib.h>
#include "Gauge.h"
#include "GaugeCommand/GaugeCommand.h"

namespace gauge_const
{
}

using namespace gauge_const;

Gauge::Gauge(Rect rect, double thick, unsigned int color, unsigned edgeColor) :
	BaseUI(rect), thick_(thick), color_(color), edgeColor_(edgeColor)
{
	Init();
}

Gauge::~Gauge()
{
}

void Gauge::Init(void)
{
	value_ = 0.0;
}

void Gauge::Update(double delta)
{
	command_->Execute(*this);
}

void Gauge::Draw(void)
{
	if (!drawFlg_)
	{
		return;
	}

	DrawBoxAA(
		static_cast<float>(range_.GetLT().x), static_cast<float>(range_.GetLT().y),
		static_cast<float>(range_.GetRB().x), static_cast<float>(range_.GetRB().y),
		edgeColor_, true, static_cast<float>(thick_)
	);
	DrawBoxAA(
		static_cast<float>(range_.GetLT().x),
		static_cast<float>(range_.GetLT().y),
		static_cast<float>(range_.GetLT().x + range_.size.x * value_),
		static_cast<float>(range_.GetRB().y),
		color_, true
	);
}

void Gauge::SetCommand(std::unique_ptr<GaugeCommand> command)
{
	command_ = std::move(command);
}

void Gauge::SetValue(double value)
{
	value_ = std::clamp(value, 0.0, 1.0);
}

void Gauge::SetColor(unsigned int color)
{
	color_ = color;
}

void Gauge::SetCC(Vector2Dbl pos)
{
	range_.SetFixedCC(pos);
}

void Gauge::SetDrawFlg(bool flg)
{
	drawFlg_ = flg;
}
