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

			ret->emplace_back(1);          //�E��
			ret->emplace_back(2);          //�E��

			ret->emplace_back(3);          //����
			ret->emplace_back(0);          //����

			ret->emplace_back(0);          //����
			ret->emplace_back(1);          //�E��

			ret->emplace_back(2);          //����
			ret->emplace_back(3);          //�E��

			return std::move(ret);
		}
	};
}
