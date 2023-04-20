#pragma once
#include <functional>
#include "GaugeCommand.h"

using CallbackGCFunc = std::function<void(Gauge&)>;

class GaugeCommandFunc :
    public GaugeCommand
{
public:
    GaugeCommandFunc(CallbackGCFunc func);
    ~GaugeCommandFunc();

    void Execute(Gauge& gauge);

private:
    CallbackGCFunc func_;
};

