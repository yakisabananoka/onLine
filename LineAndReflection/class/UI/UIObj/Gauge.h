#pragma once
#include <memory>
#include <functional>
#include "BaseUI.h"

class GaugeCommand;

class Gauge :
    public BaseUI
{
public:
    Gauge(Rect rect, double thick, unsigned int color, unsigned edgeColor);
    ~Gauge();

    void Init(void)override;
    void Update(double delta)override;
    void Draw(void)override;

    UIType GetUIType(void)override
    {
        return UIType::Gauge;
    }

    void SetCommand(std::unique_ptr<GaugeCommand> command);       //常時実行するコマンドのセット
    void SetValue(double value);
    void SetColor(unsigned int color);
    void SetCC(Vector2Dbl pos);
    void SetDrawFlg(bool flg);

private:
    std::unique_ptr<GaugeCommand> command_;                       //常時実行するコマンド

    unsigned int color_;
    unsigned int edgeColor_;
    double thick_;
    double value_;
    bool drawFlg_;
};

