#pragma once
#include <memory>
#include "../CorrectLine.h"
#include "../FreeLine.h"
#include "../Trampoline.h"
#include "../Conveyor.h"
#include "../usingLine.h"
#include "../../scene/Camera.h"

//���̐����p�֐��I�u�W�F�N�g
namespace LineGenerators
{
	//�␳���p
	struct CorrectLineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<CorrectLine>(camera, color);
		}
	};

	//���R���p
	struct FreeLineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<FreeLine>(camera, color);
		}
	};

	//�g�����|�����p
	struct TrampolineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<Trampoline>(camera, color);
		}
	};

	//�R���x�A�p
	struct ConveyorGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<Conveyor>(camera, color);
		}
	};
}
