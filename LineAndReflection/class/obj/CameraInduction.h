#pragma once
#include "Obj.h"
#include "ObjType.h"
#include "../common/Easing.h"
#include "../common/Vector2.h"

class Controller;

class CameraInduction :
    public Obj
{
public:
    CameraInduction(std::weak_ptr<Camera> camera, Vector2Dbl start, Vector2Dbl end, double moveTime, double waitTime, int parentID);
    ~CameraInduction();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::CAMERA_INDUCTION;
    }

private:
    bool Move(const Vector2Dbl& start, const Vector2Dbl& end, double nowTime);

    std::shared_ptr<Controller> controller_;

    Easing easing_;                 //イージング用関数

    const Vector2Dbl start_;        //始点
    const Vector2Dbl end_;          //終点

    const double moveTime_;         //移動時間
    const double waitTime_;         //待機時間

    const int parentID_;            //親ObjのID

    double time_;                   //経過時間
};

