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
	virtual void SpotUpdate(std::shared_ptr<Controller> controller);		//領域内にマウスがあってかつ一番上の場合に実行
	virtual void Draw(void) = 0;

	virtual bool IsIntoMousePos(const Vector2Dbl& pos);						//マウスが領域内に入っているか

	virtual UIType GetUIType(void) = 0;

	const Rect& GetRange(void)
	{
		return range_;
	}

protected:
	Rect range_;
};

