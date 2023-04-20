#pragma once
#include <memory>
#include <list>

class BaseUI;

using UIPtr = std::unique_ptr<BaseUI>;
using UIList = std::list<UIPtr>;
