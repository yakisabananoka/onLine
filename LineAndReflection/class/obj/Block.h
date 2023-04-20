#pragma once
#include "Obj.h"
#include "ObjType.h"
#include "../common/shape/Rect.h"

class Block :
    public Obj
{
public:
    enum class State
    {
        Normal,
        Destroy
    };

    Block(std::weak_ptr<Camera> camera, Rect range, int id);
    ~Block();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::BLOCK;
    }

private:
    Rect range_;        //”ÍˆÍ


};

