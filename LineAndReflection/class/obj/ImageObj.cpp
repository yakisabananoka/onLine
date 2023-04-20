#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../scene/Camera.h"
#include "ImageObj.h"
#include "../common/Utility.h"

ImageObj::ImageObj(std::weak_ptr<Camera> camera, Vector2Dbl pos, std::string path, double deg, double mag, int id) :
	Obj(camera, pos, id), path_(path), rad_(utility::DegToRad()(deg)), mag_(mag)
{
	Init();
}

ImageObj::~ImageObj()
{
}

void ImageObj::Init(void)
{
	lpImageMng.GetID(path_);
}

void ImageObj::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
}

void ImageObj::Draw(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	DrawRotaGraph(
		static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
		mag_, rad_, lpImageMng.GetID(path_)[0], true
	);
}
