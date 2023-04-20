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
		Vector2Dbl p;		//始点
		Vector2Dbl vec;		//方向ベクトル
	};

	ColPoint CheckCollision(Ray ray, Rect col)const;
	ColPoint CheckCollision(Ray ray, const double& size, const Rect& col)const;
	
	bool CheckRay(Ray ray, Line line, Vector2Dbl& colPos)const;								//レイが当たっているか
	bool CheckRay(Ray ray, Vector2Dbl pos, double size, Vector2Dbl& colPos)const;			//レイが当たっているか

	Vector2Dbl CalcLineDist(Ray ray, Line line)const;		//レイとラインの距離取得
	
private:
	
};

