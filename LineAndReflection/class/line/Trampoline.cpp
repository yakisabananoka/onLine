#include <algorithm>
#include "Trampoline.h"
#include "../obj/unit/Unit.h"
#include "../obj/Obj.h"
#include "../common/shape/Circle.h"
#include "../common/shape/Capsule.h"

namespace Trampoline_const
{
	constexpr int splitCnt = 3;
	constexpr double restPow = 1200.0;
	constexpr double refMag = 50.0;
	constexpr double minRefPow = 0.0;
	constexpr double maxRefPow = 3.0;
}

using namespace Trampoline_const;

Trampoline::Trampoline(std::weak_ptr<Camera> camera, unsigned int color) :
	BaseLine(camera, color)
{
}

Trampoline::~Trampoline()
{
}

bool Trampoline::SplitInit(void)
{
	nodeList_.clear();
	nodeList_.emplace_back(firstPos_, Node::State::COMPLETE, 0.0);
	nodeList_.emplace_back(endPos_, Node::State::COMPLETE, (endPos_ - firstPos_).Magnitude());
	SetPolygonAll();
	touchInfo_ = nullptr;
	return true;
}

void Trampoline::UpdateAfterObj(double delta, ObjList& objList)
{
	//時間外の場合は削除
	if (activeTime_ > GetMaxActiveTime())
	{
		state_ = State::DIE;
	}

	//描画中の場合は処理しない
	if (state_ == State::DRAWING)
	{
		return;
	}

	//カプセルの当たり判定
	auto checkHitCap = [](const Capsule& cap, const Circle& circle, Vector2Dbl& qPos) {
		auto tVec = circle.pos - cap.posA;
		auto capVec = cap.Vec();

		auto perQ = tVec.Dot(capVec) / capVec.SQMagnitude();
		perQ = std::clamp(perQ, 0.0, 1.0);

		qPos = capVec * perQ + cap.posA;

		double sqDist = (qPos - circle.pos).SQMagnitude();
		bool retFlg = (sqDist < pow(circle.radius + cap.radius, 2));					//厳しい判定用

		return retFlg;
	};

	//円の当たり判定
	auto checkHitCircle = [](const Circle& circleA, const Circle& circleB,Vector2Dbl& correctVec)
	{
		if (!circleA.CheckHit(circleB))
		{
			return false;
		}

		auto vec = (circleB.pos - circleA.pos);
		correctVec = vec.Normalized() * ((circleA.radius + circleB.radius) - vec.Magnitude());

		return true;
	};

	nodeList_.clear();

	if (touchInfo_)
	{
		//前に接触したObjの取得
		auto oldObjItr = std::find_if(objList.begin(), objList.end(),
			[&](const ObjPtr& objPtr)
			{
				if (!objPtr->IsUnit())
				{
					return false;
				}
				const auto& unit = dynamic_cast<const Unit&>(*objPtr);
				return (unit.GetObjID() == touchInfo_->objId) && (unit.GetState() != Unit::State::Death);
			}
		);

		if (oldObjItr == objList.end())
		{
			//Objが無効になっていた場合は接触情報を削除
			touchInfo_ = nullptr;
		}
	}

	for (auto& obj : objList)
	{
		//Unit以外は飛ばす
		if (!obj->IsUnit())
		{
			continue;
		}

		if (touchInfo_)
		{
			//前に接触したObjと違う場合は飛ばす
			if (touchInfo_->objId != obj->GetObjID())
			{
				continue;
			}
		}

		Unit& unit = dynamic_cast<Unit&>(*obj);

		//Unitが死亡していた場合はとばす
		if (unit.GetState() == Unit::State::Death)
		{
			continue;
		}

		if (!unit.IsTouchTrampoline())
		{
			continue;
		}

		auto circle = unit.GetColCircle();			//Unitの当たり判定取得
		circle.pos = unit.GetMovedPos(delta);

		Vector2Dbl correctVec;						//補正ベクトル

		//始点との補正
		Circle firstCircle(firstPos_, GetColRadius());
		if (checkHitCircle(firstCircle, circle, correctVec))
		{
			unit.AddCorrectVec(correctVec);
			circle.pos += correctVec;
		}

		//終点との補正
		Circle endCircle(endPos_, GetColRadius());
		if (checkHitCircle(endCircle, circle, correctVec))
		{
			unit.AddCorrectVec(correctVec);
			circle.pos += correctVec;
		}

		//トランポリンのトリガー
		Capsule cap(firstPos_, endPos_, GetColRadius());
		Vector2Dbl dirVec = cap.Vec();

		Vector2Dbl shortPos;

		//トリガーに接触しなかった場合
		if (!checkHitCap(cap, circle, shortPos))
		{
			if (touchInfo_)
			{
				//反射時
				if (cap.Vec().Cross(circle.pos - firstPos_) * (touchInfo_->dir) >= 0)
				{
					unit.AddMoveVec(GetRefVec(dirVec) * touchInfo_->inPow * refMag);
					SplitInit();
					break;
				}
			}
			else
			{
				SplitInit();
				continue;
			}

		}

		//初回接触時
		if (touchInfo_ == nullptr)
		{
			auto unitVec = unit.GetMovedPos(delta) - unit.GetPos();
			touchInfo_ = std::make_unique<TouchInfo>(
				unitVec.Normalized(),
				abs(dirVec.Normalized().Cross(unit.GetMovedPos(delta) - unit.GetPos())),
				cap.Vec().Cross(circle.pos - firstPos_),
				unit.GetObjID());

			//inPow_ = abs(dirVec.Normalized().Cross(unit.GetMovedPos(delta) - unit.GetPos()));
			//inPow_ = std::clamp(inPow_, minRefPow, maxRefPow);
		}
		
		Vector2Dbl firstTanPos = GetOneTanPnt(circle, firstPos_, dirVec);		//始点からの接点の取得
		Vector2Dbl endTanPos = GetOneTanPnt(circle, endPos_, dirVec);			//終点からの接点の取得

		nodeList_.emplace_back(firstPos_, Node::State::COMPLETE, 0.0);
		nodeList_.emplace_back(firstTanPos, Node::State::COMPLETE, (firstTanPos - nodeList_.back().pos).Magnitude());

		SetSplitHalfVec(circle, firstTanPos, endTanPos, splitCnt);

		nodeList_.emplace_back(endTanPos, Node::State::COMPLETE, (endTanPos - nodeList_.back().pos).Magnitude());
		nodeList_.emplace_back(endPos_, Node::State::COMPLETE, (endPos_ - nodeList_.back().pos).Magnitude());

		SetPolygonAll();

		unit.AddMoveVec(GetRefVec(dirVec) * restPow * delta);

		break;
	}

	UpdateLineScreen(delta);
	activeTime_ += delta;
	time_ += delta;
}

void Trampoline::SetPoint(Vector2Dbl pos)
{
	if (!CheckSetPoint(pos))
	{
		return;
	}

	if (nodeList_.empty())
	{
		nodeList_.emplace_back(pos, Node::State::COMPLETE, 0.0);
		nodeList_.emplace_back(pos, Node::State::COMPLETE, 0.0);

		return;
	}
	
	auto& lastNode = nodeList_.back();
	lastNode.pos = pos;
	lastNode.dist = (nodeList_.front().pos - pos).Magnitude();

}

void Trampoline::EndDrawingLine(void)
{
	if (nodeList_.size() < 2)
	{
		state_ = State::DIE;
		return;
	}

	nodeList_.back().state = Node::State::COMPLETE;
	state_ = State::STANDBY;

	firstPos_ = nodeList_.front().pos;
	endPos_ = nodeList_.back().pos;

	SetPolygonAll();
}

bool Trampoline::HasCollision(void)
{
	return false;
}

void Trampoline::SetSplitHalfVec(const Circle& circle, const Vector2Dbl& firstPos, const Vector2Dbl& secondPos, int cnt)
{
	if (cnt <= 0)
	{
		return;
	}
	cnt--;

	Vector2Dbl halfPos = ((firstPos - circle.pos) + (secondPos - circle.pos)).Normalized() * circle.radius + circle.pos;

	SetSplitHalfVec(circle, firstPos, halfPos, cnt);
	nodeList_.emplace_back(halfPos, Node::State::COMPLETE, (halfPos - nodeList_.back().pos).Magnitude());
	SetSplitHalfVec(circle, halfPos, secondPos, cnt);
}

Vector2Dbl Trampoline::GetOneTanPnt(const Circle& circle, const Vector2Dbl& point, const Vector2Dbl& dirVec) const
{
	auto pair = CalcTanPnt(circle, point);
	//_dbgDrawCircle(static_cast<int>(pair.first.x), static_cast<int>(pair.first.y), 2, 0x0000ff, true);
	//_dbgDrawCircle(static_cast<int>(pair.second.x), static_cast<int>(pair.second.y), 2, 0x0000ff, true);

	auto fCrs = dirVec.Cross(pair.first - firstPos_);
	auto eCrs = dirVec.Cross(pair.second - firstPos_);

	if ((fCrs * eCrs) < 0)
	{
		return fCrs * touchInfo_->dir < 0 ? pair.first : pair.second;
	}

	auto centerPos = (firstPos_ + endPos_) / 2.0;

	if ((fCrs * touchInfo_->dir) >= 0 && (eCrs * touchInfo_->dir) >= 0)
	{
		return (pair.first - centerPos).SQMagnitude() <= (pair.second - centerPos).SQMagnitude() ? pair.first : pair.second;
	}

	return (pair.first - centerPos).SQMagnitude() > (pair.second - centerPos).SQMagnitude() ? pair.first : pair.second;
}

std::pair<Vector2Dbl, Vector2Dbl> Trampoline::CalcTanPnt(const Circle& circle, const Vector2Dbl& point) const
{
	auto cpVec = circle.pos - point;
	auto cpDist = sqrt(cpVec.SQMagnitude() - pow(circle.radius, 2));

	cpVec.Normalize();

	cpVec = cpVec * cpDist;

	double theta = atan2(circle.radius, cpDist);

	return std::make_pair(cpVec.RotaVec(theta) + point, cpVec.RotaVec(-theta) + point);
}

Vector2Dbl Trampoline::GetRefVec(const Vector2Dbl& dirVec) const
{
	if (!touchInfo_)
	{
		return Vector2Dbl();
	}

	return (dirVec.Cross(dirVec.RotaVecLeft90()) * (touchInfo_->dir) >= 0.0 ? dirVec.RotaVecLeft90() : dirVec.RotaVecRight90()).Normalized();
}
