#pragma once
#include "../../SceneArgsStruct.h"
#include "../CrossOver.h"
#include "../Square.h"
#include "../FadeIO.h"
#include "../FadeM.h"

using namespace SceneArgsStruct;
using namespace Transition;

//�ڍs�V�[���̐����p�֐��I�u�W�F�N�g
namespace TrGenerators
{
	//�N���X�I�[�o�[�p
	struct CrossOverGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<CrossOver>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<CrossOverArgs>(argPtr));
		}
	};

	//��`�p�l���p
	struct SquareGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<Square>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<SquareArgs>(argPtr));
		}
	};

	//�t�F�[�h�p
	struct FadeIOGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<FadeIO>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<FadeIOArgs>(argPtr));
		}
	};

	//�~�b�V�����t���t�F�[�h�p
	struct FadeMGenerator
	{
		uniBaseScene operator()(uniBaseScene ownScene, uniBaseScene nextScene, std::shared_ptr<TransitionArgs> argPtr)
		{
			return std::make_unique<FadeM>(std::move(ownScene), std::move(nextScene), std::static_pointer_cast<FadeMArgs>(argPtr));
		}
	};
}

