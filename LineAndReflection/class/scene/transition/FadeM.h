#pragma once
#include "TransitionScene.h"
class FadeM :
    public TransitionScene
{
public:
	FadeM(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::FadeMArgs> args);
	~FadeM();

private:
	void DrawOwnScreen(void) override;		//TransitionSceneクラスに無くてもいい
	bool UpdateTransition(double delta) override;

	int count_;						//カウント値

	std::string missionPath_;		//ミッション内容のパス
};

