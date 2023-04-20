#include "../scene/SceneMng.h"
#include "../input/Controller.h"
#include "../scene/Camera.h"
#include "CameraInduction.h"

namespace cameraInduction_const
{
	constexpr int nullId = -1;
}

using namespace cameraInduction_const;

CameraInduction::CameraInduction(std::weak_ptr<Camera> camera, Vector2Dbl start, Vector2Dbl end, double moveTime, double waitTime, int parentID) :
	Obj(camera, start, nullId), start_(start), end_(end), moveTime_(moveTime), waitTime_(waitTime), parentID_(parentID)
{
	controller_ = lpSceneMng.GetController();
	controller_->SetAcitive(false);
	Init();
}

CameraInduction::~CameraInduction()
{
	controller_->SetAcitive(true);
}

void CameraInduction::Init(void)
{
	pos_ = defPos_;
	time_ = 0.0;
}

void CameraInduction::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (time_ < moveTime_)
	{
		Move(start_, end_, time_);
	}
	else if (time_ < moveTime_ + waitTime_)
	{
		//‘Ò‹@
	}
	else
	{
		if (!Move(end_, start_, time_ - moveTime_ - waitTime_))
		{
			for (auto& obj : objList)
			{
				if (obj->GetObjID() != parentID_)
				{
					continue;
				}

				if (camera_.expired())
				{
					break;
				}

				camera_.lock()->SetTarget(obj);
				activeFlg_ = false;
				break;
			}
		}
	}

	time_ += delta;
}

void CameraInduction::Draw(void)
{
}

bool CameraInduction::Move(const Vector2Dbl& start, const Vector2Dbl& end, double nowTime)
{
	pos_.x = easing_.OutExpo(nowTime, start.x, end.x - start.x, moveTime_);
	pos_.y = easing_.OutExpo(nowTime, start.y, end.y - start.y, moveTime_);

	return nowTime < moveTime_;
}
