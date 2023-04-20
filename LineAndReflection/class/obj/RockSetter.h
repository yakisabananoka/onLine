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
    std::mt19937 randomGen_;                    //��������
    std::uniform_real_distribution<> range_;    //�����̐����͈�

    Vector2Dbl offset_;     //�I�t�Z�b�g�l
    double time_;           //�o�ߎ���
    double genTime_;        //�����̊Ԋu����
};

