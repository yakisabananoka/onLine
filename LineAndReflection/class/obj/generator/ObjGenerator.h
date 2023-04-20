#pragma once
#include <memory>
#include <functional>
#include <unordered_map>
#include <string>
#include "../usingObj.h"
#include "../../../parser/rapidjson/document.h"

class Camera;

using GeneratorMap = std::unordered_map<std::string, std::function<ObjPtr(std::weak_ptr<Camera>, const rapidjson::Value&)>>;

class ObjGenerator
{
public:
	ObjGenerator(std::weak_ptr<Camera> camera);
	~ObjGenerator();

	ObjPtr Generate(std::string objType, const rapidjson::Value& rjObj);				//�Ή�����ObjPtr�𐶐�

private:
	GeneratorMap generatrorsMap_;		//Obj�N���X�̃T�u�N���X�𐶐�����֐��I�u�W�F�N�g�̃}�b�v
	std::weak_ptr<Camera> camera_;		//�J����
};

