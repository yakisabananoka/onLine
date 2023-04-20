#pragma once
#include "../../SceneArgsStruct.h"
#include "../CrossOver.h"
#include "../Square.h"
#include "../FadeIO.h"
#include "../FadeM.h"

using namespace SceneArgsStruct;
using namespace Transition;

//移行シーンの生成用関数オブジェクト
namespace TrGenerators
{
	//クロスオーバー用
	struct CrossOverGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<CrossOver>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<CrossOverArgs>(argPtr));
		}
	};

	//矩形パネル用
	struct SquareGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<Square>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<SquareArgs>(argPtr));
		}
	};

	//フェード用
	struct FadeIOGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<FadeIO>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<FadeIOArgs>(argPtr));
		}
	};

	//ミッション付きフェード用
	struct FadeMGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<FadeM>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<FadeMArgs>(argPtr));
		}
	};
}

