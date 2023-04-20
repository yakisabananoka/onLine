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

    void SetImage(std::string imageKey);            //�摜�̃L�[�̃Z�b�g
    void SetCC(Vector2Dbl pos);                     //���S�ʒu�̃Z�b�g

    void SetCommand(IPCommandPtr command);          //�펞���s����R�}���h�̃Z�b�g

private:
    std::string imageKey_;                          //�摜�̃L�[

    IPCommandPtr command_;                          //�펞���s����R�}���h
};

