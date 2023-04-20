#include <algorithm>
#include "../../scene/SceneMng.h"
#include "../../scene/Camera.h"
#include "../../stage/Stage.h"
#include "../../line/LineCtrl.h"
#include "../../line/BaseLine.h"
#include "Unit.h"
#include "../../collision/Collision.h"
#include "../../common/shape/Capsule.h"
#include "../../common/shape/Circle.h"

namespace unit_const
{
	constexpr double slipDegThreshould = 60.0;
	constexpr double slipRadThreshould = slipDegThreshould * DX_PI / 180.0;
}

using namespace unit_const;

Unit::Unit(std::weak_ptr<Camera> camera, const Vector2Dbl& pos, const double& radius, const int& id, const double& gravity, const double& maxSpeed, int lifePnt) :
	Obj(camera, pos, id), wallRayMaxVec_(radius / sin(slipRadThreshould), 0.0), groundRayMaxVec_(0.0, radius / cos(slipRadThreshould)),
	gravity_(gravity), maxSpeed_(maxSpeed), colCircle_(pos, radius), defLifePnt_(lifePnt)
{
	Init();
}

Unit::~Unit()
{
}

void Unit::Init(void)
{
	jumpFlg_ = false;
	moveVec_ = {};
	correctVec_ = {};
	nextMoveVec_ = {};
	pos_ = defPos_;
	intoLineCnt_ = 0;
	state_ = State::InAir;
	stateOld_ = state_;
	time_ = 0.0;
	stateTime_ = 0.0;
	lifePnt_ = defLifePnt_;
}

void Unit::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	time_ += delta;
	stateTime_ += delta;
	if (invicibleTime_)
	{
		auto& inviTime = (*invicibleTime_);
		inviTime -= delta;
		if (inviTime <= 0.0)
		{
			invicibleTime_ = nullptr;
		}
	}

	if (state_ == State::Death)
	{
		if (DeathMotion(delta, objList, lineCtrl, stage))
		{
			return;
		}
	}

	if (state_ == State::Damaged)
	{
		if (DamagedMotion(delta, objList, lineCtrl, stage))
		{
			return;
		}
	}

	InitBeforeMove(delta, objList, lineCtrl, stage);

	if (Motion(delta, objList, lineCtrl, stage))
	{
		return;
	}

	CorrectMove(delta, objList, lineCtrl, stage);
}

void Unit::ConfirmUpdate(double delta, const Stage& stage)
{
	pos_ += moveVec_ * delta + correctVec_;
	CorrectPos(stage);
}

bool Unit::DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	activeFlg_ = false;
	return true;
}

bool Unit::DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	SetState(State::InAir);
	return false;
}

const Unit::State& Unit::GetState(void) const
{
	return state_;
}

void Unit::SetState(State state)
{
	if (state_ == state)
	{
		return;
	}
	stateTime_ = 0.0;
	state_ = state;
}

const Circle& Unit::GetColCircle(void) const
{
	return colCircle_;
}

void Unit::AddMoveVec(Vector2Dbl vec)
{
	moveVec_ += vec;
}

void Unit::AddCorrectVec(Vector2Dbl vec)
{
	correctVec_ += vec;
}

Vector2Dbl Unit::GetMovedPos(double delta)
{
	return pos_ + moveVec_ * delta + correctVec_;
}

void Unit::AddDamagedPnt(int pnt, const Vector2Dbl& pos)
{
	if (invicibleTime_)
	{
		return;
	}

	lifePnt_ += pnt;
	damagedPos_ = std::make_unique<Vector2Dbl>(pos);

	State state = State::Damaged;
	if (lifePnt_ <= 0)
	{
		state = State::Death;
	}

	SetState(state);
}

void Unit::SetInvincible(double time)
{
	invicibleTime_ = std::make_unique<double>(time);
}

void Unit::InitBeforeMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	intoLineCnt_ = 0;
	colCircle_.pos = pos_;

	const auto& mapiInfo = stage.GetMapInfo();
	const auto& colList = mapiInfo.GetColLsit();

	double moveGravity = gravity_ * delta;

	correctVec_ = {};
	jumpFlg_ = false;

	stateOld_ = state_;

	switch (state_)
	{
	case Unit::State::TouchCeiling:
		moveVec_.y = (moveVec_.y < 0.0) ? 0.0 : moveVec_.y;
		break;
	case Unit::State::TouchFloor:
		moveVec_.y = 0.0;
		jumpFlg_ = true;
		break;
	case Unit::State::Sandwiched:
		moveVec_.y = 0.0;
		break;
	case Unit::State::InAir:
		break;
	case Unit::State::Death:
		break;
	default:
		break;
	}


	//移動ベクトルの初期化
	moveVec_.x = 0.0;
	moveVec_.y += moveGravity;
}

void Unit::CorrectMove(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	//異常なベクトルを丸める
	if (moveVec_ != Vector2Dbl())
	{
		double vecMag = moveVec_.Magnitude();
		vecMag = std::min(vecMag, maxSpeed_);
		moveVec_ = moveVec_.Normalized() * vecMag;
	}

	const auto& mapiInfo = stage.GetMapInfo();
	const auto& colList = mapiInfo.GetColLsit();

	//ステージとの当たり判定と補正
	Vector2Dbl move = moveVec_ * delta;

	Vector2Dbl lineCorrect = CheckMove(lineCtrl, intoLineCnt_, move);
	if (intoLineCnt_ > 4)
	{
		lineCorrect = {};
	}
	Vector2Dbl objCorrect = CheckMove(objList, move + lineCorrect);
	Vector2Dbl colCorrect = CheckMove(colList, move + lineCorrect + objCorrect);

	Vector2Dbl correctVec = lineCorrect + objCorrect + colCorrect;

	SetState(UpdateState(lineCtrl, colCorrect, objCorrect, lineCorrect));

	if (state_ == State::Sandwiched)
	{
		correctVec = {};
	}

	//跳ねる処理
	//if (boundCoeff_ != nullptr && boundThre_ != nullptr)
	//{
	//	if ((state_ != State::TouchFloor) &&
	//		(correctVec.y < 0.0) &&
	//		(moveVec_.SQMagnitude() > pow(*boundCoeff_, 2)))
	//	{
	//		moveVec_.y -= (*boundCoeff_);
	//	}
	//}

	correctVec_ += correctVec;

}

void Unit::CorrectPos(const Stage& stage)
{
	const auto& mapInfo = stage.GetMapInfo();

	//エリア外に出るのを防ぐ
	const auto& worldArea = mapInfo.GetWorldArea();
	const auto& worldSize = static_cast<Vector2Dbl>(worldArea * mapInfo.GetTileSize());
	pos_.x = std::clamp(pos_.x, colCircle_.radius, worldSize.x - colCircle_.radius);
	pos_.y = pos_.y < colCircle_.radius ? colCircle_.radius : pos_.y;

	if (pos_.y > worldSize.y)
	{
		AddDamagedPnt(-defLifePnt_, pos_);
		//SetState(State::Death);
	}
	if (pos_.y == colCircle_.radius)
	{
		moveVec_.y = 0.0;
	}
}

Vector2Dbl Unit::CheckMove(const ColPtr& col, Vector2Dbl moveVec)const
{
	Rect range;
	range.size = static_cast<Vector2Dbl>(lpSceneMng.GetWindowSize());
	range.SetFixedCC(pos_);

	if (!col->GetColRect().CheckHit(range))
	{
		return Vector2Dbl();
	}

	//auto pos = pos_ + moveVec;

	//線と円が当たっているかを判定
	auto checkHitLine = [&](Line line, Vector2Dbl pos) {
		auto tVec = pos - line.p;
		auto lVec = line.vec();
		auto nLVec = lVec.Normalized();

		auto perQ = tVec.Dot(lVec) / lVec.SQMagnitude();
		perQ = std::clamp(perQ, 0.0, 1.0);

		auto qPos = lVec * perQ + line.p;

		bool retFlg = (qPos - pos).SQMagnitude() < pow(colCircle_.radius, 2);

		return std::make_pair(retFlg, qPos);
	};

	//線と円が当たっていたら線の法線ベクトル方向に補正
	auto checkHitCol = [&](const ColPtr& col) {

		auto lineNum = col->GetLineNum();
		Vector2Dbl correctVec;

		for (int i = 0; i < lineNum; i++)
		{
			auto pos = pos_ + moveVec + correctVec;
			auto line = col->GetLine(i);
			auto hitPair = checkHitLine(line, pos);

			if (!hitPair.first)
			{
				continue;
			}

			auto nVec = line.vec().RotaVecLeft90().Normalized();
			auto mag = colCircle_.radius - (hitPair.second - pos).Magnitude();

			correctVec += nVec * mag;
		}

		return std::make_pair(correctVec != Vector2Dbl(), correctVec);
	};

	auto hitPair = checkHitCol(col);
	if (hitPair.first)
	{
		return hitPair.second;
	}

	return Vector2Dbl();
}

Vector2Dbl Unit::CheckMove(const ColPtrList& colList, Vector2Dbl moveVec)const
{
	//補正値を加算
	Vector2Dbl retVec;
	for (const auto& col : colList)
	{
		retVec += CheckMove(col, moveVec + retVec);
	}

	return retVec;

}

Vector2Dbl Unit::CheckMove(const ObjList& objList, Vector2Dbl moveVec)const
{
	Vector2Dbl ret;

	for (const auto& obj : objList)
	{
		const auto& col = obj->GetColPtr();
		if (col == nullptr)
		{
			continue;
		}

		ret += CheckMove(col, moveVec + ret);
	}

	return ret;
}

Vector2Dbl Unit::CheckMove(LineCtrl& lineCtrl, int& intoLineCnt, Vector2Dbl moveVec)const
{
	Vector2Dbl ret;
	auto pos = pos_ + moveVec;

	auto checkHitCap = [&](const Capsule& cap) {
		auto tVec = pos - cap.posA;
		auto capVec = cap.Vec();
		auto nLVec = capVec.Normalized();

		auto perQ = tVec.Dot(capVec) / capVec.SQMagnitude();
		perQ = std::clamp(perQ, 0.0, 1.0);

		auto qPos = capVec * perQ + cap.posA;

		double sqDist = (qPos - pos).SQMagnitude();
		//bool retFlg = (pow(cap.radius, 2) < sqDist) && (sqDist < pow(size + cap.radius, 2));									//易しい判定用
		bool retFlg = (pow(colCircle_.radius, 2) < sqDist) && (sqDist < pow(colCircle_.radius + cap.radius, 2));				//厳しい判定用

		return std::make_pair(retFlg, qPos);
	};

	auto correctHitCap = [&](const Capsule& cap, LinePtr& line) {
		if (!line->HasCollision())
		{
			return false;
		}

		auto hitPair = checkHitCap(cap);
		if (hitPair.first)
		{
			Vector2 capPosVec = pos - cap.posA;
			bool flg = cap.Vec().Cross(capPosVec) > 0;
			auto nVec = (flg ? cap.Vec().RotaVecRight90() : cap.Vec().RotaVecLeft90()).Normalized();
			auto mag = (colCircle_.radius + cap.radius) - (hitPair.second - pos).Magnitude();

			//めり込みカウント
			intoLineCnt++;

			Vector2Dbl correctVec = nVec * mag;

			line->SetColObjInfo(std::make_unique<ColInfo>(id_, cap));

			pos += correctVec;
			ret += correctVec;
		}

		return false;
	};

	lineCtrl.GetLineInfoCap(correctHitCap);
	return ret;
}

bool Unit::CheckRayLine(Raycast::Ray ray, LineCtrl& lineCtrl)const
{
	bool ret = false;
	auto checkHitCap = [&](const Capsule& cap, LinePtr& line) {
		ret |= raycast_.CalcLineDist(ray, { cap.posA,cap.posB }).SQMagnitude() < pow(cap.radius, 2);
		return false;
	};

	lineCtrl.GetLineInfoCap(checkHitCap);
	return ret;
}

Unit::State Unit::UpdateState(ObjList& objList, LineCtrl& lineCtrl, const Stage& stage, Vector2Dbl checkVec)const
{
	const auto& mapiInfo = stage.GetMapInfo();
	const auto& colList = mapiInfo.GetColLsit();

	int intoLineCnt = 0;

	Vector2Dbl colCorrect = CheckMove(colList, checkVec);
	Vector2Dbl objCorrect = CheckMove(objList, correctVec_);
	Vector2Dbl lineCorrect = CheckMove(lineCtrl, intoLineCnt, checkVec);

	return UpdateState(lineCtrl, colCorrect, objCorrect, lineCorrect);
	
}

Unit::State Unit::UpdateState(LineCtrl& lineCtrl,const Vector2Dbl& colCorrect, const Vector2Dbl& objCorrect, const Vector2Dbl& lineCorrect) const
{
	if (state_ == State::Death || state_ == State::Damaged)
	{
		return state_;
	}

	State state;

	if ((colCorrect.y == 0.0) && (objCorrect.y == 0.0) && (lineCorrect.y == 0.0))
	{
		state = State::InAir;
	}
	else if ((colCorrect.y >= 0.0) && (objCorrect.y >= 0.0) && (lineCorrect.y >= 0.0))
	{
		state = State::TouchCeiling;
	}
	else if ((colCorrect.y <= 0.0) && (objCorrect.y <= 0.0) && (lineCorrect.y <= 0.0))
	{
		state = State::TouchFloor;

		if (!CheckRayLine({ pos_,groundRayMaxVec_ }, lineCtrl) && lineCorrect.y < 0.0)
		{
			state = State::InAir;
		}

	}
	else
	{
		state = State::Sandwiched;
	}

	return state;
}


