#pragma once
#include <vector>
#include <memory>

class Obj;
using ObjPtr = std::shared_ptr<Obj>;
using ObjList = std::vector<ObjPtr>;
