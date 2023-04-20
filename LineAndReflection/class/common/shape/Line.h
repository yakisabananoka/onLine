#pragma once
#include "../Vector2.h"

class Line
{
public:
	Line();
	Line(Vector2Dbl s, Vector2Dbl e);
	~Line();

	Vector2Dbl p;		//始点
	Vector2Dbl end;		//終点

	Vector2Dbl vec(void)const;

private:
	
};

