#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "RunEnemy.h"

namespace runEnemy_const
{
	constexpr double size = 32.0;
	constexpr double speed = 300.0;
	constexpr double jumpSpeed = -510.0;
	constexpr double maxSpeed = 600.0;
	constexpr double gravity = 500.0;

	constexpr char image[] = "tileset1";
	constexpr int chipID = 827;
}

using namespace runEnemy_const;

RunEnemy::RunEnemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Enemy(camera, pos, size, id, gravity, maxSpeed)
{
	reverseFlg_ = false;
	oldPos_ = pos_;
}

RunEnemy::~RunEnemy()
{
}

void RunEnemy::Draw(void)
{
	Vector2Dbl camOffset = GetCamOffset();
	DrawRotaGraph(
		static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
		1.0, 0.0, lpImageMng.GetID(image)[chipID], true, reverseFlg_
	);
}

bool RunEnemy::EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	Vector2Dbl vec = pos_ - oldPos_;

	if (vec.SQMagnitude() < 0.1)
	{
		reverseFlg_ = !reverseFlg_;
	}

	moveVec_ += Vector2Dbl(reverseFlg_ ? 1.0 : -1.0, 0.0) * speed;

	oldPos_ = pos_;
	return false;
}
