#include <DxLib.h>
#include "KeyMouseInput.h"

KeyMouseInput::KeyMouseInput()
{
	Vector2 pos;
	GetMousePoint(&pos.x, &pos.y);
	pos_ = static_cast<Vector2Dbl>(pos);

	keyTbl_ = {
		{InputID::UP,KEY_INPUT_SPACE},
		{InputID::DOWN,KEY_INPUT_S},
		{InputID::LEFT,KEY_INPUT_A},
		{InputID::RIGHT,KEY_INPUT_D},
	};
	for (auto& tblData : keyTbl_)
	{
		cntData_.try_emplace(tblData.first, TrgBool{ 0,0 });
	}
	GetHitKeyStateAll(keyData_.data());

	mouseTbl_ = {
		{InputID::BTN1,MOUSE_INPUT_LEFT},
		{InputID::BTN2,MOUSE_INPUT_RIGHT}
	};
	for (auto& tblData : mouseTbl_)
	{
		cntData_.try_emplace(tblData.first, TrgBool{ 0,0 });
	}
	mouseData_ = GetMouseInput();
}

KeyMouseInput::~KeyMouseInput()
{
}

void KeyMouseInput::Update(void)
{
	for (auto& data : cntData_)
	{
		data.second[static_cast<int>(Trg::OLD)] = data.second[static_cast<int>(Trg::NOW)];
	}

	Vector2 pos;
	GetMousePoint(&pos.x, &pos.y);
	pos_ = static_cast<Vector2Dbl>(pos);

	rota_ = GetMouseWheelRotVol();

	GetHitKeyStateAll(keyData_.data());
	mouseData_ = GetMouseInput();

	for (auto& tblData : keyTbl_)
	{
		cntData_[tblData.first][static_cast<int>(Trg::NOW)] = keyData_[tblData.second] && activeFlg_;
	}
	for (auto& tblData : mouseTbl_)
	{
		cntData_[tblData.first][static_cast<int>(Trg::NOW)] = (mouseData_ & tblData.second) && activeFlg_;
	}
}

unsigned int KeyMouseInput::GetID(InputID inputId)const
{
	if (inputId == InputID::BTN1 || inputId == InputID::BTN2)
	{
		return mouseTbl_.at(inputId);
	}

	return keyTbl_.at(inputId);
}

void KeyMouseInput::SetID(InputID inputId, unsigned int keyId)
{
	if (inputId == InputID::BTN1 || inputId == InputID::BTN2)
	{
		mouseTbl_[inputId] = keyId;
		return;
	}

	keyTbl_[inputId] = keyId;
}
