#include <DxLib.h>
#include "../scene/SceneMng.h"
#include "../stage/Stage.h"
#include "../line/LineCtrl.h"
#include "../line/BaseLine.h"
#include "LineHolder.h"
#include "../scene/Camera.h"
#include "../input/Controller.h"

namespace lineHolder_const
{
	constexpr double radius = 20.0;
}

using namespace lineHolder_const;

LineHolder::LineHolder(std::weak_ptr<Camera> camera, Vector2Dbl posA, Vector2Dbl posB, int id, std::string lineType) :
	Obj(camera, posA, id), lineType_(lineType), circleA_(posA, radius), circleB_(posB, radius), generator_(camera), controller_(lpSceneMng.GetController())
{
	Init();
}

LineHolder::~LineHolder()
{
}

void LineHolder::Init(void)
{
	line_ = nullptr;
}

void LineHolder::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (line_ != nullptr)
	{
		line_->Update(delta);

		Vector2Dbl camOffset;
		if (!camera_.expired())
		{
			camOffset = camera_.lock()->GetDrawOffset();
		}

		auto onWorldMousePos = controller_->GetPos() - camOffset;

		auto deleteLine = [&onWorldMousePos, &lineCtrl](const Circle& circle, LinePtr& line) {
			if ((line == nullptr) || (!circle.InShape(onWorldMousePos)))
			{
				return;
			}

			lineCtrl.CancelLastLine();
			line = nullptr;
		};

		if (!controller_->JustOn(InputID::BTN1))
		{
			return;
		}

		deleteLine(circleA_, line_);
		deleteLine(circleB_, line_);

		return;
	}

	auto getLine = [&](const Capsule& cap, LinePtr& line) {

		if (line == nullptr)
		{
			return false;
		}

		if (linkAction_.Act(*line,circleA_,circleB_))
		{
			line->SetActive(false);
			line_ = generator_.Generate(lineType_, 0xffffff);

			for (auto& node : line->GetNodeList())
			{
				line_->SetPoint(node.pos);
			}

			return true;
		}

		return false;
	};

	lineCtrl.GetLineInfoCap(getLine);
}

void LineHolder::Draw(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	unsigned int color = line_ ? 0x73a82d : 0xe94c4d;

	DrawCircleAA(static_cast<float>(camOffset.x + circleA_.pos.x), static_cast<float>(camOffset.y + circleA_.pos.y), static_cast<float>(radius), 36, color);
	DrawCircleAA(static_cast<float>(camOffset.x + circleB_.pos.x), static_cast<float>(camOffset.y + circleB_.pos.y), static_cast<float>(radius), 36, color);

	if (line_ == nullptr)
	{
		return;
	}

	line_->Draw();
}
