#include <DxLib.h>
#include "FadeIO.h"

FadeIO::FadeIO(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::FadeIOArgs> args)
	:TransitionScene(std::move(beforeScene), std::move(nextScene), args)
{
	count_ = 0;
	nextScene_->DrawOwnScreen();
	DrawOwnScreen();
}

FadeIO::~FadeIO()
{
}

void FadeIO::DrawOwnScreen(void)
{
	SetDrawScreen(scrID_);
	ClsDrawScreen();
	if (count_ < 256)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
		beforeScene_->Draw();
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_ - 255);
		nextScene_->Draw();
	}
	
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool FadeIO::UpdateTransition(double delta)
{
	DrawOwnScreen();

	count_ += 5;
	return (count_ > 512);
}
