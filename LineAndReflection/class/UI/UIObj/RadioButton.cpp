#include <sstream>
#include <DxLib.h>
#include "../../common/FontMng.h"
#include "RadioButton.h"
#include "Button.h"
#include "ButtonCommand/ButtonCommandFunc.h"
#include "../Panels.h"


namespace rButton_const
{
	constexpr double tickness = 5.0;
	constexpr double incVal = tickness * 2.0;

	constexpr unsigned int selectColor = 0xff0000;
}

using namespace rButton_const;

RadioButton::RadioButton(std::string fontKey):
	BaseUI(Rect()),fontKey_(fontKey)
{
}

RadioButton::~RadioButton()
{
}

void RadioButton::Init(void)
{
}

void RadioButton::Update(double delta)
{
	for (auto& info : infoMap_)
	{
		info.second->button->Update(delta);
	}
}

void RadioButton::SpotUpdate(std::shared_ptr<Controller> controller)
{
	infoMap_.at(nowSpotKey_)->button->SpotUpdate(controller);
}

void RadioButton::Draw(void)
{
	for (auto& info : infoMap_)
	{
		info.second->button->Draw();
	}

	auto& range = infoMap_[nowSelectKey_]->button->GetRange();
	Rect selectRange(range.GetCC(), range.size.x + incVal, range.size.y + incVal);

	DrawBoxAA(
		static_cast<float>(selectRange.GetLT().x), static_cast<float>(selectRange.GetLT().y),
		static_cast<float>(selectRange.GetRB().x), static_cast<float>(selectRange.GetRB().y),
		selectColor, false, tickness
	);
}

bool RadioButton::IsIntoMousePos(const Vector2Dbl& mousePos)
{
	bool ret = false;

	for (auto rItr = infoMap_.rbegin(); rItr != infoMap_.rend(); ++rItr)
	{
		if (rItr->second->button->IsIntoMousePos(mousePos))
		{
			ret = true;
			nowSpotKey_ = rItr->first;

			break;
		}
	}

	return ret;
}

void RadioButton::SetChildButton(std::string key, std::string text, Vector2Dbl pos, unsigned int color, unsigned int edgeColor)
{

	Rect range = {
		{},
		{static_cast<double>(GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(strlen(text.c_str())), lpFontMng.GetID(fontKey_))),
		static_cast<double>(GetFontSizeToHandle(lpFontMng.GetID(fontKey_)))}
	};

	std::stringstream bgImageKeySS;
	bgImageKeySS << range.size.x << "_" << range.size.y << "_alpha";
	std::string bgImageKey = bgImageKeySS.str();
	if (!lpImageMng.ExistID(bgImageKey))
	{
		lpImageMng.GetID(bgImageKey, MakeScreen(static_cast<int>(range.size.x), static_cast<int>(range.size.y), true));
	}

	std::stringstream bgImageKeyWhiteSS;
	bgImageKeyWhiteSS << range.size.x << "_" << range.size.y << "_alpha";
	std::string bgImageKeyWhite = bgImageKeyWhiteSS.str();
	if (!lpImageMng.ExistID(bgImageKeyWhite))
	{
		lpImageMng.GetID(bgImageKeyWhite, MakeScreen(static_cast<int>(range.size.x), static_cast<int>(range.size.y), true));
		SetDrawScreen(lpImageMng.GetID(bgImageKeyWhite)[0]);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, static_cast<int>(range.size.x), static_cast<int>(range.size.y), 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	auto buttonPtr = std::make_unique<Button>(pos, TextOnGraphPanel()(text, bgImageKey, fontKey_, color, edgeColor), false);
	buttonPtr->SetCommand(
		Button::State::NowEnter,
		std::make_unique<ButtonCommandFunc>([=](Button& button) { button.SetImageKey(TextOnGraphPanel()(text, bgImageKey, fontKey_, color, edgeColor)); })
	);
	buttonPtr->SetCommand(
		Button::State::NowLeave,
		std::make_unique<ButtonCommandFunc>([=](Button& button) { button.SetImageKey(TextOnGraphPanel()(text, bgImageKeyWhite, fontKey_, color, edgeColor)); })
	);
	buttonPtr->SetCommand(
		Button::State::NowOn,
		std::make_unique<ButtonCommandFunc>([&, key](Button& button) { nowSelectKey_ = key; })
	);

	infoMap_[key] = std::make_unique<RadioButtonInfo>(true, std::move(buttonPtr));

	nowSelectKey_ = infoMap_.begin()->first;
}

void RadioButton::SetChildButton(std::string key, std::string text, double cX, double cY, unsigned int color, unsigned int edgeColor)
{
	Rect range = {
		{},
		{static_cast<double>(GetDrawStringWidthToHandle(text.c_str(), static_cast<int>(strlen(text.c_str())), lpFontMng.GetID(fontKey_))),
		static_cast<double>(GetFontSizeToHandle(lpFontMng.GetID(fontKey_)))}
	};

	std::stringstream bgImageKeySS;
	bgImageKeySS << range.size.x << "_" << range.size.y << "_alpha";
	std::string bgImageKey = bgImageKeySS.str();
	if (!lpImageMng.ExistID(bgImageKey))
	{
		lpImageMng.GetID(bgImageKey, MakeScreen(static_cast<int>(range.size.x), static_cast<int>(range.size.y), true));
	}

	std::stringstream bgImageKeyWhiteSS;
	bgImageKeyWhiteSS << range.size.x << "_" << range.size.y << "_alpha";
	std::string bgImageKeyWhite = bgImageKeyWhiteSS.str();
	if (!lpImageMng.ExistID(bgImageKeyWhite))
	{
		lpImageMng.GetID(bgImageKeyWhite, MakeScreen(static_cast<int>(range.size.x), static_cast<int>(range.size.y), true));
		SetDrawScreen(lpImageMng.GetID(bgImageKeyWhite)[0]);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0, 0, static_cast<int>(range.size.x), static_cast<int>(range.size.y), 0xffffff, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	auto buttonPtr = std::make_unique<Button>(Vector2Dbl(), TextOnGraphPanel()(text, bgImageKey, fontKey_, color, edgeColor), false);
	buttonPtr->SetCC({ cX,cY });
	buttonPtr->SetCommand(
		Button::State::NowEnter,
		std::make_unique<ButtonCommandFunc>([=](Button& button) { button.SetImageKey(TextOnGraphPanel()(text, bgImageKey, fontKey_, color, edgeColor)); })
	);
	buttonPtr->SetCommand(
		Button::State::NowLeave,
		std::make_unique<ButtonCommandFunc>([=](Button& button) { button.SetImageKey(TextOnGraphPanel()(text, bgImageKeyWhite, fontKey_, color, edgeColor)); })
	);
	buttonPtr->SetCommand(
		Button::State::NowOn,
		std::make_unique<ButtonCommandFunc>([&, key](Button& button) { nowSelectKey_ = key; })
	);

	infoMap_[key] = std::make_unique<RadioButtonInfo>(true, std::move(buttonPtr));

}

void RadioButton::SetSelectKey(std::string key)
{
	nowSelectKey_ = key;
}

const std::string& RadioButton::GetNowSelectKey(void) const
{
	return nowSelectKey_;
}
