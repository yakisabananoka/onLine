#pragma once
#include <string>
#include "generator/SceneGenerator.h"
#include "transition/generator/TransitionGenerator.h"
#include "temporary/generator/TemporaryGenerator.h"
#include "../common/Vector2.h"
#include "BaseScene.h"

#define lpSceneMng SceneMng::GetInstance()
//#define GAME_NAME "__UNTITLED__"

class Controller;
class MouseStalker;

namespace SceneArgsStruct
{
	struct BaseArgs;
}

class SceneMng
{
public:
	static SceneMng& GetInstance(void)
	{
		static SceneMng s_Instance;
		return s_Instance;
	}
	void Run(void);

	const Vector2& GetWindowSize(void);				//ウィンドウサイズ取得
	std::shared_ptr<Controller> GetController(void);			//コントローラー取得

	void SetNextScene(SceneID nextSceneID, TransitionID nextTransitionID,
		std::shared_ptr<SceneArgsStruct::BaseArgs> nextSceneArgsPtr,
		std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> nextTransArgsPtr);
	void SetNextScene(TemporaryID nextTempID, std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> nextTempArgsPtr);

	void SetDeltaTimeFlg(bool flg);

private:
	SceneMng();
	~SceneMng();

	bool Init(void);
	bool SysInit(void);

	void Update(double delta);
	void Draw(void);

	void WindowTextRefresh(void);									//ウィンドウのテキストの更新

	uniBaseScene ToNextScene(uniBaseScene ownScene);				//シーン移行用関数
	uniBaseScene ToNextTempScene(uniBaseScene ownScene);			//シーン移行用関数

	double time_;													//経過時間
	uniBaseScene scene_;											//現在のシーン
	std::shared_ptr<Controller> controller_;						//コントローラー

	SceneGenerator sceneGen_;										//シーン生成用クラス
	TransitionGenerator trGen_;										//トランジションの生成用クラス
	TemporaryGenerator tpGen_;

	SceneID nextSceneID_;																//次のシーンのID
	TransitionID nextTransitionID_;														//次のトランジションのID
	TemporaryID nextTemporaryID_;
	std::shared_ptr<SceneArgsStruct::BaseArgs> nextSceneArgs_;							//次のシーンの引数ポインタ
	std::shared_ptr<SceneArgsStruct::Transition::TransitionArgs> nextTransArgs_;		//次のトランジションの引数ポインタ
	std::shared_ptr<SceneArgsStruct::Temporary::TemporaryArgs> nextTempArgs_;

	std::unique_ptr<MouseStalker> mouseStalker_;            //マウスストーカー

	bool deltaTimeFlg;
};

