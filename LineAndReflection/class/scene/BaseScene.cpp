#include <DxLib.h>
#include "SceneMng.h"
#include "../common/SoundMng.h"
#include "BaseScene.h"
#include "SceneArgsStruct.h"

BaseScene::BaseScene(std::shared_ptr<SceneArgsStruct::BaseArgs> args) :
	scrSize_(lpSceneMng.GetWindowSize())
{
	scrID_ = MakeScreen(scrSize_.x, scrSize_.y);
	nextScene_ = nullptr;

	if (args->stopBGMFlg)
	{
		lpSoundMng.StopBGM();
	}
}

BaseScene::~BaseScene()
{
}

void BaseScene::Draw(void)
{
	DrawGraph(0, 0, scrID_, true);
}

const Vector2& BaseScene::GetScreenSize(void)
{
	return scrSize_;
}

const int& BaseScene::GetScrID(void)
{
	return scrID_;
}
