#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "ImagePanel.h"

ImagePanel::ImagePanel(Rect range):
	BaseUI(range)
{
}

ImagePanel::ImagePanel(Vector2Dbl pos, std::string imageKey) :
	BaseUI({ pos,Vector2Dbl() }), imageKey_(imageKey)
{
	lpImageMng.GetID(imageKey_);
	range_.size = static_cast<Vector2Dbl>(lpImageMng.GetSize(imageKey_));
}

ImagePanel::~ImagePanel()
{
}

void ImagePanel::Init(void)
{
}

void ImagePanel::Update(double delta)
{
	if (command_ == nullptr)
	{
		return;
	}

	command_->Execute(*this);
}

void ImagePanel::Draw(void)
{
	DrawGraph(
		static_cast<int>(range_.pos.x),
		static_cast<int>(range_.pos.y),
		lpImageMng.GetID(imageKey_)[0], true
	);
}

void ImagePanel::SetImage(std::string imageKey)
{
	imageKey_ = imageKey;
	range_.size = static_cast<Vector2Dbl>(lpImageMng.GetSize(imageKey));
}

void ImagePanel::SetCC(Vector2Dbl pos)
{
	range_.SetFixedCC(pos);
}

void ImagePanel::SetCommand(IPCommandPtr command)
{
	command_ = std::move(command);
}
