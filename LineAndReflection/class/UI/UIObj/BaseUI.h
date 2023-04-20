#pragma once
#include <memory>
#include "../UIType.h"
#include "../../common/shape/Rect.h"

class Controller;

class BaseUI
{
public:
	BaseUI(Rect range);
	virtual ~BaseUI();

	virtual void Init(void) = 0;
	virtual void Update(double delta) = 0;
	virtual void SpotUpdate(std::shared_ptr<Controller> controller);		//�̈���Ƀ}�E�X�������Ă���ԏ�̏ꍇ�Ɏ��s
	virtual void Draw(void) = 0;

	virtual bool IsIntoMousePos(const Vector2Dbl& pos);						//�}�E�X���̈���ɓ����Ă��邩

	virtual UIType GetUIType(void) = 0;

	const Rect& GetRange(void)
	{
		return range_;
	}

protected:
	Rect range_;
};

