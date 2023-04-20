#pragma once
#include <utility>
#include "BaseLine.h"

struct Circle;

class Trampoline :
    public BaseLine
{
public:
    struct TouchInfo
    {
        TouchInfo(Vector2Dbl inVec, double inPow, double dir, int objId) :
            inVec(inVec), inPow(inPow), dir(dir), objId(objId) {}
        Vector2Dbl inVec;       //���˕����̒P�ʃx�N�g��
        double inPow;           //���˂̋���
        double dir;             //����
        int objId;              //�I�u�W�F�N�g��ID
    };

    Trampoline(std::weak_ptr<Camera> camera, unsigned int color);
    ~Trampoline();

    bool SplitInit(void);

    void Update(double delta)override {};
    void UpdateAfterObj(double delta, ObjList& objList)override;

    void SetPoint(Vector2Dbl pos)override;
    void EndDrawingLine(void)override;

    bool HasCollision(void)override;

private:
    void SetSplitHalfVec(const Circle& circle, const Vector2Dbl& firstPos, const Vector2Dbl& secondPos, int cnt);           //���̕���
    Vector2Dbl GetOneTanPnt(const Circle& circle, const Vector2Dbl& point, const Vector2Dbl& dirVec)const;                  //�^���W�F���g�̈ʒu�擾
    std::pair<Vector2Dbl, Vector2Dbl> CalcTanPnt(const Circle& circle, const Vector2Dbl& point)const;                       //�^���W�F���g�̌v�Z

    Vector2Dbl GetRefVec(const Vector2Dbl& dirVec)const;            //���˃x�N�g���̎擾

    Vector2Dbl firstPos_;               //�n�_
    Vector2Dbl endPos_;                 //�I�_

    std::unique_ptr<TouchInfo> touchInfo_;     //�ڐG���
};

