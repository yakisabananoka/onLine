#include "../../common/ImageMng.h"
#include "../../scene/Camera.h"
#include "BoundEnemy.h"

namespace boundEnemy_const
{
	constexpr double size = 32.0;
	constexpr double speed = 200.0;
	constexpr double jumpSpeed = -510.0;
	constexpr double maxSpeed = 600.0;
	constexpr double gravity = 500.0;

	constexpr char image[] = "tileset1";
	constexpr int chipID = 823;
}

using namespace boundEnemy_const;

BoundEnemy::BoundEnemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Enemy(camera, pos, size, id, gravity, maxSpeed)
{
	reverseFlg_ = true;
}

BoundEnemy::~BoundEnemy()
{
}

void BoundEnemy::Draw(void)
{
	//カメラのオフセットを取得
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	DrawRotaGraph(
		static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
		1.0, 0.0, lpImageMng.GetID(image)[chipID], true,reverseFlg_
	);
}

bool BoundEnemy::EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (jumpFlg_)
	{
		moveVec_.y = jumpSpeed;
		jumpFlg_ = false;
	}

	for (auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		reverseFlg_ = ((obj->GetPos().x - pos_.x) > 0.0);
	}

	return false;
}
