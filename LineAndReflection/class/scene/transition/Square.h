#pragma once
#include "TransitionScene.h"
class Square :
	public TransitionScene
{
public:
	Square(uniBaseScene beforeScene, uniBaseScene nextScene, std::shared_ptr<SceneArgsStruct::Transition::SquareArgs> args);
	~Square();

private:
	void DrawOwnScreen(void) override;		//TransitionSceneクラスに無くてもいい
	bool UpdateTransition(double delta) override;

	void DrawCloseTile(int x, int y, int count);	//XとYはマス目数
	void DrawOpenTile(int x, int y, int count);		//XとYはマス目数

	int count_;					//カウント値1
	int count2_;				//カウント値2

	Vector2 chipSize_;			//チップ一つのサイズ
	Vector2 viewArea_;			//見れる範囲

	const int tTime;
	int nextScr_;		//次のスクリーン
};

