#pragma once
#include <memory>
#include <vector>

class EffectObj;

using EffectPtr = std::unique_ptr<EffectObj>;
using EffPtrVec = std::vector<EffectPtr>;