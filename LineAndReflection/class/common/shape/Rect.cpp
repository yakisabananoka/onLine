#include "Rect.h"

Rect::Rect() :
	pos(0.0, 0.0), size(0.0, 0.0)
{
}

Rect::Rect(Vector2Dbl centerPos, double w, double h) :
	pos(centerPos.x - w / 2.0, centerPos.y - h / 2.0), size(w, h)
{
}

Rect::Rect(Vector2Dbl LUPos, Vector2Dbl RDPos) :
	pos(LUPos), size(RDPos - LUPos)
{
}

double Rect::Left(void) const
{
	return pos.x;
}

double Rect::Right(void) const
{
	return pos.x + size.x;;
}

double Rect::Top(void) const
{
	return pos.y;
}

double Rect::Bottom(void) const
{
	return pos.y + size.y;
}

void Rect::SetLeft(double value)
{
	size.x += pos.x - value;
	pos.x = value;

}

void Rect::SetRight(double value)
{
	size.x = value - pos.x;
}

void Rect::SetTop(double value)
{
	size.y += pos.y - value;
	pos.y = value;
}

void Rect::SetBottom(double value)
{
	size.y = value - pos.y;
}

void Rect::SetFixedLeft(double value)
{
	pos.x = value;
}

void Rect::SetFixedRight(double value)
{
	pos.x = value - size.x;
}

void Rect::SetFixedTop(double value)
{
	pos.y = value;
}

void Rect::SetFixedBottom(double value)
{
	pos.y = value - size.y;
}

void Rect::SetFixedCC(Vector2Dbl cc)
{
	pos = cc - size / 2.0;
}

Vector2Dbl Rect::GetLT(void) const
{
	return pos;
}

Vector2Dbl Rect::GetLC(void) const
{
	return Vector2Dbl(pos.x, pos.y + size.y / 2.0);
}

Vector2Dbl Rect::GetLB(void) const
{
	return Vector2Dbl(pos.x, pos.y + size.y);
}

Vector2Dbl Rect::GetCT(void) const
{
	return Vector2Dbl(pos.x + size.x / 2.0, pos.y);
}

Vector2Dbl Rect::GetCC(void) const
{
	return pos + size / 2.0;
}

Vector2Dbl Rect::GetCB(void) const
{
	return Vector2Dbl(pos.x + size.x / 2.0, pos.y + size.y);
}

Vector2Dbl Rect::GetRT(void) const
{
	return Vector2Dbl(pos.x + size.x, pos.y);
}

Vector2Dbl Rect::GetRC(void) const
{
	return Vector2Dbl(pos.x + size.x, pos.y + size.y / 2.0);
}

Vector2Dbl Rect::GetRB(void) const
{
	return pos + size;
}

void Rect::Reset(Vector2Dbl centerPos, double w, double h)
{
	size = { w,h };
	SetFixedCC(centerPos);
}

void Rect::Reset(Vector2Dbl LUPos, Vector2Dbl RDPos)
{
	pos = LUPos;
	size = RDPos - LUPos;
}

bool Rect::InShape(Vector2Dbl checkPos)const
{
	return (pos < checkPos) && (checkPos < pos + size);
}

bool Rect::CheckHit(const Rect& rect)const
{
	if (Right() < rect.Left())
	{
		return false;
	}

	if (Left() > rect.Right())
	{
		return false;
	}

	if (Top() > rect.Bottom())
	{
		return false;
	}

	if (Bottom() < rect.Top())
	{
		return false;
	}

	return true;
}
