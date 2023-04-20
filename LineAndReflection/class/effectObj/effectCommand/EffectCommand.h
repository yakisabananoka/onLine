#pragma once

struct EffectInfo;

class EffectCommand
{
public:
	EffectCommand() {};
	~EffectCommand() {};

	virtual void Execute(EffectInfo& info) = 0;
};

