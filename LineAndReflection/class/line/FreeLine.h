#pragma once
#include "BaseLine.h"
class FreeLine :
    public BaseLine
{
public:
	FreeLine(std::weak_ptr<Camera> camera, unsigned int color);
	~FreeLine();

	void Update(double delta)override;

	void SetPoint(Vector2Dbl pos)override;
	void EndDrawingLine(void)override;

};

