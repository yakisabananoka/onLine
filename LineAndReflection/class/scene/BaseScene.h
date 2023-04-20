#pragma once
#include <memory>
#include <string>
#include "SceneID.h"
#include "../scene/SceneArgsStruct.h"
#include "transition/TransitionID.h"
#include "../input/Controller.h"
#include "../common/Vector2.h"

class BaseScene;

namespace SceneArgsStruct
{
	struct BaseArgs;
}

using uniBaseScene = std::unique_ptr<BaseScene>;

class BaseScene
{
public:
	BaseScene(std::shared_ptr<SceneArgsStruct::BaseArgs> args);
	virtual ~BaseScene();

	virtual bool Init(void) = 0;
	virtual uniBaseScene Update(double delta, uniBaseScene ownScene) = 0;
	virtual void DrawOwnScreen(void) = 0;

	void Draw(void);

	const Vector2& GetScreenSize(void);			//スクリーンサイズの取得
	const int& GetScrID(void);					//スクリーンIDの取得
	virtual void PlaySceneBGM(void) {};			//BGMの再生
	
protected:
	const Vector2 scrSize_;						//スクリーンサイズ
	std::unique_ptr<BaseScene> nextScene_;		//次のシーン
	int scrID_;									//シーンごとのスクリーンハンドル


};
