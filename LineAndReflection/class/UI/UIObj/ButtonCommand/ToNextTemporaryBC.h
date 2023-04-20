#pragma once
#include "ButtonCommand.h"

enum class TemporaryID;

namespace SceneArgsStruct
{
    struct BaseArgs;

    namespace Temporary
    {
        struct TemporaryArgs;
    }
}

class ToNextTemporaryBC :
    public ButtonCommand
{
public:
    ToNextTemporaryBC(TemporaryID id, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> tempArgs);
    ~ToNextTemporaryBC();

    void Execute(Button& button)override;

private:
    TemporaryID tempID_;
    std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> tempArgs_;
};

