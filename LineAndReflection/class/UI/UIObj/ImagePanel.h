#pragma once
#include <memory>
#include <string>
#include "BaseUI.h"
#include "ImagePanelCommand/ImagePanelCommand.h"
#include "../../common/shape/Rect.h"

class ImagePanel :
    public BaseUI
{
public:
    ImagePanel(Rect range);
    ImagePanel(Vector2Dbl pos, std::string imageKey);
    ~ImagePanel();

    void Init(void)override;
    void Update(double delta)override;
    void Draw(void)override;

    UIType GetUIType(void)override
    {
        return UIType::ImagePanel;
    }

    void SetImage(std::string imageKey);            //画像のキーのセット
    void SetCC(Vector2Dbl pos);                     //中心位置のセット

    void SetCommand(IPCommandPtr command);          //常時実行するコマンドのセット

private:
    std::string imageKey_;                          //画像のキー

    IPCommandPtr command_;                          //常時実行するコマンド
};

