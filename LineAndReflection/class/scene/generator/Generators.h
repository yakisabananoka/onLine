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

//�V�[���p�����֐��I�u�W�F�N�g
namespace SceneGenerators
{
	//�^�C�g���p
	struct TitleGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<TitleScene>(std::static_pointer_cast<TitleArgs>(argPtr));
		}
	};

	//�I�v�V�����p
	struct OptionGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<OptionScene>(std::static_pointer_cast<OptionArgs>(argPtr));
		}
	};

	//�`���[�g���A���p
	struct TutorialCheckGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<TutorialCheckScene>(std::static_pointer_cast<TutorialCheckArgs>(argPtr));
		}
	};

	//�Z���N�g�p
	struct SelectGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<SelectScene>(std::static_pointer_cast<SelectArgs>(argPtr));
		}
	};

	//�Q�[���p
	struct GameGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<GameScene>(std::static_pointer_cast<GameArgs>(argPtr));
		}
	};

	//���U���g�p
	struct ResultGenerator
	{
		uniBaseScene operator()(std::shared_ptr<BaseArgs> argPtr)
		{
			return std::make_unique<ResultScene>(std::static_pointer_cast<ResultArgs>(argPtr));
		}
	};
}
