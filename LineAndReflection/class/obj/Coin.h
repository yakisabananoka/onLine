#pragma once
#include "Obj.h"
#include "ObjType.h"
#include "../common/shape/Rect.h"

class ItemEffect;

class Coin :
    public Obj
{
public:
    Coin(std::weak_ptr<Camera> camera, Rect range, int id, int chipId);
    ~Coin();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::COIN;
    }

private:
    Rect range_;                                //範囲
    std::unique_ptr<ItemEffect> effectPtr_;     //エフェクト
    std::string cnt_;                           //自分が何番目か

    int chipId_;                                //描画するID
};

