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

	UICtrl uiCtrl_;		//UI管理用
	bool retFlg_;		//元のシーンに戻るか
};

