#include <DxLib.h>
#include "../scene/SceneMng.h"
#include "../common/ImageMng.h"
#include "../common/FontMng.h"
#include "../scene/SceneArgsStruct.h"
#include "../scene/Camera.h"
#include "../stage/Stage.h"
#include "Door.h"
#include "ObjType.h"
#include "../common/shape/Rect.h"

namespace door_const
{
	constexpr char imagePath[] = "data/image/tileset_64x64.png";
	constexpr int door_up = 778;
	constexpr int door_down = 799;

	constexpr Vector2Dbl downOffset = { 0.0,64.0 };

	constexpr Vector2Dbl size = { 64.0,128.0 };

	constexpr char fontKey[] = "result_button";
	constexpr char fontPath[] = "data/font/03スマートフォントUI.otf";
	constexpr char fontName[] = "03スマートフォントUI";
	constexpr int fontSize = 30;
	constexpr int fontThick = 10;
}

using namespace door_const;

Door::Door(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id, std::string nextMapPath, bool useFadeImage, std::string fadeImagePath, bool useThumb, std::string thumbImagePath) :
	Obj(camera, pos, id), nextMapPath_(nextMapPath), size_(size), useFadeImage_(useFadeImage), fadeImagePath_(fadeImagePath), useThumb_(useThumb), thumbImagePath_(thumbImagePath)
{
	controller_ = lpSceneMng.GetController();
	Init();
}

Door::~Door()
{
}

void Door::Init(void)
{
	state_ = State::None;
	lpFontMng.GetID(fontKey, fontPath, fontName, fontSize, fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);
}

void Door::Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)
{
	state_ = State::None;

	for (auto& obj : objList)
	{
		if (obj->GetObjType() != ObjType::PLAYER)
		{
			continue;
		}

		const auto& plPos = obj->GetPos();
		Rect range;
		range.pos = pos_;
		range.size = size_;

		if (range.InShape(plPos))
		{
			state_ = State::OnDoor;
			break;
		}
	}

	if (state_ != State::OnDoor)
	{
		return;
	}

	if (controller_->JustOn(InputID::UP))
	{
		std::shared_ptr<SceneArgsStruct::BaseArgs> sceneArgs;
		std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs;
		TransitionID id;

		if (useFadeImage_)
		{
			sceneArgs = std::make_shared<SceneArgsStruct::GameArgs>(nextMapPath_);
			transArgs = std::make_shared<SceneArgsStruct::Transition::FadeMArgs>(fadeImagePath_);
			id = TransitionID::FadeM;
		}
		else
		{
			sceneArgs = std::make_shared<SceneArgsStruct::GameArgs>(nextMapPath_);
			transArgs = std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>();
			id = TransitionID::FadeIO;
		}

		lpSceneMng.SetNextScene(SceneID::Game, id, sceneArgs, transArgs);
	}

	stage.GetMapInfo().GetMapData();
}

void Door::Draw(void)
{
	if (state_ != State::OnDoor)
	{
		return;
	}

	Vector2Dbl camOffset;
	if (!camera_.expired())
	{
		camOffset = camera_.lock()->GetDrawOffset();
	}

	if (useThumb_)
	{
		DrawRotaGraph(
			static_cast<int>(camOffset.x + pos_.x + 32.0),
			static_cast<int>(camOffset.y + pos_.y - 40.0),
			0.4, 0.0, lpImageMng.GetID(thumbImagePath_)[0], true
		);
	}

	DrawStringToHandle(
		static_cast<int>(camOffset.x + pos_.x - 20.0), static_cast<int>(camOffset.y + pos_.y + 128.0),
		"JUMP!!!", 0xffffff, lpFontMng.GetID(fontKey), 0x000000
	);

	//DrawGraph(
	//	static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
	//	lpImageMng.GetID(imagePath)[door_up], true
	//);
	//int i = DrawGraph(
	//	static_cast<int>(camOffset.x + pos_.x + downOffsetX), static_cast<int>(camOffset.y + pos_.y + downOffsetY),
	//	lpImageMng.GetID(imagePath)[door_down], true
	//);

	//DrawBox(
	//	static_cast<int>(camOffset.x + pos_.x), static_cast<int>(camOffset.y + pos_.y),
	//	static_cast<int>(camOffset.x + pos_.x + 64.0), static_cast<int>(camOffset.y + pos_.y + 64.0),
	//	0xff0000, true
	//);
}
