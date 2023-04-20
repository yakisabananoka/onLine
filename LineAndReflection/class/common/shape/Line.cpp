#include "Line.h"

Line::Line()
{
}

Line::Line(Vector2Dbl s, Vector2Dbl e) :
	p(s), end(e)
{
}

Line::~Line()
{
}

Vector2Dbl Line::vec(void) const
{
	return end - p;
}
