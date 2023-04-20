#pragma once
#include <memory>

class ImagePanel;
class ImagePanelCommand;

using IPCommandPtr = std::unique_ptr<ImagePanelCommand>;

class ImagePanelCommand
{
public:
	ImagePanelCommand() {};
	~ImagePanelCommand() {};

	virtual void Execute(ImagePanel& imagePanel) = 0;

};

