#pragma once
#include <memory>
#include <functional>
#include <string>
#include <unordered_map>
#include "../usingLine.h"

class Camera;

using LineGen = std::function<LinePtr(std::weak_ptr<Camera>, unsigned int)>;
using LineGenMap = std::unordered_map<std::string, LineGen>;

class LineGenerator
{
public:
	LineGenerator(std::weak_ptr<Camera> camera);
	~LineGenerator();

	LinePtr Generate(std::string lineType, unsigned int color)const;		//対応するLinePtrを生成

private:
	LineGenMap genMap_;						//Lineクラスのサブクラスを生成する関数オブジェクトのマップ
	std::weak_ptr<Camera> camera_;			//カメラ

};

