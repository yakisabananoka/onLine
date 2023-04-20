#include "Circle.h"

Circle::Circle():
	radius(0.0)
{
}

Circle::Circle(Vector2Dbl p, double r) :
	pos(p), radius(r)
{
}

Circle::~Circle()
{
}

bool Circle::InShape(const Vector2Dbl& checkPos)const
{
	return pow(radius, 2) > (checkPos - pos).SQMagnitude();
}

bool Circle::CheckHit(const Circle& circle)const
{
	return pow(circle.radius + radius, 2) > (circle.pos - pos).SQMagnitude();
}
