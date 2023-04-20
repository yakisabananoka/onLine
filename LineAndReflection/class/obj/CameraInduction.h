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

    Easing easing_;                 //�C�[�W���O�p�֐�

    const Vector2Dbl start_;        //�n�_
    const Vector2Dbl end_;          //�I�_

    const double moveTime_;         //�ړ�����
    const double waitTime_;         //�ҋ@����

    const int parentID_;            //�eObj��ID

    double time_;                   //�o�ߎ���
};

