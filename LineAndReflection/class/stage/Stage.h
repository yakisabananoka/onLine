#pragma once
#include <string>
#include <vector>
#include <memory>
#include "MapLoader.h"
#include "../obj/usingObj.h"

class Camera;

class Stage
{
public:
	Stage(std::string path, std::weak_ptr<Camera> camera);
	~Stage();

	void Init(void);
	void Update(double delta);
	void Draw(void);

	void SetObj(ObjList& objList);

	const MapLoader& GetMapInfo(void)const
	{
		return mapLoader_;
	}

	const double& GetCntTime(void)const
	{
		return cntTime_;
	}

private:
	MapLoader mapLoader_;				//�}�b�v�ǂݍ��ݗp
	std::weak_ptr<Camera> camera_;		//�J����

	double cntTime_;
};

