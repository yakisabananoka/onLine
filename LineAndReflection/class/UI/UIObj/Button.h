#pragma once
#include <memory>
#include <functional>
#include <list>
#include <unordered_map>
#include <string>
#include "BaseUI.h"
#include "ButtonCommand/ButtonCommand.h"

class Controller;

class Button :
    public BaseUI
{
public:
	enum class State
	{
		JustOn,				//押した瞬間
		JustOff,			//離した瞬間
		NowOn,				//押されている
		NowOff,				//離している
		NowEnter,			//判定にマウスが入っている
		NowLeave,			//判定にマウスが入っていない
		JustEnter,			//判定にマウスが入った瞬間
		JustLeave			//判定からマウスが出た瞬間
	};

	Button(Vector2Dbl pos, const std::string& imageKey, bool alphaCheck = true);
	~Button();

	virtual void Init(void)override;
	virtual void Update(double delta)override;
	virtual void SpotUpdate(std::shared_ptr<Controller> controller)override;		//レイが当たっている場合に実行する処理
	virtual void Draw(void)override;

	virtual bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//マウスの座標との当たり判定チェック

	virtual UIType GetUIType(void)override
	{
		return UIType::Button;
	}

	virtual void SetCommand(State state, ButtonCommandPtr command);					//それぞれの状態の時に実行するコマンドの設定

	virtual void SetCC(Vector2Dbl pos);												//中心位置の設定
	
	virtual void SetImageKey(std::string imageKey);									//画像のキーの設定

private:
	void InitImage(void);													//初期位置

	bool alphaCheck_;

	std::shared_ptr<Controller> controller_;

	std::string imageKey_;

	std::unordered_map<State, BCPtrList> commandMap_;
	
	State oldEnterState_;
};

