#pragma once
#include "EffectCommand.h"
class FadeOut :
    public EffectCommand
{
public:
    FadeOut(double time);
    ~FadeOut();

    void Execute(EffectInfo& info)override;

private:
    double time_;
};

