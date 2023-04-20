#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include "../BaseScene.h"

namespace SceneArgsStruct
{
	struct BaseArgs;
}

enum class SceneID;

using SceneGeneratorMap = std::unordered_map<SceneID, std::function<uniBaseScene(std::shared_ptr<SceneArgsStruct::BaseArgs>)>>;

class SceneGenerator
{
public:
	SceneGenerator();
	~SceneGenerator();

	uniBaseScene Generate(SceneID type, std::shared_ptr<SceneArgsStruct::BaseArgs> argPtr);				//対応するSceneを生成

private:
	SceneGeneratorMap genMap_;		//生成用マップ
};

