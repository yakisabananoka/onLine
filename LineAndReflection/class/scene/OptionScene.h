#pragma once
#include "BaseScene.h"
#include "../UI/UICtrl.h"

namespace SceneArgsStruct
{
    struct OptionArgs;
}

class Button;
class RadioButton;

class OptionScene :
    public BaseScene
{
public:
    OptionScene(std::shared_ptr<SceneArgsStruct::OptionArgs> args);
    ~OptionScene();

    bool Init(void)override;
    bool InitUI(void);

    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

private:
    UICtrl uiCtrl_;
};

