#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include "../../BaseScene.h"

enum class TemporaryID;

namespace SceneArgsStruct
{
	namespace Temporary
	{
		struct TemporaryArgs;
	}
}

using TpGeneratorMap = std::unordered_map<TemporaryID, std::function<uniBaseScene(uniBaseScene, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs>)>>;

class TemporaryGenerator
{
public:
	TemporaryGenerator();
	~TemporaryGenerator();

	uniBaseScene Generate(TemporaryID type, uniBaseScene ownScene, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> tempArgs);					//�Ή�����Temporary�𐶐�

private:
	TpGeneratorMap genMap_;		//�����p�}�b�v
};

