#pragma once
#include <string>
#include "Button.h"

class NormalButton :
    public Button
{
public:
    NormalButton(Vector2Dbl ccPos, const std::string& text, const std::string& fontKey,unsigned int textColor,unsigned int edgeColor,
        const std::string& normalImage, const std::string& hoverImage, const std::string& clickImage, ButtonCommandPtr command, Vector2Dbl clickOffset = {});
    ~NormalButton();

private:

};

