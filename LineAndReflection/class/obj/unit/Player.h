#pragma once
#include <memory>
#include "Unit.h"
#include "../ObjType.h"
#include "../../common/Easing.h"
#include "../../common/shape/Circle.h"

class Controller;

class Player :
    public Unit
{
public:
    Player(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~Player();

    void Init(void) override;
    void Draw(void) override;

    bool Motion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    bool DeathMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    bool DamagedMotion(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;

    ObjType GetObjType(void)const override
    {
        return ObjType::PLAYER;
    }

    void SetInitPos(const Vector2Dbl& pos);         //�����ʒu�ݒ�

private:
    void DrawBarrier(int num, double angle);        //�o���A�̕`��

    std::shared_ptr<Controller> controller_;        //�R���g���[���[

    std::unique_ptr<Vector2Dbl> dethPos_;           //���S�ʒu
    std::unique_ptr<Vector2Dbl> initPos_;           //�����ʒu

    Easing easing_;             //�C�[�W���O�p

    Vector2Dbl oldPos_;         //�O�t���[���ʒu
    Vector2Dbl corePos_;        //���S�ʒu
    Vector2Dbl coreVec_;        //���S�x�N�g��

    double inviTime_;           //���ߎ���
    
};

