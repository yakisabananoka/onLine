#include <algorithm>
#include "SceneMng.h"
#include "Camera.h"
#include "SceneMng.h"
#include "../stage/Stage.h"
#include "../obj/Obj.h"
#include "../../_debug/_DebugDispOut.h"

namespace camera_const
{
	constexpr double minShake = -1.0;
	constexpr double maxShake = 1.0;
}

using namespace camera_const;

Camera::Camera() :
	randomGen_(seed_()), shakeRange_(minShake, maxShake)
{
	Init();
}

Camera::~Camera()
{
}

void Camera::Update(double delta)
{
	Vector2Dbl pos = pos_;
	if (!target_.expired())
	{
		pos = target_.lock()->GetPos();
	}

	Vector2Dbl shake;
	if (shakeTime_)
	{
		auto& sTime = (*shakeTime_);
		shake = Vector2Dbl(shakeRange_(randomGen_), shakeRange_(randomGen_)) * shakeMag_;
		sTime -= delta;
		if (sTime < 0.0)
		{
			shakeMag_ = 0.0;
			shakeTime_ = nullptr;
		}
	}

	SetPos(pos);
	pos_ += shake;
}

void Camera::Draw(void)
{
	//auto offset = lpSceneMng.drawOffset_ - GetDrawOffset();
	//_dbgDrawBox(pos_.x + offset.x, pos_.y + offset.y, pos_.x + lpMapCtl.chipSize_.x + offset.x, pos_.y + lpMapCtl.chipSize_.y + offset.y, 0x00ff00, true);
}

const Vector2Dbl& Camera::GetPos(void)const
{
	return pos_;
}

void Camera::SetPos(Vector2Dbl pos)
{
	pos_.x = std::clamp(pos.x, antiMoveRect.Left(), antiMoveRect.Right());
	pos_.y = std::clamp(pos.y, antiMoveRect.Top(), antiMoveRect.Bottom());
}

Vector2Dbl Camera::GetDrawOffset(void)const
{
	return defPos_ - pos_;
}

bool Camera::SetStageAndTarget(std::weak_ptr<Stage> stage, std::weak_ptr<Obj> target)
{
	//ステージを先に設定
	stage_ = stage;

	//ターゲット設定
	target_ = target;

	if (target_.expired())
	{
		return false;
	}

	InitArea();

	SetPos(target_.lock()->GetPos());

	return true;
}

bool Camera::SetTarget(std::weak_ptr<Obj> target)
{
	target_ = target;

	if (target_.expired())
	{
		return false;
	}

	target_ = target;
	SetPos(target_.lock()->GetPos());

	return true;
}

void Camera::SetShake(double time, double mag)
{
	shakeTime_ = std::make_unique<double>(time);
	shakeMag_ = mag;
}

bool Camera::IsShake(void) const
{
	return shakeTime_.operator bool();
}

bool Camera::Init(void)
{
	antiMoveRect = Rect();
	return true;
}

bool Camera::InitArea(void)
{
	if (stage_.expired())
	{
		return false;
	}

	const auto& mapInfo = stage_.lock()->GetMapInfo();
	const auto& viewArea = mapInfo.GetViewArea();
	const auto& tileSize = mapInfo.GetTileSize();

	Vector2Dbl tmpPos = static_cast<Vector2Dbl>((viewArea / 2) * tileSize);
	Vector2Dbl tmpPos2 = static_cast<Vector2Dbl>((mapInfo.GetWorldArea() - ((viewArea / 2) + (viewArea % 2))) * tileSize);

	//移動不可能領域の設定
	antiMoveRect.SetLeft(tmpPos.x);
	antiMoveRect.SetTop(tmpPos.y);
	antiMoveRect.SetRight(tmpPos2.x);
	antiMoveRect.SetBottom(tmpPos2.y);

	defPos_ = { antiMoveRect.Left(),antiMoveRect.Top() };

	return true;
}

