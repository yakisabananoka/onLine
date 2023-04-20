#pragma once
#include "Temporary.h"
#include "../../UI/UICtrl.h"

class OptionMenu :
    public Temporary
{
public:
	OptionMenu(uniBaseScene beforeScene, std::shared_ptr<SceneArgsStruct::Temporary::OptionMenuArgs> args);
	~OptionMenu();

private:
	void DrawOwnScreen(void) override;
	bool UpdateTemporary(double delta) override;

	void InitUI(void);

	UICtrl uiCtrl_;		//UIä«óùóp
	bool retFlg_;		//å≥ÇÃÉVÅ[ÉìÇ…ñﬂÇÈÇ©
};

