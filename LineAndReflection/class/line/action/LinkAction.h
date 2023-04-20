#pragma once
#include "../../common/shape/Circle.h"
#include "../../common/Vector2.h"

class LinkAction
{
public:
    LinkAction();
    ~LinkAction();

    bool Act(const BaseLine& line, const Circle& circleA, const Circle& circleB)const;
};

