#pragma once
#include <memory>
#include <string>
#include "effectCommand/EffectCommand.h"
#include "../common/Vector2.h"

struct Trans
{
	void Update(const double& delta)
	{
		speed += accele * delta;
	}
	double speed = 0.0;		//速さ
	double accele = 0.0;	//加速度
};

struct EffectInfo
{
	std::string imageKey;						//画像のキー
	Vector2Dbl pos;								//位置
	Vector2Dbl vec;								//移動方向
	Trans move;									//移動量
	Trans rota;									//回転量
	Trans exAmount;								//拡大量
	Trans blendAmount;							//ブレンド量
	double angle = 0.0;							//角度
	double mag = 1.0;							//拡大率
	double lifeTime = 0.0;						//生存時間
	int blendMode = 0;							//ブレンドモード
	double blend = 0.0;							//ブレンドのパラメーター(intに変換)
	int r = 255;								//赤(0～255)
	int g = 255;								//緑(0～255)
	int b = 255;								//青(0～255)
	std::unique_ptr<EffectCommand> command;		//コマンド
};

