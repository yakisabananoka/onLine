#include "ImagePanelCommandFunc.h"

ImagePanelCommandFunc::ImagePanelCommandFunc(CallbackIPCFunc func) :
	func_(func)
{
}

ImagePanelCommandFunc::~ImagePanelCommandFunc()
{
}

void ImagePanelCommandFunc::Execute(ImagePanel& imagePanel)
{
	func_(imagePanel);
}
