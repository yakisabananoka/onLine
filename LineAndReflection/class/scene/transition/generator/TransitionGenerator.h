#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include "../../BaseScene.h"

enum class TransitionID;

namespace SceneArgsStruct
{
	namespace Transition
	{
		struct TransitionArgs;
	}
}

using TrGeneratorMap = std::unordered_map<TransitionID, std::function<uniBaseScene(uniBaseScene, uniBaseScene, std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs>)>>;

class TransitionGenerator
{
public:
	TransitionGenerator();
	~TransitionGenerator();

	uniBaseScene Generate(TransitionID type, uniBaseScene ownScene, uniBaseScene nextScene,
		std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs);					//対応するTransitionを生成

private:
	TrGeneratorMap genMap_;		//生成用マップ
};

