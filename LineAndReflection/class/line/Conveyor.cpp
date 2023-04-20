#include "Conveyor.h"
#include "../obj/Obj.h"
#include "../obj/unit/Unit.h"

namespace conveyor_const
{
	constexpr double sqCanSetDist = 20.0 * 20.0;
	constexpr double moveSpeed = 300.0;
}

using namespace conveyor_const;

Conveyor::Conveyor(std::weak_ptr<Camera> camera, unsigned int color) :
    BaseLine(camera, color)
{
}

Conveyor::~Conveyor()
{
}

void Conveyor::Update(double delta)
{
	colObjInfoVec_.clear();

	//ŽžŠÔŠO‚Ìê‡‚Ííœ
	if (activeTime_ > GetMaxActiveTime())
	{
		state_ = State::DIE;
	}

	if (state_ == State::DRAWING)
	{
		//SetPolygon(static_cast<float>(std::clamp(GetTotalLength() / GetMaxLength(), 0.0, 1.0)));
		SetPolygonAll();
	}
	else
	{
		activeTime_ += delta;
	}

	UpdateLineScreen(delta);

	time_ += delta;
}

void Conveyor::UpdateAfterObj(double delta, ObjList& objList)
{
	for (const auto& info : colObjInfoVec_)
	{
		for (auto& objPtr : objList)
		{
			if ((info->objId != objPtr->GetObjID()) || (!objPtr->IsUnit()))
			{
				continue;
			}

			auto& unit = dynamic_cast<Unit&>(*objPtr);

			Vector2Dbl vec = info->capsule.Vec().Normalized();
			unit.AddCorrectVec(vec * moveSpeed * delta);
			return;
		}
	}
}

void Conveyor::SetPoint(Vector2Dbl pos)
{
	if (!CheckSetPoint(pos))
	{
		return;
	}

	double sqDist = nodeList_.empty() ? 0.0 : (pos - nodeList_.back().pos).SQMagnitude();

	if (0.0 < sqDist && sqDist < sqCanSetDist)
	{
		return;
	}

	nodeList_.emplace_back(pos, Node::State::COMPLETE, sqrt(sqDist));
}

void Conveyor::EndDrawingLine(void)
{
	if (state_ != State::DRAWING)
	{
		return;
	}

	nodeList_.back().state = Node::State::COMPLETE;

	state_ = State::STANDBY;

	if (nodeList_.size() == 1)
	{
		state_ = State::DIE;
		return;
	}

	SetPolygonAll();
}

bool Conveyor::HasCollision(void)
{
    return true;
}
