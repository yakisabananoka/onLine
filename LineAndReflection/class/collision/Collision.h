#pragma once
#include <memory>
#include <vector>
#include "../common/shape/Rect.h"
#include "../common/shape/Line.h"
#include "../common/Vector2.h"

using VertexVec = std::vector<Vector2Dbl>;
using VertexPtr = std::unique_ptr<VertexVec>;
using IndexVec = std::vector<int>;
using IndexPtr = std::unique_ptr<IndexVec>;

class Collision
{
public:
	Collision(const Rect& range);
	~Collision();

	const Rect& GetColRect(void)const;		//コリジョンの矩形取得
	size_t GetLineNum(void)const;			//ライン数取得
	Line GetLine(int lineNum)const;			//ライン取得

	void SetVertexPtr(VertexPtr ptr);		//頂点の設定
	void SetIndexPtr(IndexPtr ptr);			//インデックスの設定

private:
	VertexPtr vertexPtr_;					//頂点配列のポインタ
	IndexPtr indexPtr_;						//インデックス配列のポインタ
	Rect range_;							//範囲
};

