#pragma once
#include <memory>
#include <vector>
#include <list>
#include <unordered_map>
#include <DxLib.h>
#include "../obj/usingObj.h"
#include "../common/shape/Capsule.h"
#include "../common/Vector2.h"

class Camera;

//線を構成するノード
struct Node
{
	enum class State
	{
		INCOMPLETE,		//未完了
		COMPLETE,		//完了
		DISPOSAL		//廃棄
	};
	Node(Vector2Dbl& p, State s, double dis) :pos(p), state(s), dist(dis) {}
	Vector2Dbl pos;
	State state;
	double dist;
};

struct ColInfo
{
	ColInfo(const int& id,const Capsule& cap):objId(id),capsule(cap){}
	int objId;
	Capsule capsule;
};

using ColorMap = std::unordered_map<Node::State, unsigned int>;
using NodeList = std::list<Node>;
using ColInfoPtr = std::unique_ptr<ColInfo>;

class BaseLine
{
public:
	enum class State
	{
		DRAWING,		//描画中
		STANDBY,		//待機中
		TOUCHING,		//接触中
		DIE				//削除対象
	};

	BaseLine(std::weak_ptr<Camera> camera, unsigned int color);
	~BaseLine();

	virtual void Update(double delta) = 0;
	virtual void UpdateAfterObj(double delta, ObjList& objList) {};			//オブジェクトのアップデート後に行う関数

	void Draw(void);

	virtual void SetPoint(Vector2Dbl pos) = 0;			//点の設置
	void ClearPoint(void);								//点の一括消去

	bool IsActive(void);								//生存フラグ
	void SetActive(bool flg);							//フラグの設定

	virtual void EndDrawingLine(void) = 0;				//終端時に呼ぶ

	const NodeList& GetNodeList(void)const				//ノードのリストを取得
	{
		return nodeList_;
	}
	const double& GetColRadius(void)const;				//当たり判定の半径を取得
	
	bool IsOverLength(void)const;						//長さがオーバーしていたらtrueを返す

	static void PreLoadLineScreen(void);				//線のスクリーン等をあらかじめロードする

	void SetColObjInfo(ColInfoPtr ptr);					//接触したObjのIDの登録

	size_t CountCompNode(void)const;					//確定済みノードの個数をカウント

	const State& GetState(void)const
	{
		return state_;
	}

	virtual bool HasCollision(void);					//当たり判定を持っているか

	double GetTotalLength(void)const;					//確定済みノードの総距離計算

	double GetMaxLength(void)const;						//最大距離取得
protected:
	double GetMaxActiveTime(void);						//最大生存可能時間の取得
	void SetPolygon(float maxU);						//描画用ポリゴンの設定
	void SetPolygonAll(void);							//全ての描画用ポリゴンの設定
	
	void UpdateLineScreen(double delta);				//下地のアップデート

	bool CheckSetPoint(const Vector2Dbl& setPos)const;	//ノードの追加判定

	std::vector<VERTEX2D> vertexVec_;					//描画用ポリゴンの頂点配列
	std::vector<VERTEX2D> bufferVertexVec_;				//カメラオフセット加算用のバッファとしてあらかじめ取っておく
	std::vector<unsigned short> index_;					//描画用ポリゴンの頂点の順番
	
	std::weak_ptr<Camera> camera_;						//カメラ
	NodeList nodeList_;									//ノードのリスト

	std::vector<ColInfoPtr> colObjInfoVec_;				//Objとの衝突情報
	
	double time_;										//インスタンス時からの経過時間
	double activeTime_;									//線の完全有効時からの経過時間
	State state_;										//現在の状態
	Vector2Dbl milkyPos_;

	Vector2Dbl starWayHighPos_;
	Vector2Dbl starWayLowPos_;

	int lineR_;
	int lineG_;
	int lineB_;

private:
	void DrawLinePolygon(const Vector2Dbl& camOffset);	//ポリゴン単位で描画
	void DrawLineScreen(void);							//線

	double starWayCnt_;
	double starWayTime_;

};

