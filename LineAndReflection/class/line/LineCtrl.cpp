#include "LineCtrl.h"
#include "../scene/SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/TimeMng.h"
#include "../scene/Camera.h"
#include "CorrectLine.h"
#include "FreeLine.h"
#include "Trampoline.h"
#include "Conveyor.h"
#include "generator/LineGenerator.h"
#include "../stage/Stage.h"
#include "../UI/UICtrl.h"
#include "../UI/UIObj/Gauge.h"
#include "../UI/UIObj/GaugeCommand/GaugeCommandFunc.h"
#include "../common/shape/Capsule.h"
#include "../../_debug/_debugConOut.h"

namespace lineCtrl_const
{
	namespace lineType
	{
		constexpr char free[] = "free";
		constexpr char trampoline[] = "trampoline";
		constexpr char conveyor[] = "conveyor";

		constexpr char key[] = "lineIcon";
		constexpr char path[] = "data/image/lineIcon.png";
		constexpr Vector2 divCnt = Vector2Dbl(3, 1);
		constexpr Vector2Dbl divSize = Vector2Dbl(512.0, 555.0);
		constexpr double mag = 0.2;
	}

	constexpr double drawTimeRate = 0.3;

	namespace gauges
	{
		constexpr Vector2Dbl size = Vector2Dbl(50.0, 10.0);
		constexpr Vector2Dbl offset = Vector2Dbl(0.0, -30.0);
	}
}

using namespace lineCtrl_const;

LineCtrl::LineCtrl(std::weak_ptr<Camera> camera, std::string genLineName) :
	camera_(camera), controller_(lpSceneMng.GetController()),genLineName_(genLineName)
{
	lpImageMng.GetID(lineType::path, lineType::key, lineType::divSize, lineType::divCnt);
	BaseLine::PreLoadLineScreen();
	generator_ = std::make_unique<LineGenerator>(camera);
	lineTypeList_[0] = lineType::free;
	lineTypeList_[1] = lineType::trampoline;
	lineTypeList_[2] = lineType::conveyor;
	Init();
}

LineCtrl::~LineCtrl()
{
}

void LineCtrl::Init(void)
{
	totalLineDist_ = 0.0;
	switchTime_ = 0.0;
	genLineNum_ = 0;
}

void LineCtrl::InitUI(UICtrl& uiCtrl)
{
	Rect rect = { Vector2Dbl(), gauges::size };
	auto gauge = std::make_unique<Gauge>(rect, 10.0, 0x00ff00, 0x000000);
	gauge->SetCommand(std::make_unique<GaugeCommandFunc>(
		[&](Gauge& gauge)
		{
			gauge.SetDrawFlg(false);
			if (!lineList_.size())
			{
				return;
			}

			const auto& line = lineList_.back();

			if (line == nullptr)
			{
				return;
			}

			if (line->GetState() != BaseLine::State::DRAWING)
			{
				return;
			}

			gauge.SetDrawFlg(true);
			double val = line->GetTotalLength() / line->GetMaxLength();
			val = (1.0 - std::clamp(val, 0.0, 1.0));
			unsigned int color = GetColor(
				static_cast<int>((1.0 - val) * 255.0),
				static_cast<int>(val * 255.0),
				0
			);
			auto pos = controller_->GetPos() + gauges::offset;

			gauge.SetValue(val);
			gauge.SetColor(color);
			gauge.SetCC(pos);
		}
		));
	uiCtrl.SetUI(std::move(gauge));
}

void LineCtrl::Update(double delta, const Stage& stage)
{
	switchTime_ -= delta;

	Vector2Dbl setOffset;
	if (!camera_.expired())
	{
		setOffset = -camera_.lock()->GetDrawOffset();
	}

	const auto& cntData = controller_->GetCntData();
	const auto& mousePos = controller_->GetPos();

	auto& wheel = controller_->GetRotate();
	if (wheel)
	{
		switchTime_ = 1.0;
		genLineNum_ += wheel;
		genLineNum_ %= 3;
		genLineNum_ += 3;
		genLineNum_ %= 3;
	}

	//左クリックした瞬間にLineを生成
	if (controller_->JustOn(InputID::BTN1))
	{
		TRACE("Line追加\n");
		lineList_.emplace_back(generator_->Generate(lineTypeList_[genLineNum_], stage.GetMapInfo().GetLineColor().GetColorCode()));
		lpTimeMng.SetTimeRate(drawTimeRate);
	}

	if (lineList_.empty())
	{
		return;
	}

	auto& lastLine = lineList_.back();

	//ヌルチェック
	if (lastLine == nullptr)
	{
		return;
	}

	if (lastLine->GetState() == BaseLine::State::DRAWING)
	{
		//左クリック中はマウスの座標にカメラオフセットを足したものを設置
		if (controller_->NowOn(InputID::BTN1))
		{
			lastLine->SetPoint(setOffset + mousePos);
		}

		//左クリックを離した瞬間に確定
		if (controller_->JustOff(InputID::BTN1) || lastLine->IsOverLength())
		{
			lastLine->EndDrawingLine();
			lpTimeMng.SetTimeRate(1.0);
			totalLineDist_ += lastLine->GetTotalLength();
		}
	}

	for (auto& line : lineList_)
	{
		if (line == nullptr)
		{
			continue;
		}

		line->Update(delta);
	}

	if (controller_->JustOn(InputID::BTN2))
	{
		lastLine = nullptr;
	}

	//時間切れであれば削除
	lineList_.remove_if([](LinePtr& line) {return line == nullptr; });
	lineList_.remove_if([](LinePtr& line) {return !line->IsActive(); });
}

void LineCtrl::UpdateAfterObj(double delta, ObjList& objList)
{
	for (auto& line : lineList_)
	{
		if (line == nullptr)
		{
			continue;
		}

		line->UpdateAfterObj(delta,objList);
	}
}

void LineCtrl::Draw(void)
{
	for (auto& line : lineList_)
	{
		if (line == nullptr)
		{
			continue;
		}

		line->Draw();
	}

	if (switchTime_ > 0.0)
	{
		auto pos = static_cast<Vector2>(controller_->GetPos());
		DrawRotaGraph(pos.x, pos.y - 32, lineType::mag, 0.0, lpImageMng.GetID(lineType::key)[genLineNum_], true);
	}
}

void LineCtrl::GetLineInfoCap(std::function<bool(const Capsule&, LinePtr&)> func)
{

	Capsule cap;
	for (auto& line : lineList_)
	{
		if (line == nullptr)
		{
			continue;
		}

		cap.radius = line->GetColRadius();

		const auto& nodeList = line->GetNodeList();
		auto nowItr = nodeList.begin();
		auto nextItr = std::find_if(std::next(nowItr, 1), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });

		while (nextItr != nodeList.end())
		{
			cap.posA = nowItr->pos;
			cap.posB = nextItr->pos;

			if (func(cap, line))
			{
				return;
			}

			nowItr = nextItr;
			nextItr = std::find_if(std::next(nowItr, 1), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
		}
	}

}

void LineCtrl::GetLineInfoNode(std::function<bool(const Node&, LinePtr&)> func)
{
	for (auto& line : lineList_)
	{
		if (line == nullptr)
		{
			continue;
		}

		const auto& nodeList = line->GetNodeList();

		for (const auto& node : nodeList)
		{
			if (func(node, line))
			{
				return;
			}
		}
	}
}

void LineCtrl::CancelLastLine(void)
{
	lineList_.back() = nullptr;
	lineList_.remove_if([](LinePtr& line) {return line == nullptr; });
}
