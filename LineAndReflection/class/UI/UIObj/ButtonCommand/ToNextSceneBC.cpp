#include "../../../scene/SceneMng.h"
#include "../../../scene/SceneArgsStruct.h"
#include "ToNextSceneBC.h"

ToNextSceneBC::ToNextSceneBC(SceneID sceneID, TransitionID trID,
	std::shared_ptr<SceneArgsStruct::BaseArgs> sceneArgs, std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs) :
	sceneID_(sceneID), trID_(trID), sceneArgs_(sceneArgs), transArgs_(transArgs)
{
}

ToNextSceneBC::~ToNextSceneBC()
{
}

void ToNextSceneBC::Execute(Button& button)
{
	lpSceneMng.SetNextScene(sceneID_, trID_, sceneArgs_, transArgs_);
}
