#pragma once
#include "Temporary.h"
#include "../../UI/UICtrl.h"

class PlayMenu :
    public Temporary
{
public:
	PlayMenu(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::PlayMenuArgs> args);
	~PlayMenu();

private:
	void DrawOwnScreen(void) override;
	bool UpdateTemporary(double delta) override;

	void InitUI(void);

	UICtrl uictrl_;		//UIŠÇ——p
	bool retFlg_;		//Œ³‚ÌƒV[ƒ“‚É–ß‚é‚©
};

