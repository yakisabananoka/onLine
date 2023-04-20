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

	void InitUI(void);		//UI‰Šú‰»—p

	UICtrl uictrl_;			//UIŠÇ—
	bool retFlg_;			//Œ³‚ÌƒV[ƒ“‚É–ß‚é‚©
};

