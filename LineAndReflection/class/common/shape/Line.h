#pragma once
#include "../Vector2.h"

class Line
{
public:
	Line();
	Line(Vector2Dbl s, Vector2Dbl e);
	~Line();

	Vector2Dbl p;		//�n�_
	Vector2Dbl end;		//�I�_

	Vector2Dbl vec(void)const;

private:
	
};

