#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../common/SoundMng.h"
#include "../scene/Camera.h"
#include "../effectObj/ItemEffect.h"
#include "unit/Player.h"
#include "SavePoint.h"

namespace savePoint_const
{
	constexpr char imageKey[] = "tileset1";
	constexpr int chipID = 818;
	constexpr char sound[] = "save";
}

using namespace savePoint_const;

SavePoint::SavePoint(std::weak_ptr<Camera> camera, Rect range, int id) :
	Obj(camera, range.GetCC(), id),range_(range)
{
	lpSoundMng.LoadSound(sound);
	Init();
}

SavePoint::~SavePoint()
{
}

void SavePoint::Init(void)
{
}

void SavePoint::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	if (effectPtr_)
	{
		effectPtr_->Update(delta);
		if (effectPtr_->IsEnd())
		{
			activeFlg_ = false;
		}
		return;
	}

	for (auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		if (!range_.InShape(obj->GetPos()))
		{
			return;
		}

		auto& player = dynamic_cast<Player&>(*obj);
		player.SetInitPos(range_.GetCC());
		effectPtr_ = std::make_unique<ItemEffect>(camera_, pos_);
		lpSoundMng.PlaySE(sound);
		break;
	}
}

void SavePoint::Draw(void)
{
	Vector2Dbl camOffset = GetCamOffset();

	if (effectPtr_)
	{
		effectPtr_->Draw();
	}
	else
	{
		DrawGraph(
			static_cast<int>(camOffset.x + range_.pos.x), static_cast<int>(camOffset.y + range_.pos.y),
			lpImageMng.GetID(imageKey)[chipID], true
		);
	}
}
