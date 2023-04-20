#include "../scene/Camera.h"
#include "CoinCtrl.h"
#include "Goal.h"
#include "CameraInduction.h"

CoinCtrl::CoinCtrl(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Obj(camera, pos, id)
{
	Init();
}

CoinCtrl::~CoinCtrl()
{
}

void CoinCtrl::Init(void)
{
	maxCoinCnt_ = 0;
}

void CoinCtrl::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	int coinCnt = 0;
	Vector2Dbl playerPos;
	int playerId = 0;

	for (const auto& obj : objList)
	{
		if (obj->GetObjType() == ObjType::COIN)
		{
			coinCnt++;
			continue;
		}
		if (obj->GetObjType() == ObjType::PLAYER)
		{
			playerPos = obj->GetPos();
			playerId = obj->GetObjID();
		}
	}

	maxCoinCnt_ = std::max(maxCoinCnt_, coinCnt);

	if (coinCnt)
	{
		return;
	}

	auto ptr = std::make_shared<CameraInduction>(camera_, playerPos, pos_, 1.0, 0.5, playerId);
	if (!camera_.expired())
	{
		camera_.lock()->SetTarget(ptr);
	}
	objList.emplace_back(ptr);
	objList.emplace_back(std::make_shared<Goal>(camera_, pos_, id_));
	activeFlg_ = false;
}

void CoinCtrl::Draw(void)
{
}

int CoinCtrl::GetMaxCoinCnt(void) const
{
	return maxCoinCnt_;
}
