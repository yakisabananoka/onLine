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

	uniBaseScene Update(double delta, uniBaseScene ownScene) override;			//�X�V
	bool Init(void) override;													//������

protected:
	uniBaseScene beforeScene_;		//�O�̃V�[��

};

