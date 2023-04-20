#pragma once
#include <memory>
#include "Unit.h"
#include "../ObjType.h"
#include "../../common/Easing.h"
#include "../../common/shape/Circle.h"

class Controller;

class Player :
    public Unit
{
public:
    Player(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~Player();

    void Init(void) override;
    void Draw(void) override;

    bool Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    bool DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    bool DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;

    ObjType GetObjType(void)const override
    {
        return ObjType::PLAYER;
    }

    void SetInitPos(const Vector2Dbl& pos);         //初期位置設定

private:
    void DrawBarrier(int num, double angle);        //バリアの描画

    std::shared_ptr<Controller> controller_;        //コントローラー

    std::unique_ptr<Vector2Dbl> dethPos_;           //死亡位置
    std::unique_ptr<Vector2Dbl> initPos_;           //初期位置

    Easing easing_;             //イージング用

    Vector2Dbl oldPos_;         //前フレーム位置
    Vector2Dbl corePos_;        //中心位置
    Vector2Dbl coreVec_;        //中心ベクトル

    double inviTime_;           //透過時間
    
};

