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
        Vector2Dbl inVec;       //入射方向の単位ベクトル
        double inPow;           //入射の強さ
        double dir;             //方向
        int objId;              //オブジェクトのID
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
    void SetSplitHalfVec(const Circle& circle, const Vector2Dbl& firstPos, const Vector2Dbl& secondPos, int cnt);           //線の分割
    Vector2Dbl GetOneTanPnt(const Circle& circle, const Vector2Dbl& point, const Vector2Dbl& dirVec)const;                  //タンジェントの位置取得
    std::pair<Vector2Dbl, Vector2Dbl> CalcTanPnt(const Circle& circle, const Vector2Dbl& point)const;                       //タンジェントの計算

    Vector2Dbl GetRefVec(const Vector2Dbl& dirVec)const;            //反射ベクトルの取得

    Vector2Dbl firstPos_;               //始点
    Vector2Dbl endPos_;                 //終点

    std::unique_ptr<TouchInfo> touchInfo_;     //接触情報
};

