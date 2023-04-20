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
	MapLoader mapLoader_;				//マップ読み込み用
	std::weak_ptr<Camera> camera_;		//カメラ

	double cntTime_;
};

