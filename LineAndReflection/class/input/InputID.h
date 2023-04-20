#pragma once
#include <type_traits>

//�{�^���̎��
enum class InputID
{
	UP,			//��
	DOWN,		//��
	LEFT,		//��
	RIGHT,		//�E
	BTN1,		//�{�^���ݒ�1
	BTN2,		//�{�^���ݒ�2
	MAX
};

static InputID begin(InputID) { return InputID::UP; };
static InputID end(InputID) { return InputID::MAX; };
static InputID operator++(InputID& id) { return id = static_cast<InputID>(std::underlying_type<InputID>::type(id) + 1); };
static InputID operator*(const InputID& id) { return id; };
