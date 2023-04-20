#pragma once
#include "../BaseScene.h"

class Temporary :
    public BaseScene
{
public:
	Temporary(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> args);
	~Temporary();

private:
	virtual bool UpdateTemporary(double delta) = 0;

	uniBaseScene Update(double delta, uniBaseScene ownScene) override;			//更新
	bool Init(void) override;													//初期化

protected:
	uniBaseScene beforeScene_;		//前のシーン

};

