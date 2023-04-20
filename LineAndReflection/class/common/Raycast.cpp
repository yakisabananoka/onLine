#include <algorithm>
#include <functional>
#include <array>
#include <map>
#include "Raycast.h"
#include "../../_debug/_DebugConOut.h"

ColPoint Raycast::CheckCollision(Ray ray, Rect col)const
{
    Line line;

    if (ray.vec.x < 0)
    {
        //左向き
        line = { col.GetRT(),col.GetRB() };
    }
    else if (ray.vec.x > 0)
    {
        //右向き
        line = { col.GetLT(),col.GetLB() };
    }
    else
    {
        if (ray.vec.y < 0)
        {
            //上向き
            line = { col.GetRB(),col.GetLB() };
        }
        else
        {
            //下向き
            line = { col.GetLT(),col.GetRT() };
        }
    }

    Vector2Dbl retPoint;
    bool retBool = CheckRay(ray, line, retPoint);

    return std::make_pair(retBool, retPoint);
}

ColPoint Raycast::CheckCollision(Ray ray, const double& size, const Rect& col)const
{
    //領域判定
    auto area = static_cast<Vector2>((((ray.p - col.pos) / col.size) + 1.0));
    std::array<int, 2> areaArray = { std::clamp(area.x, 0, 2),std::clamp(area.y, 0, 2) };

    //レイを飛ばす
    static auto convertCheckRay = [&](const Line& line) {
        Vector2Dbl colPos;
        bool retFlg = CheckRay(ray, line, colPos);
        return std::make_pair(retFlg, colPos);
    };

    //点と点の距離を計測する
    static auto checkDistance = [&](const Line& line) {
        Vector2Dbl colPos;
        bool retFlg = CheckRay(ray, line.p, size, colPos);
        return std::make_pair(retFlg, colPos);
    };

    //常にfalseを返す
    static auto retTrue = [&](const Line& line) {
        return std::make_pair(true, ray.p);
    };

    //領域に合わせて実行する式を変える
    std::map < std::array<int, 2>, std::pair< Line, std::function<ColPoint(const Line&) >>> areaMap = {
        {{0,0},std::make_pair(Line{col.GetLT(),col.GetLT()},checkDistance)},                                                    //左上
        {{1,0},std::make_pair(Line{col.GetLT() + Vector2Dbl(0.0,-size),col.GetRT() + Vector2Dbl(0.0,-size)},convertCheckRay)},  //中上
        {{2,0},std::make_pair(Line{col.GetRT(),col.GetRT()},checkDistance)},                                                    //右上
        {{0,1},std::make_pair(Line{col.GetLB() + Vector2Dbl(-size,0.0),col.GetLT() + Vector2Dbl(-size,0.0)},convertCheckRay)},  //左中
        {{1,1},std::make_pair(Line{col.GetCC(),col.GetCC()},retTrue)},                                                          //中央
        {{2,1},std::make_pair(Line{col.GetRT() + Vector2Dbl(size,0.0),col.GetRB() + Vector2Dbl(size,0.0)},convertCheckRay)},    //右中
        {{0,2},std::make_pair(Line{col.GetLB(),col.GetLB()},checkDistance)},                                                    //左下
        {{1,2},std::make_pair(Line{col.GetRB() + Vector2Dbl(0.0,size),col.GetLB() + Vector2Dbl(0.0,size)},convertCheckRay)},    //中下
        {{2,2},std::make_pair(Line{col.GetRB(),col.GetRB()},checkDistance)}                                                     //右下
    };

    //std::map < std::array<int, 2>, std::pair< Line, std::function<ColPoint(const Line&) >>> areaMap = {
    //       {{0,0},std::make_pair(Line{col.GetLT(),col.GetLT()},checkDistance)},      //左上
    //       {{1,0},std::make_pair(Line{col.GetLT(),col.GetRT()},convertCheckRay)},    //中上
    //       {{2,0},std::make_pair(Line{col.GetRT(),col.GetRT()},checkDistance)},      //右上
    //       {{0,1},std::make_pair(Line{col.GetLB(),col.GetLT()},convertCheckRay)},    //左中
    //       {{1,1},std::make_pair(Line{col.GetCC(),col.GetCC()},retTrue)},            //中央
    //       {{2,1},std::make_pair(Line{col.GetRT(),col.GetRB()},convertCheckRay)},    //右中
    //       {{0,2},std::make_pair(Line{col.GetLB(),col.GetLB()},checkDistance)},      //左下
    //       {{1,2},std::make_pair(Line{col.GetRB(),col.GetLB()},convertCheckRay)},    //中下
    //       {{2,2},std::make_pair(Line{col.GetRB(),col.GetRB()},checkDistance)}       //右下
    //};


    return areaMap[areaArray].second(areaMap[areaArray].first);
}

bool Raycast::CheckRay(Ray ray, Line line, Vector2Dbl& colPos)const
{
    Vector2Dbl v = line.p - ray.p;
    double crsRvLv = ray.vec.Cross(line.vec());
    if (crsRvLv == 0.0)
    {
        // 平行状態
        return false;
    }

    double crsVRv = v.Cross(ray.vec);
    double crsVLv = v.Cross(line.vec());

    double s = crsVLv / crsRvLv;
    double t = crsVRv / crsRvLv;

    if (s < 0.0 || s > 1.0 || t  < 0.0 || t  > 1.0)
    {
        // 交差していない
        return false;
    }

    colPos = ray.p + ray.vec * s;

    return true;
}

bool Raycast::CheckRay(Ray ray, Vector2Dbl pos, double size,Vector2Dbl& colPos)const
{
    // 半径がマイナスはエラー（半径ゼロは許容）
    if (size < 0.0)
    {
        return false;
    }

    if (ray.vec == Vector2Dbl())
    {
        return false;
    }

    // 円の中心点が原点になるように始点をオフセット
    ray.p -= pos;

    // レイの方向ベクトルを正規化
    ray.vec.Normalize();

    // 係数tを算出
    double dotAV = ray.p.Dot(ray.vec);
    double dotAA = ray.p.Dot(ray.p);
    double s = dotAV * dotAV - dotAA + size * size;

    if (s < 0.0)
    {
        return false; // 衝突していない
    }
        
    double sq = sqrt(s);
    double t1 = -dotAV - sq;
    double t2 = -dotAV + sq;

    // もしt1及びt2がマイナスだったら始点が
    // 円内にめり込んでいるのでエラーとする
    if (t1 < 0.0 || t2 < 0.0)
    {
        return false;
    }

    // 衝突座標を出力
    colPos = ray.p + t1 * ray.vec + pos;

    return true;
}

Vector2Dbl Raycast::CalcLineDist(Ray ray, Line line)const
{
    //点から線の中で最短の点を取得
    auto calcShortestVec = [](const Vector2Dbl& pos, const Line& line) {
        auto tVec = pos - line.p;
        auto lVec = line.vec();
        auto nLVec = lVec.Normalized();

        auto perQ = tVec.Dot(lVec) / lVec.SQMagnitude();
        perQ = std::clamp(perQ, 0.0, 1.0);

        return lVec * perQ + line.p - pos;
    };

    auto selectShortestVec = [](const Vector2Dbl& vecA, const Vector2Dbl& vecB) {
        return vecA.SQMagnitude() < vecB.SQMagnitude() ? vecA : vecB;
    };

    auto calcLineToLineVec = [&calcShortestVec, &selectShortestVec](const Line& baseLine, const Line& posLine) {

        Vector2Dbl pToBase = calcShortestVec(posLine.p, baseLine);
        Vector2Dbl eToBase = calcShortestVec(posLine.end, baseLine);

        return selectShortestVec(pToBase, eToBase);
    };

    Line rayLine = { ray.p,ray.p + ray.vec };

    double sqRaySize = ray.vec.SQMagnitude();
    double sqLineSize = line.vec().SQMagnitude();

    if (sqRaySize == 0.0)
    {
        if (sqLineSize == 0.0)
        {
            return ray.p - line.p;
        }

        return calcShortestVec(ray.p, line);
    }
    else
    {
        if (sqLineSize == 0.0)
        {
            return calcShortestVec(line.p, rayLine);
        }
    }

    Vector2Dbl colPos;
    if (CheckRay(ray, line, colPos))
    {
        return Vector2Dbl();
    }

    Vector2Dbl rayPosToLine = calcLineToLineVec(line, rayLine);
    Vector2Dbl linePosToRay = calcLineToLineVec(rayLine, line);

    return selectShortestVec(rayPosToLine, linePosToRay);
}
