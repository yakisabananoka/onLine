#pragma once
#include "TransitionScene.h"
class FadeM :
    public TransitionScene
{
public:
	FadeM(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::FadeMArgs> args);
	~FadeM();

private:
	void DrawOwnScreen(void) override;		//TransitionScene�N���X�ɖ����Ă�����
	bool UpdateTransition(double delta) override;

	int count_;						//�J�E���g�l

	std::string missionPath_;		//�~�b�V�������e�̃p�X
};

