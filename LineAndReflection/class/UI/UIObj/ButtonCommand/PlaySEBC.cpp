#include "PlaySEBC.h"
#include "../../../common/SoundMng.h"

PlaySEBC::PlaySEBC(std::string soundKey):
	soundKey_(soundKey)
{
}

PlaySEBC::~PlaySEBC()
{
}

void PlaySEBC::Execute(Button& button)
{
	lpSoundMng.PlaySE(soundKey_);
}
