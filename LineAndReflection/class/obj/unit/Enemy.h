#pragma once
#include "Unit.h"
#include "../ObjType.h"
#include "../../common/shape/Circle.h"

class Enemy :
    public Unit
{
public:
    Enemy(std::weak_ptr<Camera> camera, Vector2Dbl pos, double size, int id, double gravity, double maxSpeed);
    ~Enemy();

    void Init(void) override;

    bool Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override final;
    virtual bool EnemyMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage) = 0;
    virtual void ColMotion(double delta, ObjPtr& colObj) {}
    bool IsTouchTrampoline(void)override { return false; }

    ObjType GetObjType(void)const override
    {
        return ObjType::ENEMY;
    }

private:
};

