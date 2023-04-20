#pragma once
#include <memory>
#include <vector>
#include "usingObj.h"
#include "../collision/usingCollision.h"
#include "../common/Vector2.h"

class Camera;
class LineCtrl;
class Stage;
class UICtrl;
enum class ObjType;

class Obj
{
public:
	Obj(std::weak_ptr<Camera> camera, const Vector2Dbl& pos, const int& id);
	virtual ~Obj();

	virtual void Init(void) = 0;																			//初期化
	virtual void Update(double delta, ObjList& objList, LineCtrl& lineCtrl, const Stage& stage) = 0;		//更新
	virtual void ConfirmUpdate(double delta, const Stage& stage) {};										//更新の確定
	virtual void Draw(void) = 0;																			//描画

	virtual void SetUI(UICtrl& uiCtrl) {};				//Obj個別のUIの設定

	virtual ObjType GetObjType(void)const = 0;			//ObjTypeの取得

	virtual bool IsUnit(void)const						//Unitかどうか
	{
		return false;
	}

	const Vector2Dbl& GetPos(void)const					//位置の取得
	{
		return pos_;
	}

	const bool& GetSceneEndFlg(void)const				//シーンが終了したか
	{
		return sceneEndFlg_;
	}

	const int& GetObjID(void)const						//固有IDの取得
	{
		return id_;
	}

	const ColPtr& GetColPtr(void)const					//コリジョンの取得
	{
		return colPtr_;
	}

	const bool& IsActive(void)const						//有効状態か
	{
		return activeFlg_;
	}

protected:
	Vector2Dbl GetCamOffset(void);			//カメラオフセットの取得

	std::weak_ptr<Camera> camera_;			//カメラ
	const Vector2Dbl defPos_;				//初期位置
	Vector2Dbl pos_;						//位置
	bool sceneEndFlg_;						//シーンの終了フラグ
	const int id_;							//固有ID

	ColPtr colPtr_;							//コリジョン

	bool activeFlg_;						//有効フラグ

};

