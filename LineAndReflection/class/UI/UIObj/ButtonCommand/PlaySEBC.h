#pragma once
#include <string>
#include "ButtonCommand.h"

class PlaySEBC :
    public ButtonCommand
{
public:
    PlaySEBC(std::string soundKey);
    ~PlaySEBC();

    void Execute(Button& button)override;
private:
    std::string soundKey_;
};

