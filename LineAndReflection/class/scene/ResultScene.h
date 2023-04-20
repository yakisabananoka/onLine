#pragma once
#include <memory>
#include "BaseScene.h"
#include "../UI/UICtrl.h"

namespace SceneArgsStruct
{
    struct ResultArgs;
}

class ResultScene :
    public BaseScene
{
public:
    ResultScene(std::shared_ptr<SceneArgsStruct::ResultArgs> args);
    ~ResultScene();

    bool Init(void)override;
    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

private:
    void InitUI(void);

    void PlaySceneBGM(void)override;

    std::shared_ptr<Controller> controller_;

    UICtrl uiCtrl_;

    double cntTime_;            //Œo‰ßŠÔ
    double totalLineDist_;      //ü‚Ì‹——£‚Ì‡Œv

};

