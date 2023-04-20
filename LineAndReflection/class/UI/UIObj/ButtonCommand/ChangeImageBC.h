#pragma once
#include <string>
#include "ButtonCommand.h"

class ChangeImageBC :
    public ButtonCommand
{
public:
    ChangeImageBC(std::string imageKey);
    ~ChangeImageBC();

    void Execute(Button& button)override;
private:
    std::string imageKey_;

};

