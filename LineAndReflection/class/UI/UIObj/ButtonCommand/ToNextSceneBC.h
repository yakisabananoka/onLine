#pragma once
#include <memory>
#include "ButtonCommand.h"
#include "../../../scene/SceneID.h"
#include "../../../scene/transition/TransitionID.h"

namespace SceneArgsStruct
{
    struct BaseArgs;

    namespace Transition
    {
        struct TransitionArgs;
    }
}

class ToNextSceneBC :
    public ButtonCommand
{
public:
    ToNextSceneBC(SceneID sceneID, TransitionID trID, 
        std::shared_ptr<SceneArgsStruct::BaseArgs> sceneArgs,
        std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs);
    ~ToNextSceneBC();

    void Execute(Button& button)override;

private:
    SceneID sceneID_;
    TransitionID trID_;
    std::shared_ptr<SceneArgsStruct::BaseArgs> sceneArgs_;
    std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> transArgs_;

};

