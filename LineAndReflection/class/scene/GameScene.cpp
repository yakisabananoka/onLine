#include <array>
#include "SceneMng.h"
#include "../common/SoundMng.h"
#include "../common/FontMng.h"
#include "Camera.h"
#include "GameScene.h"
#include "ResultScene.h"
#include "SceneArgsStruct.h"
#include "../scene/temporary/TemporaryID.h"
#include "../obj/Obj.h"
#include "../stage/Stage.h"
#include "../line/LineCtrl.h"
#include "../obj/ObjType.h"
#include "../UI/UIObj/NormalButton.h"
#include "../UI/UIObj/ButtonCommand/ToNextTemporaryBC.h"
#include "../../_debug/_debugConOut.h"

namespace game_const
{
	namespace button
	{
		constexpr char image[] = "data/image/004_01.png";                           //�ʏ펞�̉摜
		constexpr char imageClick[] = "data/image/004_01_click.png";                //�N���b�N���̉摜
		constexpr char imageHover[] = "data/image/004_01_hover.png";                //��ɏ悹�Ă�Ƃ��̉摜

		constexpr char fontKey[] = "game_button";                                   //�t�H���g�̃L�[
		constexpr char fontPath[] = "data/font/03�X�}�[�g�t�H���gUI.otf";           //�t�H���g�̃p�X
		constexpr char fontName[] = "03�X�}�[�g�t�H���gUI";                         //�t�H���g��

		constexpr int fontSize = 60;                                                //�t�H���g�̃T�C�Y
		constexpr int fontThick = 10;                                               //�t�H���g�̑���

		constexpr unsigned int textColor = 0xffffff;
		constexpr unsigned int edgeColor = 0x000000;

		constexpr Vector2Dbl clickOffset = { 0.0,5.0 };
		constexpr Vector2Dbl basePos = { 40.0,40.0 };

		namespace menu
		{
			constexpr char text[] = "��";
			constexpr Vector2Dbl pos = basePos;
		}
	}
}

using namespace game_const;

GameScene::GameScene(std::shared_ptr<SceneArgsStruct::GameArgs> args):
	BaseScene(args)
{
	TRACE("GameScene�̐���\n");

	objList_.reserve(100);
	camera_ = std::make_shared<Camera>();
	stage_ = std::make_shared<Stage>(args->mapfilePath_, camera_);
	lineCtrl_ = std::make_unique<LineCtrl>(camera_, stage_->GetMapInfo().GetLineType());

	menuFlg_ = args->menuFlg_;

	lpSoundMng.LoadSound(stage_->GetMapInfo().GetBGM());

	Init();
	InitUI();
}

GameScene::~GameScene()
{
	TRACE("GameScene�̔j��\n");

	lineCtrl_.reset();
}

bool GameScene::Init(void)
{
	//�I�u�W�F�N�g�𐶐�
	stage_->SetObj(objList_);

	//�J�����̒Ǐ]�ݒ�
	for (auto& obj : objList_)
	{
		obj->SetUI(uiCtrl_);
		if (obj->GetObjType() == ObjType::PLAYER)
		{
			camera_->SetStageAndTarget(stage_, obj);
		}
	}
	lineCtrl_->InitUI(uiCtrl_);

	return true;
}

bool GameScene::InitUI(void)
{
	lpFontMng.GetID(button::fontKey, button::fontPath, button::fontName, button::fontSize, button::fontThick, DX_FONTTYPE_ANTIALIASING_EDGE_8X8);


	if (menuFlg_)
	{
		auto menuPtr = std::make_unique<NormalButton>(
			button::menu::pos,button::menu::text, button::fontKey, button::textColor, button::edgeColor,
			button::image, button::imageHover, button::imageClick,
			std::make_unique<ToNextTemporaryBC>(
				TemporaryID::PlayMenu, std::make_shared<SceneArgsStruct::Temporary::PlayMenuArgs>()),
			button::clickOffset);

		uiCtrl_.SetUI(std::move(menuPtr));
	}

	return true;
}

uniBaseScene GameScene::Update(double delta, uniBaseScene ownScene)
{
	auto removeItr = std::remove_if(objList_.begin(), objList_.end(), [](const ObjPtr& objPtr) {return !objPtr->IsActive(); });
	objList_.erase(removeItr, objList_.end());

	lineCtrl_->Update(delta, *stage_);
	stage_->Update(delta);

	bool sceneEndFlg = false;
	for (auto& obj : objList_)
	{
		obj->Update(delta, objList_, *lineCtrl_, *stage_);
	}

	lineCtrl_->UpdateAfterObj(delta, objList_);

	for (auto& obj : objList_)
	{
		obj->ConfirmUpdate(delta, *stage_);
		sceneEndFlg |= obj->GetSceneEndFlg();
	}

	if (sceneEndFlg)
	{
		lpSceneMng.SetNextScene(SceneID::Result, TransitionID::FadeIO,
			std::make_shared<SceneArgsStruct::ResultArgs>(stage_->GetCntTime(), lineCtrl_->GetTotalLineDist()),
			std::make_shared<SceneArgsStruct::Transition::FadeIOArgs>());
	}

	camera_->Update(delta);

	uiCtrl_.Update(delta);

	DrawOwnScreen();

	return ownScene;
}

void GameScene::DrawOwnScreen(void)
{
	SetDrawScreen(scrID_);
	ClsDrawScreen();

	stage_->Draw();

	for (auto& obj : objList_)
	{
		obj->Draw();
	}

	lineCtrl_->Draw();

	camera_->Draw();

	uiCtrl_.Draw();
}

void GameScene::PlaySceneBGM(void)
{
	lpSoundMng.PlayBGM(stage_->GetMapInfo().GetBGM());
}
