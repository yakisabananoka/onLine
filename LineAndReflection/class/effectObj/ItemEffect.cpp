#include "../scene/Camera.h"
#include "EffectObj.h"
#include "EffectInfo.h"
#include "effectCommand/FadeOut.h"
#include "ItemEffect.h"

namespace itemEffect_const
{
	namespace out
	{
		constexpr char key[] = "data/effect/Textures/nc202888.png";
		constexpr int genNum = 30;
		constexpr double lifeTime = 1.3;
		constexpr double fadeOutTime = 0.5;
		
		constexpr double ampMag = 120.0;
		constexpr Vector2Dbl vecX = Vector2Dbl(-1.0, 1.0) * ampMag;
		constexpr Vector2Dbl vecY = Vector2Dbl(-1.0, 1.0) * ampMag;

		constexpr double mag = 0.05;
	}
}

using namespace itemEffect_const;

ItemEffect::ItemEffect(std::weak_ptr<Camera> camera, Vector2Dbl pos) :
	camera_(camera), pos_(pos), randomGen_(seed_()),
	outVecXRange_(out::vecX.x, out::vecX.y), outVecYRange_(out::vecY.x, out::vecY.y)
{
	std::unique_ptr<EffectInfo> info;

	for (int i = 0; i < out::genNum; i++)
	{
		info = std::make_unique<EffectInfo>();

		info->imageKey = out::key;
		info->pos = pos_;
		info->vec = { outVecXRange_(randomGen_),outVecYRange_(randomGen_) };
		info->move.speed = 1.0;
		info->lifeTime = out::lifeTime;
		info->mag = out::mag;
		info->command = std::make_unique<FadeOut>(out::fadeOutTime);

		effList_.emplace_back(std::make_unique<EffectObj>(std::move(info)));
	}

	
}

ItemEffect::~ItemEffect()
{
}

void ItemEffect::Update(double delta)
{
	for (auto& effObj : effList_)
	{
		effObj->Update(delta);
	}

	auto itr = std::remove_if(effList_.begin(), effList_.end(), [](EffectPtr& ptr) {return !ptr->IsAlive(); });
	effList_.erase(itr, effList_.end());
}

void ItemEffect::Draw(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	for (auto& effObj : effList_)
	{
		effObj->Draw(camOffset);
	}
}

bool ItemEffect::IsEnd(void) const
{
	return effList_.size() <= 0;
}
