#pragma once
#include <memory>
#include <random>
#include <vector>
#include "usingEffectObj.h"

class Controller;

class MouseStalker
{
public:
	MouseStalker();
	~MouseStalker();

	void Update(void);		//更新
	void Draw(void);		//描画

private:
	std::shared_ptr<Controller> controller_;		//コントローラー

	std::random_device seed_;						//シード値生成
	std::mt19937 randomGen_;						//乱数生成

	std::uniform_real_distribution<> rangeVecX_;		//Xの範囲
	std::uniform_real_distribution<> rangeVecY_;		//Yの範囲
	std::uniform_real_distribution<> rangeShiftAngle_;	//角度の範囲

	EffPtrVec effList_;			//エフェクトのリスト

	Vector2Dbl oldMousePos;		//前フレームのマウスの位置

	Vector2Dbl mousePos_;		//現在のマウスの位置

};

