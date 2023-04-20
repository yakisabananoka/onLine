#include <DxLib.h>
#include "../common/ImageMng.h"
#include "EffectObj.h"

EffectObj::EffectObj(std::unique_ptr<EffectInfo> effectInfo):
    effectInfo_(std::move(effectInfo))
{
}

EffectObj::~EffectObj()
{
}

void EffectObj::Update(double delta)
{
    effectInfo_->pos += effectInfo_->move.speed * delta * effectInfo_->vec;
    effectInfo_->angle += effectInfo_->rota.speed * delta;
    effectInfo_->mag += effectInfo_->exAmount.speed * delta;
    effectInfo_->blend += effectInfo_->blendAmount.speed * delta;

    effectInfo_->move.Update(delta);
    effectInfo_->rota.Update(delta);
    effectInfo_->exAmount.Update(delta);
    effectInfo_->blendAmount.Update(delta);

    effectInfo_->lifeTime -= delta;

    if (effectInfo_->command == nullptr)
    {
        return;
    }

    effectInfo_->command->Execute(*effectInfo_);
}

void EffectObj::Draw(const Vector2Dbl& offset)
{
    SetDrawBlendMode(effectInfo_->blendMode, static_cast<int>(effectInfo_->blend));
    SetDrawBright(effectInfo_->r, effectInfo_->g, effectInfo_->b);

    DrawRotaGraph(
        static_cast<int>(offset.x + effectInfo_->pos.x), static_cast<int>(offset.y + effectInfo_->pos.y),
        effectInfo_->mag, effectInfo_->angle, lpImageMng.GetID(effectInfo_->imageKey)[0], true
    );

    SetDrawBright(255, 255, 255);
    SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

bool EffectObj::IsAlive(void)const
{
    return effectInfo_->lifeTime > 0.0;
}
