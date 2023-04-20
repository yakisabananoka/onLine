#include "../BaseLine.h"
#include "EncloseAction.h"
#include "../../common/shape/Circle.h"

EncloseAction::EncloseAction(Vector2Dbl pos):
	targetPos_(pos)
{
}

EncloseAction::~EncloseAction()
{
}

bool EncloseAction::Act(const BaseLine& line) const
{
	auto& nodeList = line.GetNodeList();
	auto& radius = line.GetColRadius();

	if (line.CountCompNode() < 3)
	{
		return false;
	}

	Circle firstCircle = {
		std::find_if(nodeList.begin(), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; })->pos,
		radius
	};

	Circle endCircle = {
		std::find_if(nodeList.rbegin(), nodeList.rend(), [](const Node& node) {return node.state == Node::State::COMPLETE; })->pos,
		radius
	};

	if (!firstCircle.CheckHit(endCircle))
	{
		return false;
	}

	auto itr = std::find_if(nodeList.begin(), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
	auto nextItr = std::find_if(std::next(itr, 1), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });

	const bool flg = (itr->pos - nextItr->pos).Cross(targetPos_) < 0;

	while (nextItr != nodeList.end())
	{
		if (flg != ((itr->pos - nextItr->pos).Cross(targetPos_) < 0))
		{
			return false;
		}

		itr = nextItr;
		nextItr = std::find_if(std::next(itr, 1), nodeList.end(), [](const Node& node) {return node.state == Node::State::COMPLETE; });
	}

	return true;
}
