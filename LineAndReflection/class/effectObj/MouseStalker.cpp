#include <cassert>
#include "../scene/SceneMng.h"
#include "../common/TimeMng.h"
#include "../common/ImageMng.h"
#include "../input/Controller.h"
#include "EffectObj.h"
#include "effectCommand/FadeOut.h"
#include "MouseStalker.h"
#include "../common/Utility.h"

namespace ms_const
{
	constexpr double mag = 0.05;
	constexpr double mag_speed = -1.0;

	constexpr Vector2Dbl vec = Vector2Dbl{ 0.0,0.1 }*mag;
	constexpr Vector2Dbl vec_amp = Vector2Dbl{ 0.025,0.01 }*mag;
	constexpr Vector2Dbl vec_min = vec - vec_amp;
	constexpr Vector2Dbl vec_max = vec + vec_amp;

	constexpr double speed= 0000.0;

	constexpr double lifeTime = 0.6;

	constexpr double fadeOutTime = 0.7;

	constexpr int genNum = 5;

	constexpr double shiftAngle_amp = 15.0;
	constexpr double shiftAngle_min = -shiftAngle_amp;
	constexpr double shiftAngle_max = shiftAngle_amp;

	constexpr double blend = 255.0;
	constexpr double blend_speed = 255.0;

	constexpr char path[] = "data/image/eff_light.png";

	constexpr char imagePath[] = "data/image/wand.png";
	constexpr double imageRate = 0.05;

	constexpr Vector2Dbl imageOffset = { 10.0,10.0 };
}

using namespace ms_const;

MouseStalker::MouseStalker() :
	controller_(lpSceneMng.GetController()), randomGen_(seed_()),
	rangeVecX_(vec_min.x, vec_max.x), rangeVecY_(vec_min.y, vec_max.y),
	rangeShiftAngle_(shiftAngle_min, shiftAngle_max)
{
	lpImageMng.GetID(path);
	oldMousePos = controller_->GetPos();
	mousePos_ = oldMousePos;

	SetMouseDispFlag(false);
}

MouseStalker::~MouseStalker()
{
}

void MouseStalker::Update(void)
{
	 mousePos_ = controller_->GetPos();
	const double& delta = lpTimeMng.GetDeltaTime();

	for (auto& effObj : effList_)
	{
		effObj->Update(delta);
	}

	auto itr = std::remove_if(effList_.begin(), effList_.end(), [](EffectPtr& ptr) {return !ptr->IsAlive(); });
	effList_.erase(itr, effList_.end());

	double dist = (mousePos_ - oldMousePos).Magnitude();
	if (dist == 0.0)
	{
		return;
	}

	std::unique_ptr<EffectInfo> info;

	for (int i = 0; i < genNum; i++)
	{
		info = std::make_unique<EffectInfo>();

		info->imageKey = path;
		info->pos = (mousePos_ - oldMousePos).RotaVec(static_cast<float>(rangeShiftAngle_(randomGen_))) + oldMousePos;
		info->vec = { rangeVecX_(randomGen_),rangeVecY_(randomGen_) };
		info->move.speed = speed;
		info->lifeTime = lifeTime;
		info->mag = mag;
		info->command = std::make_unique<FadeOut>(fadeOutTime);
		//info.exAmount.speed = mag_speed;

		effList_.emplace_back(std::make_unique<EffectObj>(std::move(info)));
	}

	oldMousePos = mousePos_;
}

void MouseStalker::Draw(void)
{
	Vector2Dbl offset;
	for (auto& effObj : effList_)
	{
		effObj->Draw(offset);
	}

	DrawRotaGraph(
		static_cast<int>(imageOffset.x + mousePos_.x), static_cast<int>(imageOffset.y + mousePos_.y),
		imageRate, 0.0, lpImageMng.GetID(imagePath)[0], true
	);
}

