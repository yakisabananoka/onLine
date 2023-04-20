#pragma once
#include <memory>
#include "../CorrectLine.h"
#include "../FreeLine.h"
#include "../Trampoline.h"
#include "../Conveyor.h"
#include "../usingLine.h"
#include "../../scene/Camera.h"

//線の生成用関数オブジェクト
namespace LineGenerators
{
	//補正線用
	struct CorrectLineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<CorrectLine>(camera, color);
		}
	};

	//自由線用
	struct FreeLineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<FreeLine>(camera, color);
		}
	};

	//トランポリン用
	struct TrampolineGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<Trampoline>(camera, color);
		}
	};

	//コンベア用
	struct ConveyorGenerator
	{
		LinePtr operator()(std::weak_ptr<Camera> camera, unsigned int color)
		{
			return std::make_unique<Conveyor>(camera, color);
		}
	};
}
