#include <DxLib.h>
#include "Color.h"

Color::Color() :
	r(0), g(0), b(0)
{
}

Color::Color(int r, int g, int b) :
	r(r), g(g), b(b)
{
}

Color::Color(unsigned int color)
{
	GetColor2(color, &r, &g, &b);
}

unsigned int Color::GetColorCode(void) const
{
	return GetColor(r, g, b);
}
