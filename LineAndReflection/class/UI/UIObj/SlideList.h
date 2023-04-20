#pragma once
#include <memory>
#include <vector>
#include <string>
#include "BaseUI.h"
#include "../UIObj/usingImagePanel.h"

class SlideList :
    public BaseUI
{
public:
	enum class Dir
	{
		Up,
		Down,
		Left,
		Right
	};

	SlideList(Rect range,std::string key);
    ~SlideList();

	void Init(void)override;
	void InitUI(void);
	void Update(double delta)override;
	void SpotUpdate(std::shared_ptr<Controller> controller)override;		//レイが当たっている場合に実行する処理
	void Draw(void)override;

	bool IsIntoMousePos(const Vector2Dbl& mousePos)override;				//マウスの座標との当たり判定チェック

	UIType GetUIType(void)override
	{
		return UIType::SlideList;
	}

private:
	std::unique_ptr<std::string> frameImage_;
	std::string scrKey_;
	std::string image_;


};

