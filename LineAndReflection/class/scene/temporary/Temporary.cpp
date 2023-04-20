#include "Temporary.h"
#include "../../../_debug/_debugConOut.h"

Temporary::Temporary(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> args) :
	BaseScene(args), beforeScene_(std::move(beforeScene))
{
}

Temporary::~Temporary()
{
}

uniBaseScene Temporary::Update(double delta, uniBaseScene ownScene)
{
	if (UpdateTemporary(delta))
	{
		TRACE("TemporarySceneèIóπ\n");
		return std::move(beforeScene_);
	}
	return ownScene;
}

bool Temporary::Init(void)
{
	return true;
}
