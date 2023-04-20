#include "../../../scene/SceneMng.h"
#include "ToNextTemporaryBC.h"

ToNextTemporaryBC::ToNextTemporaryBC(TemporaryID id, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> tempArgs) :
	tempID_(id), tempArgs_(tempArgs)
{
}

ToNextTemporaryBC::~ToNextTemporaryBC()
{
}

void ToNextTemporaryBC::Execute(Button& button)
{
	lpSceneMng.SetNextScene(tempID_, tempArgs_);
}
