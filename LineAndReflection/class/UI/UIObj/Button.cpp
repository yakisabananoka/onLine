#include <sstream>
#include <DxLib.h>
#include "../../scene/SceneMng.h"
#include "../../common/ImageMng.h"
#include "../../input/Controller.h"
#include "Button.h"
#include "../../../_debug/_debugConOut.h"
#include "../../../_debug/_debugDispOut.h"

Button::Button(Vector2Dbl pos, const std::string& imageKey, bool alphaCheck) :
	BaseUI({ pos,static_cast<Vector2Dbl>(lpImageMng.GetSize(imageKey)) }),
	imageKey_(imageKey), alphaCheck_(alphaCheck)
{
	InitImage();
	Init();
}

Button::~Button()
{

}

void Button::Init(void)
{
	controller_ = lpSceneMng.GetController();
	oldEnterState_ = State::NowLeave;
}

void Button::Update(double delta)
{
	State state = IsIntoMousePos(controller_->GetPos()) ? State::NowEnter : State::NowLeave;
	if (commandMap_.count(state))
	{
		for (auto& command : commandMap_[state])
		{
			command->Execute(*this);
		}
	}

	if (state != oldEnterState_)
	{
		if (state == State::NowEnter)
		{
			for (auto& command : commandMap_[State::JustEnter])
			{
				command->Execute(*this);
			}
		}
		else
		{
			for (auto& command : commandMap_[State::JustLeave])
			{
				command->Execute(*this);
			}
		}
	}

	oldEnterState_ = state;
}

void Button::SpotUpdate(std::shared_ptr<Controller> controller)
{
	for (auto& commandListPair : commandMap_)
	{
		bool flg = false;

		switch (commandListPair.first)
		{
		case Button::State::JustOn:
			flg = controller_->JustOn(InputID::BTN1);
			break;
		case Button::State::JustOff:
			flg = controller_->JustOff(InputID::BTN1);
			break;
		case Button::State::NowOn:
			flg = controller_->NowOn(InputID::BTN1);
			break;
		case Button::State::NowOff:
			flg = controller_->NowOff(InputID::BTN1);
			break;
		default:
			break;
		}

		if (flg)
		{
			for (auto& command : commandListPair.second)
			{
				command->Execute(*this);
			}
		}
	}
}

void Button::Draw(void)
{
	DrawGraph(
		static_cast<int>(range_.pos.x),
		static_cast<int>(range_.pos.y),
		lpImageMng.GetID(imageKey_)[0], true
	);
}

bool Button::IsIntoMousePos(const Vector2Dbl& mousePos)
{
	if (!range_.InShape(mousePos))
	{
		return false;
	}

	if (!alphaCheck_)
	{
		return true;
	}

	Vector2 pos = static_cast<Vector2>(mousePos - range_.pos);

	int alpha;
	GetPixelSoftImage(lpImageMng.GetSoftID(imageKey_), pos.x, pos.y, NULL, NULL, NULL, &alpha);

	return alpha;
}

void Button::SetCommand(State state, ButtonCommandPtr command)
{
	commandMap_[state].emplace_back(std::move(command));
}

void Button::SetCC(Vector2Dbl pos)
{
	range_.SetFixedCC(pos);
}

void Button::SetImageKey(std::string imageKey)
{
	imageKey_ = imageKey;
	InitImage();
}

void Button::InitImage(void)
{
	lpImageMng.GetID(imageKey_);

	if (lpImageMng.ExistSoftID(imageKey_))
	{
		return;
	}

	Vector2 size = lpImageMng.GetSize(imageKey_);
	int gHandle = MakeScreen(size.x, size.y, true);

	SetDrawScreen(gHandle);

	SetDrawBlendMode(DX_BLENDMODE_SRCCOLOR, 255);
	DrawGraph(0, 0, lpImageMng.GetID(imageKey_)[0], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	int sHandle = MakeARGB8ColorSoftImage(size.x, size.y);
	GetDrawScreenSoftImage(0, 0, size.x, size.y, sHandle);

	lpImageMng.GetSoftID(imageKey_, sHandle);

	DeleteGraph(gHandle);
	
}
