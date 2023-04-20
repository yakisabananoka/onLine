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

	LinePtr Generate(std::string lineType, unsigned int color)const;		//�Ή�����LinePtr�𐶐�

private:
	LineGenMap genMap_;						//Line�N���X�̃T�u�N���X�𐶐�����֐��I�u�W�F�N�g�̃}�b�v
	std::weak_ptr<Camera> camera_;			//�J����

};

