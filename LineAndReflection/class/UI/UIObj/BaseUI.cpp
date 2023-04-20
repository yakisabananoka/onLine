#include "BaseUI.h"

BaseUI::BaseUI(Rect range) :
	range_(range)
{
}

BaseUI::~BaseUI()
{
}

void BaseUI::SpotUpdate(std::shared_ptr<Controller> controller)
{
}

bool BaseUI::IsIntoMousePos(const Vector2Dbl& pos)
{
	return (range_.GetLT() < pos) && (pos < range_.GetRB());
}
