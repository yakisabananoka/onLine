#pragma once
#include <functional>
#include <sstream>
#include "BaseUI.h"

using InfoMesCommandPtr = std::function<void(std::stringstream&)>;

class InfoMessage :
    public BaseUI
{
public:
    InfoMessage(Vector2Dbl pos);
    ~InfoMessage();

    void Init(void)override;
    void Update(double delta)override;
    void Draw(void)override;

    UIType GetUIType(void)override
    {
        return UIType::InfoMes;
    }

    void SetCommand(InfoMesCommandPtr command);       //�펞���s����R�}���h�̃Z�b�g

private:
    InfoMesCommandPtr command_;                       //�펞���s����R�}���h

    std::stringstream buffer_;
};

