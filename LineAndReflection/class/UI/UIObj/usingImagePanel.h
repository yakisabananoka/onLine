#pragma once
#include <memory>
#include <vector>

class ImagePanel;
using IPPtr = std::unique_ptr<ImagePanel>;
using IPList = std::vector<IPPtr>;
