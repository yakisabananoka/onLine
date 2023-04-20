#pragma once
#include <memory>
#include <random>
#include <vector>
#include "usingEffectObj.h"
#include "../common/Vector2.h"

class Camera;

class ItemEffect
{
public:
	ItemEffect(std::weak_ptr<Camera> camera, Vector2Dbl pos);
	~ItemEffect();

	void Update(double delta);				//更新
	void Draw(void);						//描画

	bool IsEnd(void)const;					//終了しているか

private:
	std::weak_ptr<Camera> camera_;			//カメラ

	std::random_device seed_;				//シード値を生成
	std::mt19937 randomGen_;				//乱数生成用

	std::uniform_real_distribution<> outVecXRange_;		//Xの範囲
	std::uniform_real_distribution<> outVecYRange_;		//Yの範囲

	EffPtrVec effList_;			//エフェクトのリスト

	Vector2Dbl pos_;			//基準位置
};

