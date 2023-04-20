#include "Block.h"
#include "../common/ImageMng.h"
#include "../common/SoundMng.h"
#include "../scene/Camera.h"
#include "../line/LineCtrl.h"
#include "../line/BaseLine.h"
#include "../collision/SetCollisionForRect.h"
#include "../common/shape/Capsule.h"

namespace block_const
{
	constexpr char image[] = "tileset1";
	constexpr int chipID = 782;
	constexpr char sound[] = "block";
}

using namespace block_const;

Block::Block(std::weak_ptr<Camera> camera, Rect range, int id) :
	Obj(camera, range.pos, id),range_(range)
{
	colPtr_ = std::make_unique<Collision>(range);
	colPtr_->SetVertexPtr(SetCollisionForRect::SetVertexPtr()(range));
	colPtr_->SetIndexPtr(SetCollisionForRect::SetIndexPtr()(range));

	lpSoundMng.LoadSound(sound);

	Init();
}

Block::~Block()
{
}

void Block::Init(void)
{
}

void Block::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	auto checkTouch = [&](const Node& node, LinePtr& line) {
		if (range_.InShape(node.pos))
		{
			lpSoundMng.PlaySE(sound);
			activeFlg_ = false;
			return true;
		}

		return false;
	};

	lineCtrl.GetLineInfoNode(checkTouch);
}

void Block::Draw(void)
{
	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	DrawGraph(
		static_cast<int>(camOffset.x + range_.pos.x), static_cast<int>(camOffset.y + range_.pos.y),
		lpImageMng.GetID(image)[chipID], true
	);
}
