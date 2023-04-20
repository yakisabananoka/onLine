#pragma once
#include <random>
#include "Obj.h"
#include "ObjType.h"

class Camera;

class RockSetter :
    public Obj
{
public:
    RockSetter(std::weak_ptr<Camera> camera, Vector2Dbl pos, double minX, double maxX, double genTime, int id);
    ~RockSetter();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::ROCK_SETTER;
    }

private:
    std::mt19937 randomGen_;                    //乱数生成
    std::uniform_real_distribution<> range_;    //乱数の生成範囲

    Vector2Dbl offset_;     //オフセット値
    double time_;           //経過時間
    double genTime_;        //生成の間隔時間
};

