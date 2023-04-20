#include <DxLib.h>
#include "../../common/ImageMng.h"
#include "FadeM.h"

namespace fadeM_const
{
	//constexpr char missionPath[] = "data/image/mission_bg.png";
}

using namespace fadeM_const;

FadeM::FadeM(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::FadeMArgs> args)
	:TransitionScene(std::move(beforeScene), std::move(nextScene), args),missionPath_(args->fadeImagePath)
{
	count_ = 0;
	nextScene_->DrawOwnScreen();
	DrawOwnScreen();

	lpImageMng.GetID(missionPath_);
}

FadeM::~FadeM()
{
}

void FadeM::DrawOwnScreen(void)
{
	SetDrawScreen(scrID_);
	ClsDrawScreen();
	if (count_ < 256)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255 - count_);
		beforeScene_->Draw();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_);
		DrawGraph(0, 0, lpImageMng.GetID(missionPath_)[0], false);
	}
	else if (count_ < 512)
	{
		DrawGraph(0, 0, lpImageMng.GetID(missionPath_)[0], false);
	}
	else
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 768 - count_);
		DrawGraph(0, 0, lpImageMng.GetID(missionPath_)[0], false);

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, count_ - 511);
		nextScene_->Draw();
	}

	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool FadeM::UpdateTransition(double delta)
{
	DrawOwnScreen();

	count_ += 3;
	return (count_ > 768);
}
