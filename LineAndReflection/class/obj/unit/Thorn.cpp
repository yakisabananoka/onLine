#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "Player.h"
#include "Thorn.h"
#include "../../common/shape/Circle.h"

namespace thorn_const
{
	constexpr double size = 32.0;
	constexpr double speed = 200.0;
	constexpr double jumpSpeed = -510.0;
	constexpr double maxSpeed = 600.0;
	constexpr double gravity = 500.0;

	constexpr char image[] = "tileset1";
	constexpr int chipID = 747;

	constexpr Vector2Dbl offset = Vector2Dbl(32.0, 32.0);
}

using namespace thorn_const;

Thorn::Thorn(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Obj(camera, pos, id)
{
}

Thorn::~Thorn()
{
}

void Thorn::Init(void)
{
}

void Thorn::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	Circle colCircle(pos_ + offset, size);
	for (auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		//auto player = std::dynamic_pointer_cast<Player>(obj);
		auto& player = dynamic_cast<Player&>(*obj);

		if (player.GetColCircle().CheckHit(colCircle))
		{
			player.AddDamagedPnt(-1, pos_);
		}
	}
}

void Thorn::Draw(void)
{
	Vector2Dbl camOffset = GetCamOffset();
	DrawGraph(
		static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
		lpImageMng.GetID(image)[chipID], true
	);
}
