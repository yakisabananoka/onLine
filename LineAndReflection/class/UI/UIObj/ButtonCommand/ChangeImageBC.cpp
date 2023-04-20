#include "../Button.h"
#include "ChangeImageBC.h"

ChangeImageBC::ChangeImageBC(std::string imageKey):
	imageKey_(imageKey)
{
}

ChangeImageBC::~ChangeImageBC()
{
}

void ChangeImageBC::Execute(Button& button)
{
	button.SetImageKey(imageKey_);
}
