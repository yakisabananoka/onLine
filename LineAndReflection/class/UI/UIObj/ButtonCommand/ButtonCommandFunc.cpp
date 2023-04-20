#include "ButtonCommandFunc.h"

ButtonCommandFunc::ButtonCommandFunc(CallbackFunc func) :
	func_(func)
{
}

ButtonCommandFunc::~ButtonCommandFunc()
{
}

void ButtonCommandFunc::Execute(Button& button)
{
	func_(button);
}
