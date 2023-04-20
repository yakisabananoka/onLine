#include "../BaseLine.h"
#include "LinkAction.h"

LinkAction::LinkAction()
{
}

LinkAction::~LinkAction()
{
}

bool LinkAction::Act(const BaseLine& line, const Circle& circleA, const Circle& circleB)const
{
    auto& nodeList = line.GetNodeList();
    auto& radius = line.GetColRadius();

    if (line.CountCompNode() < 2)
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

    if ((!firstCircle.CheckHit(circleA)) && (!firstCircle.CheckHit(circleB)))
    {
        return false;
    }

    if (firstCircle.CheckHit(circleA) && endCircle.CheckHit(circleB))
    {
        return true;
    }

    if (firstCircle.CheckHit(circleB) && endCircle.CheckHit(circleA))
    {
        return true;
    }

    return false;
}
