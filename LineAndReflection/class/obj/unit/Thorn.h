#pragma once
#include "../Obj.h"
#include "../ObjType.h"

class Thorn :
    public Obj
{
public:
    Thorn(std::weak_ptr<Camera> camera, Vector2Dbl pos, int id);
    ~Thorn();

    void Init(void) override;
    void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage)override;
    void Draw(void) override;

    ObjType GetObjType(void)const override
    {
        return ObjType::DOOR;
    }
};

