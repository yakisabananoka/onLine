#pragma once
#include <memory>
#include <DxLib.h>
#include "KeyMouseInput.h"

struct InputSelecter
{
	std::unique_ptr <Controller> operator()()
	{
		return std::make_unique<KeyMouseInput>();
	}

};
