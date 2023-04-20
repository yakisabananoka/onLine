#include <DxLib.h>
#include "../common/ImageMng.h"
#include "Goal.h"
#include "../scene/Camera.h"

namespace goal_const
{
	constexpr char imagePath[] = "tileset1";
	constexpr int chipID = 809;
}

using namespace goal_const;

Goal::Goal(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id) :
	Obj(camera, pos, id)
{
	Init();
}

Goal::~Goal()
{
}

void Goal::Init(void)
{
	Vector2 size;
	GetGraphSize(lpImageMng.GetID(imagePath)[chipID], &size.x, &size.y);
	size_ = static_cast<Vector2Dbl>(size);

}

void Goal::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	for (const auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		Vector2Dbl pos = obj->GetPos();
		if ((pos_ - size_ < pos) && (pos < pos_ + size_))
		{
			sceneEndFlg_ = true;
		}
		break;
	}
}

void Goal::Draw(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	//DrawGraph(
	//	static_cast<int>(camOffset.x + pos_.x),
	//	static_cast<int>(camOffset.y + pos_.y),
	//	lpImageMng.GetID(imagePath)[chipID], false);
	DrawRotaGraph(
		static_cast<int>(camOffset.x + pos_.x),
		static_cast<int>(camOffset.y + pos_.y),
		2.0, 0.0, lpImageMng.GetID(imagePath)[chipID], false
	);


}
