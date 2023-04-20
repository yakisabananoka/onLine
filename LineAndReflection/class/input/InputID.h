#pragma once
#include <type_traits>

//ボタンの種類
enum class InputID
{
	UP,			//上
	DOWN,		//下
	LEFT,		//左
	RIGHT,		//右
	BTN1,		//ボタン設定1
	BTN2,		//ボタン設定2
	MAX
};

static InputID begin(InputID) { return InputID::UP; };
static InputID end(InputID) { return InputID::MAX; };
static InputID operator++(InputID& id) { return id = static_cast<InputID>(std::underlying_type<InputID>::type(id) + 1); };
static InputID operator*(const InputID& id) { return id; };
