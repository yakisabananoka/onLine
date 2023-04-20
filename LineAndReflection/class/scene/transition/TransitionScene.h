#pragma once
#include "../BaseScene.h"

enum class Transition
{
	CrossOver,
	Page,
	MAX
};

class TransitionScene :
	public BaseScene
{
public:
	TransitionScene(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> args);
	~TransitionScene();

private:
	virtual bool UpdateTransition(double delta) = 0;

	uniBaseScene Update(double delta, uniBaseScene ownScene) override;
	bool Init(void) override;

protected:
	uniBaseScene beforeScene_;		//前のシーン
	uniBaseScene nextScene_;		//次のシーン

};

