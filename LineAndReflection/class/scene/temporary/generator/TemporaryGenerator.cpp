#include "TemporaryGenerator.h"
#include "../TemporaryID.h"
#include "Generators.h"

TemporaryGenerator::TemporaryGenerator()
{
    genMap_.try_emplace(TemporaryID::PlayMenu, TpGenerators::PlayMenuGenerator());
    genMap_.try_emplace(TemporaryID::HowToPlay, TpGenerators::HowToPlayGenerator());
    genMap_.try_emplace(TemporaryID::OptionMenu, TpGenerators::OptionMenuGenerator());
}

TemporaryGenerator::~TemporaryGenerator()
{
}

uniBaseScene TemporaryGenerator::Generate(TemporaryID type, uniBaseScene ownScene, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> tempArgs)
{
    return genMap_[type](std::move(ownScene), tempArgs);
}
