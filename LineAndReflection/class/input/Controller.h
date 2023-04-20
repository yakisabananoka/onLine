#pragma once
#include <array>
#include <map>
#include "InputID.h"
#include "../common/Vector2.h"

//入力装置の種類
enum class CntType
{
	KEY_MOUSE,		//キーボードとマウス
	MAX
};

//バッファの
enum class Trg
{
	NOW,		//現在
	OLD,		//前フレーム
	MAX
};

using TrgBool = std::array<bool, static_cast<size_t>(Trg::MAX)>;
using CntData = std::map<InputID, TrgBool>;

class Controller
{
public:
	Controller();
	virtual ~Controller() {};

	virtual void Update(void) = 0;					//更新
	virtual CntType GetCntType(void)const = 0;		//コントローラーの種類を取得

	//コントローラーのデータ取得
	const CntData& GetCntData(void)const
	{
		return cntData_;
	}

	//位置取得
	const Vector2Dbl& GetPos(void)const
	{
		return pos_;
	}

	//回転量取得
	const int& GetRotate(void)const
	{
		return rota_;
	}

	virtual unsigned int GetID(InputID inputId)const = 0;				//キーテーブルに設定されている実値を取得
	virtual void SetID(InputID inputId, unsigned int keyId) = 0;		//実値をキーテーブルに設定

	bool NowOn(InputID inputID)const;		//現在押されているか
	bool NowOff(InputID inputID)const;		//現在離れているか
	bool JustOn(InputID inputID)const;		//押された瞬間
	bool JustOff(InputID inputID)const;		//離れた瞬間

	void SetAcitive(bool flg);				//アクティブ状態の切り替え
	
protected:
	CntData cntData_;		//押下状態のデータ
	Vector2Dbl pos_;		//現在位置

	int rota_;				//回転量

	bool activeFlg_;		//有効か否か
};

