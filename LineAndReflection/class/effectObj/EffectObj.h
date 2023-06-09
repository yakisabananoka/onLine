#pragma once
#include <memory>
#include <string>
#include "EffectInfo.h"
#include "../common/Vector2.h"

class EffectObj
{
public:
	EffectObj(std::unique_ptr<EffectInfo> effectInfo);
	~EffectObj();

	void Update(double delta);					//更新
	void Draw(const Vector2Dbl& offset);		//描画

	bool IsAlive(void)const;					//生きているか否か

private:
	std::unique_ptr<EffectInfo> effectInfo_;

};

