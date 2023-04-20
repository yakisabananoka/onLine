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
    std::shared_ptr<Camera> camera_;                        //カメラ

    ObjList objList_;                                       //オブジェクト格納用
    std::unique_ptr<LineCtrl> lineCtrl_;                    //線管理用オブジェクト
    std::shared_ptr<Stage> stage_;                          //ステージ

    UICtrl uiCtrl_;

    bool menuFlg_;
};

