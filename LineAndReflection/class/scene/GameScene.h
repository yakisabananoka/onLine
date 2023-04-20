#pragma once
#include <vector>
#include "BaseScene.h"
#include "../obj/usingObj.h"
#include "../UI/UICtrl.h"

class Stage;
class LineCtrl;
class Camera;

namespace SceneArgsStruct
{
    struct GameArgs;
}

class GameScene :
    public BaseScene
{
public:
    GameScene(std::shared_ptr<SceneArgsStruct::GameArgs> args);
    ~GameScene();

    bool Init(void)override;
    bool InitUI(void);
    uniBaseScene Update(double delta, uniBaseScene ownScene)override;
    void DrawOwnScreen(void)override;

    void PlaySceneBGM(void)override;

private:
    std::shared_ptr<Camera> camera_;                        //�J����

    ObjList objList_;                                       //�I�u�W�F�N�g�i�[�p
    std::unique_ptr<LineCtrl> lineCtrl_;                    //���Ǘ��p�I�u�W�F�N�g
    std::shared_ptr<Stage> stage_;                          //�X�e�[�W

    UICtrl uiCtrl_;

    bool menuFlg_;
};

