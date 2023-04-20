#include "TransitionGenerator.h"
#include "../TransitionID.h"
#include "Generators.h"

TransitionGenerator::TransitionGenerator()
{
    genMap_.try_emplace(TransitionID::CrossOver, TrGenerators::CrossOverGenerator());
    genMap_.try_emplace(TransitionID::Square, TrGenerators::SquareGenerator());
    genMap_.try_emplace(TransitionID::FadeIO, TrGenerators::FadeIOGenerator());
    genMap_.try_emplace(TransitionID::FadeM, TrGenerators::FadeMGenerator());
}

TransitionGenerator::~TransitionGenerator()
{
}

uniBaseScene TransitionGenerator::Generate(TransitionID type, uniBaseScene ownScene, uniBaseScene nextScene,
    std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs)
{
    return genMap_[type](std::move(ownScene), std::move(nextScene), transArgs);
}
