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

	void Update(double delta);					//XV
	void Draw(const Vector2Dbl& offset);		//•`‰æ

	bool IsAlive(void)const;					//¶‚«‚Ä‚¢‚é‚©”Û‚©

private:
	std::unique_ptr<EffectInfo> effectInfo_;

};

