#pragma once
#include "Temporary.h"
#include "../../UI/UICtrl.h"

class HowToPlay :
    public Temporary
{
public:
	HowToPlay(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::HowToPlayArgs> args);
	~HowToPlay();

private:
	void DrawOwnScreen(void) override;
	bool UpdateTemporary(double delta) override;

	void InitUI(void);		//UI�������p

	UICtrl uictrl_;			//UI�Ǘ�
	bool retFlg_;			//���̃V�[���ɖ߂邩
};

