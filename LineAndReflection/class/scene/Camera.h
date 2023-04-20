#pragma once
#include <memory>
#include <random>
#include <DxLib.h>
#include "../common/shape/Rect.h"
#include "../common/Vector2.h"

class Obj;
class Stage;

class Camera
{
public:
	Camera();
	~Camera();

	void Update(double delta);
	void Draw(void);

	const Vector2Dbl& GetPos(void)const;													//位置の取得
	void SetPos(Vector2Dbl pos);														//位置の設定
	
	Vector2Dbl GetDrawOffset(void)const;													//描画時のオフセット値の取得

	bool SetStageAndTarget(std::weak_ptr<Stage> stage, std::weak_ptr<Obj> target);			//ステージの設定(こちらを先に設定)
	bool SetTarget(std::weak_ptr<Obj> target);

	void SetShake(double time, double mag);
	bool IsShake(void)const;

private:
	bool Init(void);					//初期化用関数
	bool InitArea(void);				//移動領域の初期化

	std::weak_ptr<Obj> target_;			//注視点
	std::weak_ptr<Stage> stage_;		//ステージ

	Vector2Dbl defPos_;					//初期位置
	Vector2Dbl pos_;					//位置

	Rect antiMoveRect;					//移動不可領域
	
	std::random_device seed_;
	std::mt19937 randomGen_;
	std::uniform_real_distribution<> shakeRange_;

	std::unique_ptr<double> shakeTime_;	//揺れる時間
	double shakeMag_;					//揺れる大きさ


};

