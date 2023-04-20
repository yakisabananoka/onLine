#include <DxLib.h>
#include "InfoMessage.h"

namespace infoMes_const
{
	//constexpr color
}

using namespace infoMes_const;

InfoMessage::InfoMessage(Vector2Dbl pos) :
	BaseUI(Rect(pos, pos))
{
}

InfoMessage::~InfoMessage()
{
}

void InfoMessage::Init(void)
{
}

void InfoMessage::Update(double delta)
{
	command_(buffer_);
}

void InfoMessage::Draw(void)
{
	//DrawFormatStringToHandle(static_cast<int>(range_.pos.x),static_cast<int>(range_.pos.y),)
}

void InfoMessage::SetCommand(InfoMesCommandPtr command)
{
	command_ = command;
}
