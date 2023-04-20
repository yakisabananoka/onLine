#pragma once
#include <functional>
#include "ButtonCommand.h"

using CallbackFunc = std::function<void(Button&)>;

class ButtonCommandFunc :
    public ButtonCommand
{
public:
    ButtonCommandFunc(CallbackFunc func);
    ~ButtonCommandFunc();

    void Execute(Button& button)override;

private:
    CallbackFunc func_;

};

