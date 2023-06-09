#include <DxLib.h>

#include "TransitionScene.h"
#include "../../../_debug/_DebugConOut.h"

TransitionScene::TransitionScene(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> args) :
	BaseScene(args), beforeScene_(std::move(beforeScene)), nextScene_(std::move(nextScene))
{
	//ここは修正する時期を見計らって修正

	TRACE("TransitionSceneの生成\n");
}

TransitionScene::~TransitionScene()
{
}

uniBaseScene TransitionScene::Update(double delta, uniBaseScene own)
{
	if (UpdateTransition(delta))
	{
		TRACE("TransitionScene終了\n");
		nextScene_->PlaySceneBGM();
		return std::move(nextScene_);
	}
	return own;
}

bool TransitionScene::Init(void)
{
	//何もしない
	return true;
}
