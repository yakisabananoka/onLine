#include "Controller.h"

Controller::Controller()
{
	activeFlg_ = true;
	rota_ = 0;
}

bool Controller::NowOn(InputID inputID) const
{
	return cntData_.at(inputID)[static_cast<int>(Trg::NOW)];
}

bool Controller::NowOff(InputID inputID) const
{
	return !cntData_.at(inputID)[static_cast<int>(Trg::NOW)];
}

bool Controller::JustOn(InputID inputID) const
{
	return ((cntData_.at(inputID)[static_cast<int>(Trg::NOW)]) && (!cntData_.at(inputID)[static_cast<int>(Trg::OLD)]));
}

bool Controller::JustOff(InputID inputID) const
{
	return (!(cntData_.at(inputID)[static_cast<int>(Trg::NOW)]) && (cntData_.at(inputID)[static_cast<int>(Trg::OLD)]));
}

void Controller::SetAcitive(bool flg)
{
	activeFlg_ = flg;
}
