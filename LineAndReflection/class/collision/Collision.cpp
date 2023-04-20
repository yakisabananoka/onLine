#include "Collision.h"

Collision::Collision(const Rect& range) :
	range_(range)
{
}

Collision::~Collision()
{
}

const Rect& Collision::GetColRect(void) const
{
	return range_;
}

size_t Collision::GetLineNum(void) const
{
	return indexPtr_->size() / 2;
}

Line Collision::GetLine(int lineNum)const
{
	lineNum *= 2;
	return Line((*vertexPtr_)[(*indexPtr_)[lineNum]], (*vertexPtr_)[(*indexPtr_)[static_cast<size_t>(lineNum) + 1]]);
}

void Collision::SetVertexPtr(VertexPtr ptr)
{
	vertexPtr_ = std::move(ptr);
}

void Collision::SetIndexPtr(IndexPtr ptr)
{
	indexPtr_ = std::move(ptr);
}
