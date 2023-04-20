#pragma once
#include "Collision.h"

namespace SetCollisionForRect
{
	struct SetVertexPtr
	{
		VertexPtr operator()(const Rect& colRect)
		{
			VertexPtr ret = std::make_unique<VertexVec>();

			ret->emplace_back(colRect.GetLT());       //0
			ret->emplace_back(colRect.GetRT());       //1
			ret->emplace_back(colRect.GetRB());       //2
			ret->emplace_back(colRect.GetLB());       //3

			return std::move(ret);
		}
	};

	struct SetIndexPtr
	{
		IndexPtr operator()(const Rect& colRect)
		{
			IndexPtr ret = std::make_unique<IndexVec>();

			ret->emplace_back(1);          //右上
			ret->emplace_back(2);          //右下

			ret->emplace_back(3);          //左下
			ret->emplace_back(0);          //左上

			ret->emplace_back(0);          //左上
			ret->emplace_back(1);          //右上

			ret->emplace_back(2);          //左下
			ret->emplace_back(3);          //右下

			return std::move(ret);
		}
	};
}
