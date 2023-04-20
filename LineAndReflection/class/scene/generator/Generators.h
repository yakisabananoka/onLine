#pragma once
#include <memory>
#include "../BaseScene.h"
#include "../TitleScene.h"
#include "../OptionScene.h"
#include "../TutorialCheckScene.h"
#include "../SelectScene.h"
#include "../GameScene.h"
#include "../ResultScene.h"
#include "../SceneArgsStruct.h"

using namespace SceneArgsStruct;

//シーン用生成関数オブジェクト
namespace SceneGenerators
{
	//タイトル用
	struct TitleGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<TitleScene>(std::static_pointer_cast<TitleArgs>(argPtr));
		}
	};

	//オプション用
	struct OptionGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<OptionScene>(std::static_pointer_cast<OptionArgs>(argPtr));
		}
	};

	//チュートリアル用
	struct TutorialCheckGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<TutorialCheckScene>(std::static_pointer_cast<TutorialCheckArgs>(argPtr));
		}
	};

	//セレクト用
	struct SelectGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<SelectScene>(std::static_pointer_cast<SelectArgs>(argPtr));
		}
	};

	//ゲーム用
	struct GameGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<GameScene>(std::static_pointer_cast<GameArgs>(argPtr));
		}
	};

	//リザルト用
	struct ResultGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<ResultScene>(std::static_pointer_cast<ResultArgs>(argPtr));
		}
	};
}
