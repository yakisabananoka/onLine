#pragma once
#include <memory>
#include "BaseScene.h"
#include "../UI/UICtrl.h"

class Controller;

namespace SceneArgsStruct
{
    struct SelectArgs;
}

class SelectScene :
    public BaseScene
{
public:
    SelectScene(std::shared_ptr<SceneArgsStruct::SelectArgs> args);
    ~SelectScene();

    bool Init(void)override;
    bool InitUI(void);
    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

private:
    std::shared_ptr<Controller> controller_;

    UICtrl uiCtrl_;
};

