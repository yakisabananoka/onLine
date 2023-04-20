#pragma once
#include "BaseLine.h"

class CorrectLine:
	public BaseLine
{
public:
	CorrectLine(std::weak_ptr<Camera> camera, unsigned int color);
	~CorrectLine();

	void Update(double delta)override;

	void SetPoint(Vector2Dbl pos)override;
	void EndDrawingLine(void)override;

private:
	void EdgeCorrect(void);		//ï‚ê≥

};

