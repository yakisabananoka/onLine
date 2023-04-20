#pragma once
#include "TransitionScene.h"
class CrossOver :
	public TransitionScene
{
public:
	CrossOver(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::CrossOverArgs> args);
	~CrossOver();

private:
	void DrawOwnScreen(void) override;		//TransitionSceneクラスに無くてもいい
	bool UpdateTransition(double delta) override;

	int count_;		//カウント値

};

