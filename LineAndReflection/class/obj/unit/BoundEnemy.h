#pragma once
#include "Enemy.h"

class BoundEnemy :
    public Enemy
{
public:
    BoundEnemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~BoundEnemy();

    void Draw(void) override;

    bool EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;

private:
    bool reverseFlg_;       //”½“]•`‰æƒtƒ‰ƒO
};

