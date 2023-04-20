#pragma once
#include "../../common/Vector2.h"

class EncloseAction
{
public:
    EncloseAction(Vector2Dbl pos);
    ~EncloseAction();

    bool Act(const BaseLine& line)const;

private:
    Vector2Dbl targetPos_;
};

