#include <DxLib.h>
#include "Obj.h"
#include "../scene/Camera.h"
#include "../collision/Collision.h"

Obj::Obj(std::weak_ptr<Camera> camera, const Vector2Dbl& pos, const int& id) :
	camera_(camera), defPos_(pos), pos_(pos), id_(id)
{
	sceneEndFlg_ = false;
	activeFlg_ = true;
}

Obj::~Obj()
{
}

Vector2Dbl Obj::GetCamOffset(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	return camOffset;
}
