#pragma once
#include "Enemy.h"

class RunEnemy :
    public Enemy
{
public:
    RunEnemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~RunEnemy();

    void Draw(void) override;

    bool EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;

private:
    Vector2Dbl oldPos_;     //�O�t���[���ʒu
    bool reverseFlg_;       //���]�`��t���O
};

