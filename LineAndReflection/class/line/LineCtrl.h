#pragma once
#include <memory>
#include <functional>
#include <array>
#include <list>
#include <string>
#include <utility>
#include "../input/Controller.h"
#include "usingLine.h"
#include "../obj/usingObj.h"

class LineGenerator;
class Camera;
class UICtrl;
class Gauge;
class Stage;
struct Capsule;
struct Node;

class LineCtrl
{
public:
	LineCtrl(std::weak_ptr<Camera> camera, std::string genLineName);
	~LineCtrl();

	void Init(void);
	void InitUI(UICtrl& uiCtrl);

	void Update(double delta, const Stage& stage);									//更新
	void UpdateAfterObj(double delta, ObjList& objList);							//Objのアップデート後に実行
	void Draw(void);																//描画

	void GetLineInfoCap(std::function<bool(const Capsule&, LinePtr&)> func);		//線の情報をカプセル単位で渡す
	void GetLineInfoNode(std::function<bool(const Node&, LinePtr&)> func);			//線の情報をノード単位で渡す

	void CancelLastLine(void);							//直前の線を取り消し

	const double& GetTotalLineDist(void)const			//線の距離の合計の取得
	{
		return totalLineDist_;
	}

private:

	std::shared_ptr<Controller> controller_;		//コントローラー
	std::weak_ptr<Camera> camera_;					//カメラ
	std::list<LinePtr> lineList_;					//線の配列
	std::array<std::string, 3> lineTypeList_;		//ラインの種類の配列

	std::unique_ptr<LineGenerator> generator_;		//ラインのジェネレーター

	std::string genLineName_;						//生成する線の名前

	int genLineNum_;								//生成する線の番号

	double totalLineDist_;							//線の距離の合計
	double switchTime_;								//切り替え時間
};
