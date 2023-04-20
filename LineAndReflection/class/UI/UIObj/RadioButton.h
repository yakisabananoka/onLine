#pragma once
#include <memory>
#include <map>
#include <string>
#include "BaseUI.h"
#include "../../common/Vector2.h"

class Button;

struct RadioButtonInfo
{
	RadioButtonInfo(bool flg, std::unique_ptr<Button> btn) :activeFlg(flg), button(std::move(btn)) {};
	bool activeFlg = true;
	std::unique_ptr<Button> button;
};

class RadioButton :
    public BaseUI
{
public:
	RadioButton(std::string fontKey);
    ~RadioButton();

	void Init(void)override;
	void Update(double delta)override;
	void SpotUpdate(std::shared_ptr<Controller> controller)override;		//レイが当たっている場合に実行する処理
	void Draw(void)override;

	bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//マウスの座標との当たり判定チェック

	UIType GetUIType(void)override
	{
		return UIType::RadioButton;
	}

	void SetChildButton(std::string key, std::string text, Vector2Dbl pos, unsigned int color, unsigned int edgeColor);					//使用するボタン
	void SetChildButton(std::string key, std::string text, double cX, double cY, unsigned int color, unsigned int edgeColor);			//使用するボタンの登録

	void SetSelectKey(std::string key);

	const std::string& GetNowSelectKey(void)const;

private:
	std::string fontKey_;

	std::map<std::string, std::unique_ptr<RadioButtonInfo>> infoMap_;
	std::string nowSelectKey_;

	std::string nowSpotKey_;

};

