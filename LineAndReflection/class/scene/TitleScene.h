#pragma once
#include <memory>
#include "BaseScene.h"
#include "../UI/UICtrl.h"

class Controller;

namespace SceneArgsStruct
{
    struct TitleArgs;
}

class TitleScene :
    public BaseScene
{
public:
    TitleScene(std::shared_ptr<SceneArgsStruct::TitleArgs> args);
    ~TitleScene();

    bool Init(void)override;
    bool InitUI(void);
    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

    void PlaySceneBGM(void)override;

private:
    std::shared_ptr<Controller> controller_;

    UICtrl uiCtrl_;

    std::unique_ptr<BaseScene> gameScene_;
};

