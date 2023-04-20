#include "FreeLine.h"

namespace freeLine_const
{
	constexpr double sqCanSetDist = 20.0 * 20.0;
	//constexpr double sqCanSetDist = 0.0 * 0.0;
}

using namespace freeLine_const;

FreeLine::FreeLine(std::weak_ptr<Camera> camera, unsigned int color):
	BaseLine(camera, color)
{
}

FreeLine::~FreeLine()
{
}

void FreeLine::Update(double delta)
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

void FreeLine::SetPoint(Vector2Dbl pos)
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

void FreeLine::EndDrawingLine(void)
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
