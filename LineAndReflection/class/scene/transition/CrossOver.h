#pragma once
#include "TransitionScene.h"
class CrossOver :
	public TransitionScene
{
public:
	CrossOver(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::CrossOverArgs> args);
	~CrossOver();

private:
	void DrawOwnScreen(void) override;		//TransitionScene�N���X�ɖ����Ă�����
	bool UpdateTransition(double delta) override;

	int count_;		//�J�E���g�l

};

