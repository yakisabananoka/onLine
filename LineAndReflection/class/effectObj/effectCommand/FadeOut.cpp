#include <DxLib.h>
#include "FadeOut.h"
#include "../EffectInfo.h"

FadeOut::FadeOut(double time):
	time_(time)
{
}

FadeOut::~FadeOut()
{
}

void FadeOut::Execute(EffectInfo& info)
{
	if (info.lifeTime < time_)
	{
		info.blendMode = DX_BLENDGRAPHTYPE_ALPHA;
		info.blend = (info.lifeTime / time_) * 255.0;
	}
}
