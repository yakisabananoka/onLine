#pragma once
#include <functional>
#include "ImagePanelCommand.h"

using CallbackIPCFunc = std::function<void(ImagePanel&)>;

class ImagePanelCommandFunc :
    public ImagePanelCommand
{
public:
    ImagePanelCommandFunc(CallbackIPCFunc func);
    ~ImagePanelCommandFunc();

    void Execute(ImagePanel& imagePanel);

private:
    CallbackIPCFunc func_;

};

