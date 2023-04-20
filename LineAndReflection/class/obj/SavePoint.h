#pragma once
#include <memory>
#include "Obj.h"
#include "ObjType.h"
#include "../common/shape/Rect.h"

class ItemEffect;

class SavePoint :
    public Obj
{
public:
    SavePoint(std::weak_ptr<Camera> camera, Rect range, int id);
    ~SavePoint();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::SAVE_POINT;
    }

private:
    Rect range_;                                //範囲
    std::unique_ptr<ItemEffect> effectPtr_;     //エフェクト
};

