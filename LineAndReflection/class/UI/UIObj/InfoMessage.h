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

    void SetCommand(InfoMesCommandPtr command);       //常時実行するコマンドのセット

private:
    InfoMesCommandPtr command_;                       //常時実行するコマンド

    std::stringstream buffer_;
};

