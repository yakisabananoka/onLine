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

	void SetUI(UIPtr uiPtr);		//UI�̃Z�b�g�p
	UIList& GetUIList(void);		//UI�̃��X�g�̎擾�p

private:
	std::shared_ptr<Controller> controller_;		//�R���g���[���[
	UIList uiList_;									//UIObj�̃��X�g
};

