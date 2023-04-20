#pragma once
#include "BaseScene.h"
#include "../UI/UICtrl.h"

namespace SceneArgsStruct
{
    struct TutorialCheckArgs;
}

class TutorialCheckScene :
    public BaseScene
{
public:
    TutorialCheckScene(std::shared_ptr<SceneArgsStruct::TutorialCheckArgs> args);
    ~TutorialCheckScene();

    bool Init(void)override;
    bool InitUI(void);
    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

private:
    UICtrl uiCtrl_;
};

