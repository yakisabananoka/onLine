#pragma once
#include "../Vector2.h"

struct Capsule
{
	Capsule();
	Capsule(Vector2Dbl pA, Vector2Dbl pB, double r);

	Vector2Dbl posA;
	Vector2Dbl posB;
	double radius;

	Vector2Dbl Vec(void)const;

	bool InShape(const Vector2Dbl& checkPos)const;
};