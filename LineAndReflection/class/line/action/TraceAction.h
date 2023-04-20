#pragma once
#include "../usingLine.h"

class TraceAction
{
public:
    TraceAction();
    ~TraceAction();

    bool Act(const BaseLine& line,const BaseLine& foundLine)const;
};

