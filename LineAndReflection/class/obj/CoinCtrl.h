#pragma once
#include "Obj.h"
#include "ObjType.h"

class CoinCtrl :
    public Obj
{
public:
    CoinCtrl(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~CoinCtrl();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::COIN_CTRL;
    }

    int GetMaxCoinCnt(void)const;

private:
    int maxCoinCnt_;        //‰½–‡‚ÌƒRƒCƒ“‚ğİ’è‚·‚é‚©
};

