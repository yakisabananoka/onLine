#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, double size, int id, double gravity, double maxSpeed) :
	Unit(camera, pos, size, id, gravity, maxSpeed)
{
	Init();
}

Enemy::~Enemy()
{
}

void Enemy::Init(void)
{
	Unit::Init();
}

bool Enemy::Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	for (auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		//auto player = std::dynamic_pointer_cast<Player>(obj);
		auto& player = dynamic_cast<Player&>(*obj);

		if (player.GetColCircle().CheckHit(colCircle_))
		{
			player.AddDamagedPnt(-1, pos_);
			ColMotion(delta, obj);
		}
	}

	return EnemyMotion(delta, objList, lineCtrl, stage);
}
