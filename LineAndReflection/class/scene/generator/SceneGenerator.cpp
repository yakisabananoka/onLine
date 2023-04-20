#include "SceneGenerator.h"
#include "Generators.h"
#include "../SceneArgsStruct.h"

SceneGenerator::SceneGenerator()
{
    genMap_.try_emplace(SceneID::Title, SceneGenerators::TitleGenerator());
    genMap_.try_emplace(SceneID::Option, SceneGenerators::OptionGenerator());
    genMap_.try_emplace(SceneID::TutorialCheck, SceneGenerators::TutorialCheckGenerator());
    genMap_.try_emplace(SceneID::Select, SceneGenerators::SelectGenerator());
    genMap_.try_emplace(SceneID::Game, SceneGenerators::GameGenerator());
    genMap_.try_emplace(SceneID::Result, SceneGenerators::ResultGenerator());
}

SceneGenerator::~SceneGenerator()
{
}

uniBaseScene SceneGenerator::Generate(SceneID type, std::shared_ptr<SceneArgsStruct::BaseArgs> argPtr)
{
    return genMap_[type](argPtr);
}
