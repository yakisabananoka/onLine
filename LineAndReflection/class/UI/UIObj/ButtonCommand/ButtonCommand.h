#pragma once
#include <memory>
#include <list>

class Button;
class ButtonCommand;

using ButtonCommandPtr = std::unique_ptr<ButtonCommand>;
using BCPtrList = std::list<ButtonCommandPtr>;

class ButtonCommand
{
public:
	ButtonCommand() {};
	~ButtonCommand() {};

	virtual void Execute(Button& button) = 0;
};

