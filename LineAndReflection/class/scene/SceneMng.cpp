#include <cassert>
#include <sstream>
#include <cmath>
#include <DxLib.h>
#include "../../resource.h"
#include "SceneMng.h"
#include "../common/TimeMng.h"
#include "../common/ImageMng.h"
#include "../common/SoundMng.h"
#include "../common/Utility.h"
#include "TitleScene.h"
#include "GameScene.h"
#include "SceneArgsStruct.h"
#include "../scene/temporary/TemporaryID.h"
#include "../input/InputSelecter.h"
#include "../effectObj/MouseStalker.h"
#include "../../_debug/_debugConOut.h"
#include "../../_debug/_debugDispOut.h"

namespace sceneMng_const
{
	constexpr char backgrPath[] = "data/image/Background.png";
	constexpr char soundListPath[] = "data/sound/soundList.json";

	constexpr Vector2 windowSize = { 1024,768 };
}

using namespace sceneMng_const;

void SceneMng::Run(void)
{
	Init();
	SetWindowText("onLine");
	while (!ProcessMessage() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		
		double delta = lpTimeMng.Update();

		if (!deltaTimeFlg)
		{
			delta = 0.0;
		}

		_dbgStartDraw();
		Update(delta);
		Draw();
		time_ += delta;
	}

	DeleteMaskScreen();
	//Effekseer→Dxlibの順で終了処理
	DxLib_End();
}

const Vector2& SceneMng::GetWindowSize(void)
{
	return windowSize;
}

std::shared_ptr<Controller> SceneMng::GetController(void)
{
	return controller_;
}

void SceneMng::SetNextScene(SceneID nextSceneID, TransitionID nextTransitionID,
	std::shared_ptr<SceneArgsStruct::BaseArgs> nextSceneArgsPtr,
	std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> nextTransArgsPtr)
{
	nextSceneID_ = nextSceneID;
	nextTransitionID_ = nextTransitionID;
	nextSceneArgs_ = nextSceneArgsPtr;
	nextTransArgs_ = nextTransArgsPtr;
}

void SceneMng::SetNextScene(TemporaryID nextTempID,
	std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> nextTempArgsPtr)
{
	nextTemporaryID_ = nextTempID;
	nextTempArgs_ = nextTempArgsPtr;
}

void SceneMng::SetDeltaTimeFlg(bool flg)
{
	deltaTimeFlg = flg;
}

SceneMng::SceneMng()
{
	if (!SysInit())
	{
		//失敗時に再度チェック
		assert(SysInit());
	}
}

SceneMng::~SceneMng()
{
}

bool SceneMng::Init(void)
{
	controller_ = InputSelecter()();

	lpSoundMng.LoadSoundJSON(soundListPath);
	//lpSoundMng.LoadSoundAll();

	scene_ = std::make_unique<TitleScene>(std::make_unique<SceneArgsStruct::TitleArgs>());
	//scene_ = std::make_unique<GameScene>("data/map/map1.json");
	scene_->PlaySceneBGM();

	time_ = 0.0;

	nextSceneID_ = SceneID::None;
	nextTransitionID_ = TransitionID::None;
	nextTemporaryID_ = TemporaryID::None;

	mouseStalker_ = std::make_unique<MouseStalker>();
	
	deltaTimeFlg = true;

	return true;
}

bool SceneMng::SysInit(void)
{
	SetWindowText("初期化中");
	SetGraphMode(windowSize.x, windowSize.y, 32);
	SetOutApplicationLogValidFlag(false);
	ChangeWindowMode(true);
	SetWindowIconID(IDI_ICON1);			//差し替え予定

	if (DxLib_Init() == -1)
	{
		return false;
	}

	CreateMaskScreen();

	_dbgSetup(windowSize.x, windowSize.y, 255);
	lpTimeMng.Init();

	return true;
}

void SceneMng::Update(double delta)
{
	//WindowTextRefresh();
	controller_->Update();
	scene_ = ToNextScene(scene_->Update(delta, std::move(scene_)));
	scene_ = ToNextTempScene(std::move(scene_));
	mouseStalker_->Update();
}

void SceneMng::Draw(void)
{
	SetDrawScreen(DX_SCREEN_BACK);
	ClsDrawScreen();

	DrawGraph(0, 0, lpImageMng.GetID(backgrPath)[0], true);
	scene_->Draw();

	mouseStalker_->Draw();

	_dbgAddDraw();
	ScreenFlip();
}

void SceneMng::WindowTextRefresh(void)
{
	if (!utility::Timer()(time_, 0.5))
	{
		return;
	}

	std::ostringstream oss;
	oss << "タイトル未定 " << "fps:" << (std::round((GetFPS() * 10.0f)) / 10.0f) << std::endl;
	SetWindowText(oss.str().c_str());
}

uniBaseScene SceneMng::ToNextScene(uniBaseScene ownScene)
{
	if (nextSceneID_ == SceneID::None)
	{
		return ownScene;
	}

	uniBaseScene ret;

	uniBaseScene nextScene = sceneGen_.Generate(nextSceneID_, nextSceneArgs_);

	if (nextTransitionID_ == TransitionID::None)
	{
		ret = std::move(nextScene);
	}
	else
	{
		ret = trGen_.Generate(nextTransitionID_, std::move(ownScene), std::move(nextScene), nextTransArgs_);
	}

	nextSceneID_ = SceneID::None;
	nextTransitionID_ = TransitionID::None;
	nextSceneArgs_ = nullptr;
	nextTransArgs_ = nullptr;

	return std::move(ret);
}

uniBaseScene SceneMng::ToNextTempScene(uniBaseScene ownScene)
{
	if (nextTemporaryID_ == TemporaryID::None)
	{
		return std::move(ownScene);
	}

	uniBaseScene ret = tpGen_.Generate(nextTemporaryID_, std::move(ownScene), nextTempArgs_);

	nextTemporaryID_ = TemporaryID::None;
	nextTempArgs_ = nullptr;

	return std::move(ret);
}

