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

	const Rect& GetColRect(void)const;		//�R���W�����̋�`�擾
	size_t GetLineNum(void)const;			//���C�����擾
	Line GetLine(int lineNum)const;			//���C���擾

	void SetVertexPtr(VertexPtr ptr);		//���_�̐ݒ�
	void SetIndexPtr(IndexPtr ptr);			//�C���f�b�N�X�̐ݒ�

private:
	VertexPtr vertexPtr_;					//���_�z��̃|�C���^
	IndexPtr indexPtr_;						//�C���f�b�N�X�z��̃|�C���^
	Rect range_;							//�͈�
};

