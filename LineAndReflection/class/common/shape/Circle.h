#pragma once
#include "../Vector2.h"

struct Circle
{
	Circle();
	Circle(Vector2Dbl p, double r);
	~Circle();

	Vector2Dbl pos;		//íÜêSç¿ïW
	double radius;		//îºåa

	bool InShape(const Vector2Dbl& checkPos)const;
	bool CheckHit(const Circle& circle)const;

};

