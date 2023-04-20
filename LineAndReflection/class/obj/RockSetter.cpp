#include "../scene/SceneMng.h"
#include "RockSetter.h"
#include "unit/Player.h"
#include "unit/Rock.h"
#include "../common/Utility.h"

namespace rockSetter_const
{
	constexpr Vector2Dbl offset = Vector2Dbl(0.0, -64.0);
	constexpr int genId = -1;
}

using namespace rockSetter_const;

RockSetter::RockSetter(std::weak_ptr<Camera> camera, Vector2Dbl pos, double minX, double maxX, double genTime, int id) :
	Obj(camera, pos, id), range_(minX, maxX), genTime_(genTime)
{
	std::random_device seed;
	randomGen_.seed(seed());
	time_ = 0.0;
	
	offset_ += offset + Vector2Dbl(0.0, static_cast<double>(-lpSceneMng.GetWindowSize().y) / 2.0);
}

RockSetter::~RockSetter()
{
}

void RockSetter::Init(void)
{
}

void RockSetter::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	time_ += delta;
	if (!utility::Timer()(time_, genTime_))
	{
		return;
	}

	for (const auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		pos_ = offset_ + obj->GetPos();
	}

	pos_.x = range_(randomGen_);
	objList.emplace_back(std::make_unique<Rock>(camera_, pos_, genId));
}

void RockSetter::Draw(void)
{
}
