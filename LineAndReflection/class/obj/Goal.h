#pragma once
#include "Obj.h"
#include "ObjType.h"

class Goal :
    public Obj
{
public:
    Goal(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~Goal();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::GOAL;
    }

private:
    Vector2Dbl size_;       //ÉTÉCÉY

};

