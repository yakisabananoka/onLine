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

	UICtrl uictrl_;		//UI管理用
	bool retFlg_;		//元のシーンに戻るか
};

