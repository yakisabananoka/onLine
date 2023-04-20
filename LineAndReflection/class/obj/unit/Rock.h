#pragma once
#include "Enemy.h"

class Rock :
    public Enemy
{
public:
    Rock(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~Rock();

    void Draw(void) override;

    bool EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void ColMotion(double delta, ObjPtr& colObj)override;
    bool DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;

private:
    double rotaAngle_;      //回転量
    double rotaSpeed_;      //回転スピード
    int expId_;             //爆発画像のハンドル
};

