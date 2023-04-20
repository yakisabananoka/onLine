#pragma once
#include "../../SceneArgsStruct.h"
#include "../PlayMenu.h"
#include "../HowToPlay.h"
#include "../OptionMenu.h"

using namespace SceneArgsStruct;
using namespace Temporary;

//一時シーン
namespace TpGenerators
{
	//プレイ中のメニュー用
	struct PlayMenuGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<PlayMenu>(std::move(ownScene), std::static_pointer_cast<PlayMenuArgs>(argPtr));
		}
	};

	//プレイ説明用
	struct HowToPlayGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<HowToPlay>(std::move(ownScene), std::static_pointer_cast<HowToPlayArgs>(argPtr));
		}
	};

	//オプションメニュー用
	struct OptionMenuGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<OptionMenu>(std::move(ownScene), std::static_pointer_cast<OptionMenuArgs>(argPtr));
		}
	};
}

