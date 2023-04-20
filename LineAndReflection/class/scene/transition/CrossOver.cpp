#include <algorithm>
#include <DxLib.h>
#include "CrossOver.h"

CrossOver::CrossOver(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::CrossOverArgs> args)
	:TransitionScene(std::move(beforeScene), std::move(nextScene), args)
{
	count_ = 0;
	DrawOwnScreen();
}

CrossOver::~CrossOver()
{
}

void CrossOver::DrawOwnScreen(void)
{
	SetDrawScreen(scrID_);
	ClsDrawScreen();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
	beforeScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
	nextScene_->Draw();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool CrossOver::UpdateTransition(double delta)
{
	DrawOwnScreen();
	return (++count_ > 255);
}
