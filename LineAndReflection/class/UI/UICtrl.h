#pragma once
#include "usingUI.h"

class Controller;

class UICtrl
{
public:
	UICtrl();
	~UICtrl();

	bool Init(void);
	void Update(double delta);
	void Draw(void);

	void SetUI(UIPtr uiPtr);		//UIのセット用
	UIList& GetUIList(void);		//UIのリストの取得用

private:
	std::shared_ptr<Controller> controller_;		//コントローラー
	UIList uiList_;									//UIObjのリスト
};

