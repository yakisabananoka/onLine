#include <sstream>
#include <DxLib.h>
#include "../common/ImageMng.h"
#include "../common/SoundMng.h"
#include "../common/FontMng.h"
#include "../scene/Camera.h"
#include "Coin.h"
#include "CoinCtrl.h"
#include "../collision/Collision.h"
#include "../effectObj/ItemEffect.h"
#include "../collision/SetCollisionForRect.h"

namespace coin_const
{
	constexpr char imageKey[] = "tileset1";
	//constexpr int chipID = 789;
	constexpr char sound[] = "item";

	constexpr char fontKey[] = "coinNum";
	constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";
	constexpr char fontName[] = "03スマートフォントUI";
	constexpr int fontSize = 30;
	constexpr int fontThick = 10;
	constexpr unsigned int color = 0xff0000;
	constexpr unsigned int edgeColor = 0x000000;
}

using namespace coin_const;

Coin::Coin(std::weak_ptr<Camera> camera, Rect range, int id, int chipId) :
	Obj(camera, range.GetCC(), id), range_(range),chipId_(chipId)
{
	lpSoundMng.LoadSound(sound);
	lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
	Init();
}

Coin::~Coin()
{
}

void Coin::Init(void)
{
}

void Coin::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
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

		effectPtr_ = std::make_unique<ItemEffect>(camera_, pos_);
		lpSoundMng.PlaySE(sound);
		int cnt = 0;
		int maxCoinCnt = 0;
		for (const auto& cObj : objList)
		{
			if (cObj->GetObjType() == ObjType::COIN)
			{
				cnt++;
			}
			if (cObj->GetObjType() == ObjType::COIN_CTRL)
			{
				auto& coinCtrl = dynamic_cast<CoinCtrl&>(*cObj);
				maxCoinCnt = coinCtrl.GetMaxCoinCnt();
			}
		}
		std::stringstream ss;
		ss << (maxCoinCnt + 1) - cnt;
		cnt_ = ss.str();
	}
}

void Coin::Draw(void)
{
	Vector2Dbl camOffset = GetCamOffset();

	if (effectPtr_)
	{
		effectPtr_->Draw();
		DrawStringToHandle(
			static_cast<int>(camOffset.x + range_.GetCT().x), static_cast<int>(camOffset.y + range_.GetCT().y - 64.0),
			cnt_.c_str(), color, lpFontMng.GetID(fontKey), edgeColor
		);
	}
	else
	{
		DrawGraph(
			static_cast<int>(camOffset.x + range_.pos.x), static_cast<int>(camOffset.y + range_.pos.y),
			lpImageMng.GetID(imageKey)[chipId_], true
		);
	}
}
