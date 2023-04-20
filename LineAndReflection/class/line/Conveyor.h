#pragma once
#include "BaseLine.h"
class Conveyor :
    public BaseLine
{
public:
    Conveyor(std::weak_ptr<Camera> camera, unsigned int color);
    ~Conveyor();

    void Update(double delta)override;
    void UpdateAfterObj(double delta, ObjList& objList)override;

    void SetPoint(Vector2Dbl pos)override;
    void EndDrawingLine(void)override;

    bool HasCollision(void)override;

private:

};

