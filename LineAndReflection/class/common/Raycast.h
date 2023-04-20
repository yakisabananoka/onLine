#pragma once
#include <utility>
#include "Vector2.h"
#include "shape/Rect.h"
#include "shape/Line.h"

using ColPoint = std::pair<bool, Vector2Dbl>; 

class Raycast
{
public:
	struct Ray
	{
		Vector2Dbl p;		//�n�_
		Vector2Dbl vec;		//�����x�N�g��
	};

	ColPoint CheckCollision(Ray ray, Rect col)const;
	ColPoint CheckCollision(Ray ray, const double& size, const Rect& col)const;
	
	bool CheckRay(Ray ray, Line line, Vector2Dbl& colPos)const;								//���C���������Ă��邩
	bool CheckRay(Ray ray, Vector2Dbl pos, double size, Vector2Dbl& colPos)const;			//���C���������Ă��邩

	Vector2Dbl CalcLineDist(Ray ray, Line line)const;		//���C�ƃ��C���̋����擾
	
private:
	
};

