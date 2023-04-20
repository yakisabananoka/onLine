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

	void Update(double delta);					//�X�V
	void Draw(const Vector2Dbl& offset);		//�`��

	bool IsAlive(void)const;					//�����Ă��邩�ۂ�

private:
	std::unique_ptr<EffectInfo> effectInfo_;

};

