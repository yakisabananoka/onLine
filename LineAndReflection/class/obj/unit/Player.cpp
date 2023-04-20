#include <algorithm>
#include <cmath>
#include <array>
#include <sstream>
#include <DxLib.h>
#include "Player.h"
#include "../../scene/SceneMng.h"
#include "../../common/SoundMng.h"
#include "../../scene/Camera.h"
#include "../../stage/Stage.h"
#include "../../line/LineCtrl.h"
#include "../../input/Controller.h"
#include "../../../_debug/_debugDispOut.h"

namespace pl_const
{
	constexpr double size = 32.0;
	constexpr double speed = 250.0;
	constexpr double jumpSpeed = -510.0;
	constexpr double maxSpeed = 700.0;
	//constexpr double gravity = 12.5;
	constexpr double gravity = 500.0;
	constexpr int posnum = 32;

	constexpr double bound_coeff = 300.0;
	constexpr double bound_thre = 0.0;
	constexpr double rebornTime = 1.0;

	constexpr int defLife = 5;
	constexpr int minLife = 3;

	constexpr double blinkTime = 0.1;

	constexpr double damagedInviTime = 3.0;

	constexpr double shakeTime = 0.5;
	constexpr double shakeMag = 10.0;

	constexpr Vector2Dbl barieerBaseVec = Vector2Dbl(0.0, -32.0);

	namespace se
	{
		constexpr char jump[] = "jump";
	}
}

using namespace pl_const;

Player::Player(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Unit(camera, pos, size, id, gravity, maxSpeed)
{
	controller_ = lpSceneMng.GetController();
	boundThre_ = std::make_unique<double>(bound_thre);
	boundCoeff_ = std::make_unique<double>(bound_coeff);
	lpSoundMng.LoadSound(se::jump);
	Init();
}

Player::~Player()
{
}

void Player::Init(void)
{
	Unit::Init();
	dethPos_ = nullptr;
	oldPos_ = pos_;
	corePos_ = pos_;
	if (initPos_)
	{
		pos_ = *initPos_;
	}
}

void Player::Draw(void)
{
	if (state_ == State::Death)
	{
		return;
	}

	if (invicibleTime_)
	{
		if (static_cast<int>((*invicibleTime_) / blinkTime) % 2 == 0)
		{
			return;
		}
	}

	//カメラのオフセットを取得
	Vector2Dbl camOffset = GetCamOffset();

	//当たり判定描画(画像置き換え)
	//SetDrawBlendMode(DX_BLENDMODE_ADD, 128);
	DrawCircleAA(
		static_cast<float>(camOffset.x + pos_.x),
		static_cast<float>(camOffset.y + pos_.y),
		static_cast<float>(size + 2.0),
		posnum, 0x000000, true
	);

	DrawCircleAA(
		static_cast<float>(camOffset.x + pos_.x),
		static_cast<float>(camOffset.y + pos_.y),
		static_cast<float>(size),
		posnum, 0xff0000, true
	);

	//DrawCircleAA(
	//	static_cast<float>(camOffset.x + corePos_.x),
	//	static_cast<float>(camOffset.y + corePos_.y),
	//	static_cast<float>(size / 2.0),
	//	posnum, 0xff0000, true
	//);

	//SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	
}

bool Player::Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	oldPos_ = pos_;

	//移動ベクトル
	if (controller_->NowOn(InputID::UP) && jumpFlg_)
	{
		moveVec_.y += jumpSpeed;
		lpSoundMng.PlaySE(se::jump);
		jumpFlg_ = false;
	}
	if (controller_->NowOn(InputID::LEFT))
	{
		if (!CheckRayLine({ pos_,-wallRayMaxVec_ }, lineCtrl))
		{
			moveVec_.x -= speed;
		}
	}
	if (controller_->NowOn(InputID::RIGHT))
	{
		if (!CheckRayLine({ pos_,wallRayMaxVec_ }, lineCtrl))
		{
			moveVec_.x += speed;
		}
	}

	return false;
}

bool Player::DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (damagedPos_)
	{
		SetInvincible(damagedInviTime);
		if (!camera_.expired())
		{
			camera_.lock()->SetShake(shakeTime, shakeMag);
		}
		moveVec_ = {};
		damagedPos_ = nullptr;
	}

	if (!camera_.expired())
	{
		if (camera_.lock()->IsShake())
		{
			return true;
		}
	}

	if (dethPos_ == nullptr)
	{
		dethPos_ = std::make_unique<Vector2Dbl>(pos_);
	}

	Vector2Dbl rebornPos = initPos_ ? *initPos_ : defPos_;

	auto deltaVec = rebornPos - (*dethPos_);

	auto time = stateTime_ - shakeTime;

	pos_.x = easing_.InOutCirc(time, dethPos_->x, deltaVec.x, rebornTime);
	pos_.y = easing_.InOutCirc(time, dethPos_->y, deltaVec.y, rebornTime);

	if (time >= rebornTime)
	{
		Init();
		lineCtrl.Init();
	}

	return true;
}

bool Player::DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (damagedPos_)
	{
		SetInvincible(damagedInviTime);
		if (!camera_.expired())
		{
			camera_.lock()->SetShake(shakeTime, shakeMag);
		}
		damagedPos_ = nullptr;
	}

	if (!camera_.expired())
	{
		if (camera_.lock()->IsShake())
		{
			return true;
		}
	}

	if(dethPos_ == nullptr)
	{
		moveVec_ = {};
		dethPos_ = std::make_unique<Vector2Dbl>(pos_);
	}

	Vector2Dbl rebornPos = initPos_ ? *initPos_ : defPos_;

	auto deltaVec = rebornPos - (*dethPos_);

	pos_.x = easing_.InOutCirc(stateTime_ - shakeTime, dethPos_->x, deltaVec.x, rebornTime);
	pos_.y = easing_.InOutCirc(stateTime_ - shakeTime, dethPos_->y, deltaVec.y, rebornTime);

	if (stateTime_ >= rebornTime)
	{
		Init();
		lineCtrl.Init();
	}

	return true;
}

void Player::SetInitPos(const Vector2Dbl& pos)
{
	initPos_ = std::make_unique<Vector2Dbl>(pos);
}

void Player::DrawBarrier(int num, double angle)
{
	Vector2Dbl basePos = barieerBaseVec.RotaVec(angle);
	
}

