#pragma once
#include <memory>
#include <list>

class Collision;

using ColPtr = std::unique_ptr<Collision>;
using CollisionList = std::list<Collision>;
using ColPtrList = std::list<ColPtr>;
