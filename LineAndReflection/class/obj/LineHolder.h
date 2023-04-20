#pragma once
#include <memory>
#include <string>
#include <unordered_map>
#include "Obj.h"
#include "ObjType.h"
#include "../line/usingLine.h"
#include "../line/generator/LineGenerator.h"
#include "../line/action/LinkAction.h"
#include "../common/shape/Circle.h"

class Camera;
class Controller;

class LineHolder :
    public Obj
{
public:
    LineHolder(std::weak_ptr<Camera> camera, Vector2Dbl posA, Vector2Dbl posB, int id, std::string lineType);
    ~LineHolder();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::LINE_HOLDER;
    }

private:
    LinePtr line_;                          //保持するライン
    LinkAction linkAction_;                 //繋げたことで発生するアクション
    LineGenerator generator_;               //線のジェネレーター

    std::string lineType_;                  //線の種類

    Circle circleA_;                        //保持端点
    Circle circleB_;                        //保持端点

    std::shared_ptr<Controller> controller_;        //コントローラー
};

