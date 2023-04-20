#pragma once
#include "../../SceneArgsStruct.h"
#include "../PlayMenu.h"
#include "../HowToPlay.h"
#include "../OptionMenu.h"

using namespace SceneArgsStruct;
using namespace Temporary;

//�ꎞ�V�[��
namespace TpGenerators
{
	//�v���C���̃��j���[�p
	struct PlayMenuGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<PlayMenu>(std::move(ownScene), std::static_pointer_cast<PlayMenuArgs>(argPtr));
		}
	};

	//�v���C�����p
	struct HowToPlayGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<HowToPlay>(std::move(ownScene), std::static_pointer_cast<HowToPlayArgs>(argPtr));
		}
	};

	//�I�v�V�������j���[�p
	struct OptionMenuGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, std::shared_ptr<TemporaryArgs> argPtr)
		{
			return std::make_unique<OptionMenu>(std::move(ownScene), std::static_pointer_cast<OptionMenuArgs>(argPtr));
		}
	};
}

