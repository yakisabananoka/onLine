#pragma once
#include "TransitionScene.h"
class FadeIO :
	public TransitionScene
{
public:
	FadeIO(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::FadeIOArgs> args);
	~FadeIO();

private:
	void DrawOwnScreen(void) override;		//TransitionSceneクラスに無くてもいい
	bool UpdateTransition(double delta) override;

	int count_;		//カウント値

};

